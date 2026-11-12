import * as THREE from './vendor/three.module.js';
import { DEFAULT_CHARACTER_APPEARANCE, loadNativeCharacter } from './native-character.js';
import { WORKSHOP_APPEARANCES, appearanceDetails } from './character-appearances.js';
import { loadNativeCombat, NativePoseTimeline, summarizeNativeMove } from './native-combat.js';
import { loadGmc, loadGmb } from './gmc-loader.js';

const $ = selector => document.querySelector(selector);
const canvas = $('#compare-world'), stage = canvas.parentElement;
const requestedAppearance = new URL(location.href).searchParams.get('appearance');
const initialAppearance = WORKSHOP_APPEARANCES.includes(requestedAppearance) ? requestedAppearance : DEFAULT_CHARACTER_APPEARANCE;
const referenceAppearance = appearance => appearance === 'hutao' ? 'raiden' : 'hutao';
$('#compare-appearance').replaceChildren(...WORKSHOP_APPEARANCES.map(id => { const option = document.createElement('option'); option.value = id; option.textContent = appearanceDetails(id).title; return option; }));
const reducedMotion = matchMedia('(prefers-reduced-motion: reduce)').matches;
const state = { appearance: initialAppearance, complete: true, motion: 'idle', playing: false, physics:true, time: 0, angle: .1, pitch: .1, distance: 6.2, focus: 1.45, view: 'full', ready: false };
const definitions = { idle: { label: '站姿', ids: [6] }, run: { label: '跑步', ids: [144] }, attack: { label: '出招', ids: [262, 263, 264] }, jump: { label: '跳跃', ids: [151, 152, 180] }, guard: { label: '防御', ids: [16] } };
let renderer, camera, actors = [], scenes = [], workshopWeapons = [], motions, raf, pointer = null, lastFrame = performance.now(), lastLabel = 0, width = 1, height = 1, disposed = false;

function resize() {
  width = stage.clientWidth; height = stage.clientHeight;
  renderer.setSize(width, height, false); camera.aspect = width / 2 / height; camera.updateProjectionMatrix();
}
function setMotion(name) {
  if (!motions?.[name]) return;
  actors.forEach(actor=>actor.setSourceRestPose?.(false)); updateSourceRestControl();
  state.motion = name; state.time = 0;
  document.querySelectorAll('[data-motion]').forEach(button => button.setAttribute('aria-pressed', String(button.dataset.motion === name)));
  renderPose(); actors.forEach(actor=>actor.resetSecondaryMotion()); render();
}
function setView(view) {
  const sourceProportions=actors[1]?.sourceRestAvailable;
  state.view = view; state.distance = view === 'face' ? (sourceProportions ? 1.5 : 1.25) : 6.2; state.focus = view === 'face' ? (sourceProportions ? 2.85 : 2.68) : 1.45; state.pitch = view === 'face' ? .015 : .1; state.angle = .1;
  document.querySelectorAll('[data-view]').forEach(button => button.setAttribute('aria-pressed', String(button.dataset.view === view)));
  render();
}
function setPlaying(value) {
  if(value&&actors[1]?.sourceRestPose){actors[1].setSourceRestPose(false);updateSourceRestControl();renderPose();}
  state.playing = value; $('#play-toggle').setAttribute('aria-pressed', String(value)); $('#play-toggle').textContent = value ? '暂停动作' : '播放动作';
}
function updateSourceRestControl(){
  const available=!!actors[1]?.sourceRestAvailable,active=!!actors[1]?.sourceRestPose,button=$('#source-rest');
  button.hidden=!available;button.setAttribute('aria-pressed',String(active));button.textContent=active?'返回动作预览':'原模型姿态';
  $('#hair-physics').disabled=active;$('#hair-physics').textContent=active?'头发物理：暂停':state.physics?'头发物理：开':'头发物理：关';
  $('#motion-frame').disabled=active;if(workshopWeapons[1])workshopWeapons[1].visible=!active;
}
function renderPose(updateLabel = true) {
  if (!state.ready) return;
  const motion = motions[state.motion]; let remaining = state.time % motion.duration, part = motion.parts.at(-1);
  for (const candidate of motion.parts) { part = candidate; if (remaining <= candidate.duration) break; remaining -= candidate.duration; }
  const timeline = new NativePoseTimeline(part.pose); const frame = timeline.advance(Math.min(remaining, part.duration));
  // The same browser physical jump is applied to both actors. Suppressed native
  // scene translation remains aligned with the collision-root jump fix.
  const time = state.time % motion.duration, lift = state.motion === 'jump' ? Math.max(0, 12 * time - 17 * time * time) : 0;
  for (const actor of actors) { actor.group.position.y = lift; actor.setPoseFrame(frame.source, frame.frame); }
  if (!updateLabel) return;
  const fraction = (state.time % motion.duration) / motion.duration;
  $('#motion-frame').value = String(Math.round(fraction * 1000)); $('#progress-label').textContent = `${Math.round(fraction * 100)}%`;
  $('#frame-label').textContent = actors[1]?.sourceRestPose ? '原模型姿态' : `同步：${definitions[state.motion].label} · ${Math.round(fraction * 100)}%`;
}
function render() {
  if (!renderer || !camera) return;
  const motion = motions?.[state.motion], time = motion ? state.time % motion.duration : 0;
  const lift = state.motion === 'jump' ? Math.max(0, 12 * time - 17 * time * time) : 0;
  const focus = new THREE.Vector3(0, state.focus + lift, 0);
  // Narrow side-by-side panes need more distance to keep the whole face in
  // frame. Both subjects still use exactly the same camera and zoom factor.
  const distance = state.distance * Math.max(1, (state.view === 'face' ? .7 : .35) / camera.aspect);
  camera.position.set(Math.sin(state.angle) * distance, focus.y + Math.sin(state.pitch) * distance, Math.cos(state.angle) * distance); camera.lookAt(focus);
  renderer.setScissorTest(true);
  for (let side = 0; side < scenes.length; side++) {
    const left = side === 0 ? 0 : Math.floor(width / 2), paneWidth = side === 0 ? Math.floor(width / 2) : width - left;
    renderer.setViewport(left, 0, paneWidth, height); renderer.setScissor(left, 0, paneWidth, height); renderer.render(scenes[side], camera);
  }
}
function frame(now) {
  if (disposed) return;
  const dt = Math.min(.05, Math.max(0, (now - lastFrame) / 1000)); lastFrame = now;
  if (state.ready && state.playing && !document.hidden) { state.time += dt; const updateLabel = now - lastLabel > 65; renderPose(updateLabel); if (updateLabel) lastLabel = now; }
  if(state.ready&&!document.hidden)actors.forEach(actor=>actor.updateSecondaryMotion(dt,{groundY:0}));
  render(); raf = requestAnimationFrame(frame);
}
function studio(actor) {
  const scene = new THREE.Scene(); scene.background = new THREE.Color(0x1b2627);
  scene.add(new THREE.HemisphereLight(0xdfe9e4, 0x7b7462, 2));
  const key = new THREE.DirectionalLight(0xffebcd, 2.3); key.position.set(-3, 5, 5); scene.add(key);
  const fill = new THREE.DirectionalLight(0xb8d3df, .65); fill.position.set(4, 2, 2); scene.add(fill);
  const rim = new THREE.DirectionalLight(0xc5e1d1, 1.1); rim.position.set(1, 3, -4); scene.add(rim);
  const floor = new THREE.Mesh(new THREE.CircleGeometry(8, 96), new THREE.MeshStandardMaterial({ color: 0x283331, roughness: .96 })); floor.rotation.x = -Math.PI / 2; floor.position.y = -.035; scene.add(floor);
  const ring = new THREE.Mesh(new THREE.RingGeometry(1.05, 1.055, 96), new THREE.MeshBasicMaterial({ color: 0x778878, transparent: true, opacity: .38, side: THREE.DoubleSide })); ring.rotation.x = -Math.PI / 2; ring.position.y = -.025; scene.add(ring);
  scene.add(actor.group); return scene;
}
async function sword() {
  const root = new URL('./assets/original/weapon-models/', import.meta.url), manifest = await fetch(new URL('manifest.json', root)).then(response => { if (!response.ok) throw new Error('原版武器清单未能读取'); return response.json(); });
  const item = manifest.models.find(model => model.modelId.toLowerCase() === 'w0_0'); if (!item) throw new Error('原版长剑缺失');
  const textureMap = {}, textureAlphaMap = {};
  for (const texture of item.textures) { const path = texture.url || texture.frames?.[0]?.url; if (path) textureMap[texture.reference.toLowerCase()] = new URL(path, root).href; if (texture.alphaMask) textureAlphaMap[texture.reference.toLowerCase()] = new URL(texture.alphaMask, root).href; }
  const url = new URL(item.modelUrl, root), loader = item.format === 'GMB' ? loadGmb : loadGmc;
  const model = await loader(url.href, { scale: 1, groundZ: 0, textureMap, textureAlphaMap, texturePath: new URL('textures/', url).href, unlit: true });
  for (const actor of actors) { const clone = model.clone(true); clone.rotation.x = Math.PI / 2; actor.getAttachment('d_wpnR').add(clone); actor.registerVisualAttachment?.(clone,'d_wpnR'); workshopWeapons.push(clone); }
}
function updateVariantLabels() {
  const details = appearanceDetails(state.appearance);
  const reference = appearanceDetails(referenceAppearance(state.appearance));
  $('#compare-appearance').value = state.appearance;
  updateSourceRestControl();
  $('#compare-name').textContent = details.name;
  $('#reference-title').textContent = reference.title;
  $('#variant-title').textContent = details.title;
  $('#apply-appearance').textContent = state.complete ? '使用此外观进入游戏 ↗' : '模型不完整，暂不可启用';
  $('#apply-appearance').disabled = !state.complete;
  $('#compare-description').textContent = `左侧为${reference.name}，右侧为${details.name}。两侧共用视角、灯光和动作进度。`;
  $('#appearance-note').textContent = state.complete ? details.note : actors[1]?.appearanceStatus.reason || '当前模型尚不完整，仅供工坊预览。';
  document.title = `${details.name} · 人物外观对照`;
  const url = new URL(location.href); url.searchParams.set('appearance', state.appearance); history.replaceState(null, '', url.pathname + url.search + url.hash);
  for (const [index, selector] of ['#reference-stats', '#variant-stats'].entries()) {
    $(selector).textContent = `${(actors[index].mesh.geometry.index.count / 3).toLocaleString()} 三角面`;
  }
}
$('#compare-appearance').value = initialAppearance;
$('#compare-appearance').addEventListener('change', async event => {
  if (!state.ready) return;
  const requested = event.target.value, select = event.target; select.disabled = true; $('#apply-appearance').disabled = true;
  try {
    const status = await actors[1].setAppearance(requested, { allowIncomplete: true });
    if (!status.available) throw new Error(status.reason || '外观无法载入');
    const reference = await actors[0].setAppearance(referenceAppearance(requested));
    if (!reference.available) throw new Error(reference.reason || '对照人物无法载入');
    state.appearance = requested; state.complete = status.complete !== false;
    updateVariantLabels(); renderPose(); actors.forEach(actor => actor.resetSecondaryMotion()); render();
  } catch (error) {
    await Promise.all([actors[0].setAppearance(referenceAppearance(state.appearance)), actors[1].setAppearance(state.appearance, { allowIncomplete: true })]);
    updateVariantLabels(); $('#appearance-note').textContent = error.message + '。已恢复此前外观，可稍后重试。';
  }
  finally { select.disabled = false; $('#apply-appearance').disabled = !state.complete || actors[1].appearance !== state.appearance; }
});
document.querySelectorAll('[data-motion]').forEach(button => button.addEventListener('click', () => setMotion(button.dataset.motion)));
document.querySelectorAll('[data-view]').forEach(button => button.addEventListener('click', () => setView(button.dataset.view)));
$('#reset-view').addEventListener('click', () => setView(state.view));
$('#play-toggle').addEventListener('click', () => setPlaying(!state.playing));
$('#source-rest').addEventListener('click',()=>{const value=!actors[1]?.sourceRestPose;if(value){setPlaying(false);setMotion('idle');}actors[1]?.setSourceRestPose(value);updateSourceRestControl();renderPose();render();});
$('#hair-physics').addEventListener('click',()=>{state.physics=!state.physics;actors.forEach(actor=>actor.setSecondaryMotionEnabled(state.physics));$('#hair-physics').setAttribute('aria-pressed',String(state.physics));$('#hair-physics').textContent=state.physics?'头发物理：开':'头发物理：关';});
$('#motion-frame').addEventListener('input', event => { if (!state.ready) return; setPlaying(false); state.time = Number(event.target.value) / 1000 * motions[state.motion].duration; if (Number(event.target.value) === 1000) state.time -= 1e-6; renderPose(); actors.forEach(actor=>actor.resetSecondaryMotion()); render(); });
canvas.addEventListener('pointerdown', event => { if (event.button !== 0) return; pointer = { id: event.pointerId, x: event.clientX, y: event.clientY }; canvas.setPointerCapture(event.pointerId); canvas.focus(); });
canvas.addEventListener('pointermove', event => { if (!pointer || pointer.id !== event.pointerId) return; state.angle -= (event.clientX - pointer.x) * .006; state.pitch = THREE.MathUtils.clamp(state.pitch + (event.clientY - pointer.y) * .004, -.25, .7); pointer.x = event.clientX; pointer.y = event.clientY; render(); });
for (const name of ['pointerup', 'pointercancel', 'lostpointercapture']) canvas.addEventListener(name, () => { pointer = null; });
canvas.addEventListener('wheel', event => { event.preventDefault(); state.distance = THREE.MathUtils.clamp(state.distance + event.deltaY * .004, state.view === 'face' ? .8 : 2.7, 10); render(); }, { passive: false });
canvas.addEventListener('keydown', event => { if (!['ArrowLeft', 'ArrowRight', 'ArrowUp', 'ArrowDown', ' '].includes(event.key)) return; event.preventDefault(); if (event.key === ' ') setPlaying(!state.playing); else if (event.key === 'ArrowLeft') state.angle -= .1; else if (event.key === 'ArrowRight') state.angle += .1; else state.pitch = THREE.MathUtils.clamp(state.pitch + (event.key === 'ArrowUp' ? -.06 : .06), -.25, .7); render(); });
$('#apply-appearance').addEventListener('click', () => { if (!state.complete) return; try { const prefs = JSON.parse(localStorage.getItem('meteor-web-original-v2') || '{}'); prefs.character = 0; prefs.characterAppearance = state.appearance; prefs.characterSelected = true; localStorage.setItem('meteor-web-original-v2', JSON.stringify(prefs)); } catch { /* the game also receives the explicit appearance query */ } location.href = './index.html?appearance='+encodeURIComponent(state.appearance); });
window.addEventListener('resize', () => { if (renderer) { resize(); render(); } });
window.addEventListener('pagehide', () => { disposed = true; cancelAnimationFrame(raf); actors.forEach(actor => actor.dispose()); renderer?.dispose(); });

try {
  renderer = new THREE.WebGLRenderer({ canvas, antialias: true, powerPreference: 'high-performance' }); renderer.setPixelRatio(Math.min(devicePixelRatio || 1, 2)); renderer.outputColorSpace = THREE.SRGBColorSpace; renderer.toneMapping = THREE.ACESFilmicToneMapping; renderer.toneMappingExposure = 1.05;
  camera = new THREE.PerspectiveCamera(36, 1, .05, 100); resize();
  const [reference, enhanced, combat] = await Promise.all([loadNativeCharacter(0, { inPlace: true, appearance: referenceAppearance(initialAppearance) }), loadNativeCharacter(0, { inPlace: true, appearance: initialAppearance }), loadNativeCombat()]);
  actors = [reference, enhanced]; if (reference.appearance !== referenceAppearance(initialAppearance)) throw new Error(reference.appearanceStatus.reason || '对照人物无法载入'); await enhanced.setAppearance(initialAppearance, { allowIncomplete: true }); state.complete = enhanced.appearanceStatus.complete !== false; if (enhanced.appearance !== initialAppearance) throw new Error(enhanced.appearanceStatus.reason || '所选外观尚未能载入');
  scenes = actors.map(studio); await sword();
  motions = Object.fromEntries(Object.entries(definitions).map(([key, value]) => { const parts = value.ids.map(id => { const pose = combat.poses.get(id); if (!pose?.valid) throw new Error(`原版动作 ${id} 不可用`); return { pose, duration: summarizeNativeMove(pose).duration }; }); return [key, { parts, duration: parts.reduce((sum, part) => sum + part.duration, 0) }]; }));
  updateVariantLabels();
  state.ready = true; $('#compare-loading').hidden = true; $('#compare-appearance').disabled = false; $('#apply-appearance').disabled = !state.complete; setMotion('idle'); setPlaying(false); if (reducedMotion) $('#play-toggle').title = '已尊重系统减少动态效果设置，点击后播放';
  raf = requestAnimationFrame(frame);
} catch (error) {
  console.error(error); const loading = $('#compare-loading'); loading.replaceChildren(); const title = document.createElement('strong'); title.textContent = '人物工坊暂未准备好'; const description = document.createElement('p'); description.textContent = error.message; const retry = document.createElement('button'); retry.className = 'primary'; retry.textContent = '重新载入'; retry.addEventListener('click', () => location.reload()); loading.append(title, description, retry);
}
