import * as THREE from './vendor/three.module.js';
import { loadGmb, loadGmc } from './gmc-loader.js';

const TAU = Math.PI * 2;
const clamp = THREE.MathUtils.clamp;
const mix = THREE.MathUtils.lerp;
const WEAPONS = {
  sword: { name: '长剑', reach: 3.15, damage: 24, duration: .55, color: 0xe4e8db },
  blade: { name: '大刀', reach: 3.35, damage: 32, duration: .72, color: 0xd9dccd },
  spear: { name: '长枪', reach: 4.5, damage: 25, duration: .65, color: 0xd6e1e0 }
};
const UP = new THREE.Vector3(0, 1, 0);

export class MeteorGame {
  constructor(canvas, { onUpdate = () => {}, onEvent = () => {}, onEnd = () => {} } = {}) {
    this.canvas = canvas;
    this.onUpdate = onUpdate; this.onEvent = onEvent; this.onEnd = onEnd;
    this.scene = new THREE.Scene();
    this.scene.background = new THREE.Color(0x090f17);
    this.scene.fog = new THREE.FogExp2(0x15202a, .017);
    this.camera = new THREE.PerspectiveCamera(48, 1, .1, 220);
    this.renderer = new THREE.WebGLRenderer({ canvas, antialias: true, alpha: false, powerPreference: 'high-performance' });
    this.renderer.setPixelRatio(Math.min(devicePixelRatio || 1, 1.75));
    this.renderer.shadowMap.enabled = true;
    this.renderer.shadowMap.type = THREE.PCFSoftShadowMap;
    this.renderer.outputColorSpace = THREE.SRGBColorSpace;
    this.renderer.toneMapping = THREE.ACESFilmicToneMapping;
    this.renderer.toneMappingExposure = 1.3;
    this.clock = new THREE.Clock();
    this.elapsed = 0; this.updateAccum = 0; this.running = false; this.paused = false;
    this.keys = new Set(); this.enemies = []; this.effects = []; this.trails = [];
    this.particles = []; this.collision = []; this.weapon = 'sword'; this.map = 'sifang';
    this.difficulty = 'normal'; this.quality = 'high'; this.muted = false;
    this.cameraAngle = .4; this.cameraPitch = .5; this.cameraDistance = 10;
    this.cameraTarget = new THREE.Vector3(); this.locked = null;
    this.wind = new THREE.Vector3(.2, 0, .1);
    this.materials = {}; this._listeners = [];
    this._initMaterials(); this._initLights(); this._buildWorld('sifang');
    this.hero = this._fighter(0xd4d0b8, 0x213a3f, true);
    this.scene.add(this.hero.root);
    this._resetFighter(this.hero, 3, 2, 100);
    this.hero.root.rotation.y = -.5;
    this.hero.root.scale.setScalar(1.38);
    this._loadOriginalWeapon();
    this._bind(); this.resize();
    this._frame = this._frame.bind(this); this.raf = requestAnimationFrame(this._frame);
    if (typeof window !== 'undefined') window.__game = this;
  }

  _mat(name, color, roughness = .85, metalness = 0) {
    return this.materials[name] ||= new THREE.MeshStandardMaterial({ color, roughness, metalness });
  }
  _initMaterials() {
    this._mat('stone', 0x3b4548); this._mat('edge', 0x282f34); this._mat('tile', 0x3c4b4e);
    this._mat('wood', 0x342220); this._mat('redwood', 0x713b32); this._mat('roof', 0x27343b);
    this._mat('gold', 0xb39452, .35, .72); this._mat('darkgold', 0x62533a, .6, .4);
    this._mat('black', 0x151e24); this._mat('skin', 0xd3b79b); this._mat('hair', 0x14191c);
    this._mat('leaf', 0x974653); this._mat('bamboo', 0x37594e); this._mat('ember', 0xc34f22);
  }
  _initLights() {
    this.ambient = new THREE.HemisphereLight(0xa5b5c3, 0x161e20, 2.05);
    this.scene.add(this.ambient);
    this.key = new THREE.DirectionalLight(0xb1cedf, 2.8);
    this.key.position.set(-16, 28, 8); this.key.castShadow = true;
    Object.assign(this.key.shadow.camera, { left: -25, right: 25, top: 25, bottom: -25, near: .5, far: 80 });
    this.key.shadow.mapSize.set(2048, 2048); this.key.shadow.bias = -.00035;
    this.key.shadow.normalBias = .035; this.scene.add(this.key);
    this.rim = new THREE.DirectionalLight(0xd1776a, 1.55); this.rim.position.set(8, 9, -20); this.scene.add(this.rim);
    this.heroLight = new THREE.PointLight(0xc2def6, 10, 15, 2); this.heroLight.position.set(2, 5, 4); this.scene.add(this.heroLight);
  }
  _mesh(geometry, material, parent, x = 0, y = 0, z = 0, shadow = true) {
    const mesh = new THREE.Mesh(geometry, material); mesh.position.set(x, y, z);
    mesh.castShadow = shadow; mesh.receiveShadow = true; (parent || this.world).add(mesh); return mesh;
  }
  _box(w, h, d, mat, parent, x = 0, y = 0, z = 0, shadow = true) {
    return this._mesh(new THREE.BoxGeometry(w, h, d), mat, parent, x, y, z, shadow);
  }
  _cyl(rt, rb, height, mat, parent, x = 0, y = 0, z = 0, sides = 10) {
    return this._mesh(new THREE.CylinderGeometry(rt, rb, height, sides), mat, parent, x, y, z);
  }
  _beam(a, b, radius, mat, parent) {
    const v = new THREE.Vector3().subVectors(b, a);
    const mesh = this._cyl(radius * .8, radius, v.length(), mat, parent);
    mesh.position.copy(a).add(b).multiplyScalar(.5); mesh.quaternion.setFromUnitVectors(UP, v.normalize()); return mesh;
  }
  _disposeGroup(group) {
    if (!group) return;
    const shared = new Set(Object.values(this.materials)), geometries = new Set(), materials = new Set(), textures = new Set();
    group.traverse(o => {
      if (o.geometry) geometries.add(o.geometry);
      for (const m of o.material ? (Array.isArray(o.material) ? o.material : [o.material]) : []) {
        if (!shared.has(m)) { materials.add(m); if (m.map) textures.add(m.map); }
      }
    });
    geometries.forEach(g => g.dispose()); textures.forEach(t => t.dispose()); materials.forEach(m => m.dispose());
    group.removeFromParent();
  }
  _buildWorld(map) {
    this._disposeGroup(this.world);
    this.world = new THREE.Group(); this.scene.add(this.world); this.collision = []; this.petals = [];
    this.originalMap = null; this.groundCache = new Map(); this.mapBuildId = (this.mapBuildId || 0) + 1;
    const forge = map === 'forge', valley = map === 'butterfly';
    const fog = forge ? 0x251b1c : valley ? 0x152923 : 0x17232c;
    this.scene.background.set(forge ? 0x150d12 : valley ? 0x071815 : 0x09121d);
    this.scene.fog.color.setHex(fog); this.scene.fog.density = valley ? .021 : .015;
    this.key.color.setHex(forge ? 0xdab2a1 : valley ? 0xb8d1c1 : 0xb5d6e9);
    this.rim.color.setHex(forge ? 0xff6532 : valley ? 0xb5cfa1 : 0xe69d8d);
    const baseMat = forge ? this._mat('forgestone', 0x332d30) : this.materials.stone;
    const tileMat = forge ? this._mat('forgetile', 0x393236) : valley ? this._mat('mossytile', 0x3b4b43) : this.materials.tile;
    this._box(43, 1.2, 43, this.materials.edge, this.world, 0, -.75, 0);
    this._box(39, .35, 39, baseMat, this.world, 0, -.12, 0);
    // A deliberately imperfect field of individual stone paving slabs.
    const slabGeo = new THREE.BoxGeometry(2.32, .14, 2.32);
    const floor = new THREE.InstancedMesh(slabGeo, tileMat, 256);
    const dummy = new THREE.Object3D(); let idx = 0;
    for (let ix = 0; ix < 16; ix++) for (let iz = 0; iz < 16; iz++) {
      dummy.position.set((ix - 7.5) * 2.4, -.015 + Math.sin(ix * 7 + iz) * .012, (iz - 7.5) * 2.4);
      dummy.rotation.y = ((ix * 31 + iz * 17) % 5 - 2) * .002; dummy.updateMatrix(); floor.setMatrixAt(idx++, dummy.matrix);
      floor.setColorAt(idx - 1, new THREE.Color().setScalar(.76 + ((ix * 13 + iz * 7) % 9) * .03));
    }
    floor.receiveShadow = true; this.world.add(floor);
    for (let radius of [4.7, 5, 7.8]) {
      const ring = this._mesh(new THREE.TorusGeometry(radius, radius === 5 ? .035 : .018, 4, 112), this.materials.darkgold, this.world, 0, .073, 0, false);
      ring.rotation.x = Math.PI / 2;
    }
    for (let i = 0; i < 12; i++) {
      const a = i * TAU / 12;
      const mark = this._box(.09, .02, .65, this.materials.gold, this.world, Math.sin(a) * 5.45, .08, Math.cos(a) * 5.45, false); mark.rotation.y = a;
    }
    // Inlaid compass petals at the arena centre.
    for (let i = 0; i < 8; i++) {
      const a = i * TAU / 8;
      const line = this._box(.035, .015, 2.9, this.materials.darkgold, this.world, Math.sin(a) * 1.5, .08, Math.cos(a) * 1.5, false); line.rotation.y = a;
    }
    this._railings(forge);
    if (forge) this._forge();
    else {
      this._pavilion(0, -17.5, 1.35, true);
      this._pavilion(-17.5, -7, .68); this._pavilion(17.5, -7, .68);
      this._gate(0, 17.7, .9);
      this.fallbackObjects = this.world.children.slice();
      if (valley) this._bamboo(); else { this._cherry(-12.5, -9); this._cherry(15, 10, .7); }
      this._moon(valley);
    }
    this._mountains(forge, valley);
    this._mist(forge, valley);
    for (const [x, z] of [[-15, -13], [15, -13], [-15, 12], [15, 12]]) {
      this._lanternPost(x, z, forge); this.collision.push({ x, z, r: .65 });
    }
    for (let i = 0; i < 40; i++) {
      const p = this._mesh(new THREE.PlaneGeometry(.08 + Math.random() * .1, .11), new THREE.MeshBasicMaterial({ color: forge ? 0xff963e : valley ? 0xc6d5ad : 0xd88e9b, side: THREE.DoubleSide, transparent: true, opacity: .65 }), this.world, (Math.random() - .5) * 38, 2 + Math.random() * 10, (Math.random() - .5) * 38, false);
      p.rotation.set(Math.random() * 3, Math.random() * 3, Math.random() * 3); this.petals.push({ mesh: p, speed: .25 + Math.random() * .5, phase: Math.random() * TAU });
    }
    this.map = map;
    if (map === 'sifang') this._loadOriginalMap(this.mapBuildId);
  }
  async _loadOriginalMap(buildId) {
    try {
      const model = await loadGmb('./assets/sifang/sn06.gmb', { scale: .015, groundZ: -360.545, texturePath: './assets/sifang/textures/' });
      if (this.disposed || buildId !== this.mapBuildId || this.map !== 'sifang') { this._disposeGroup(model); return; }
      this.originalMap = model; this.groundMeshes = model.children.filter(m => m.userData.collidable); this.world.add(model); model.updateMatrixWorld(true);
      for (const object of this.fallbackObjects) object.visible = false;
      this.collision = []; this.raycaster ||= new THREE.Raycaster();
      for (const f of [this.hero, ...this.enemies]) if (f) f.root.position.y = this._groundHeight(f.root.position.x, f.root.position.z) + f.jump;
      if (!this.running && this.hero) { this.hero.root.position.set(3.5, this._groundHeight(3.5, 2), 2); }
      this._tickCamera(1);
    } catch (error) { console.warn('Original map could not be loaded; using the built-in arena.', error); }
  }
  _groundHeight(x, z) {
    if (!this.originalMap) return 0;
    const key = `${Math.round(x * 4)},${Math.round(z * 4)}`;
    if (this.groundCache.has(key)) return this.groundCache.get(key);
    this.raycaster ||= new THREE.Raycaster();
    this.raycaster.set(new THREE.Vector3(x, 30, z), new THREE.Vector3(0, -1, 0));
    const hit = this.raycaster.intersectObjects(this.groundMeshes || this.originalMap.children, false).find(h => h.face?.normal.y > .4 && h.point.y < 12);
    const height = hit ? Math.max(0, hit.point.y) : 0; this.groundCache.set(key, height); return height;
  }
  async _loadOriginalWeapon() {
    try {
      const model = await loadGmc('./assets/weapons/qingfeng.gmc', { scale: .06, groundZ: 0, texturePath: './assets/weapons/' });
      if (this.disposed) { this._disposeGroup(model); return; }
      this.originalSword = model;
      if (this.hero.weapon === 'sword') this._equip(this.hero, 'sword');
    } catch (error) { console.warn('Community sword unavailable; using the built-in weapon.', error); }
  }
  _railings(forge) {
    const m = forge ? this.materials.black : this.materials.redwood;
    for (let side of [-1, 1]) for (let i = -3; i <= 3; i++) {
      for (let axis = 0; axis < 2; axis++) {
        const x = axis ? i * 5 : side * 19, z = axis ? side * 19 : i * 5;
        if (axis && Math.abs(i) < 2) continue;
        this._box(.5, 1.8, .5, this.materials.stone, this.world, x, .8, z);
        this._box(.7, .14, .7, this.materials.gold, this.world, x, 1.72, z);
        const beam = this._box(axis ? 4.5 : .16, .17, axis ? .16 : 4.5, m, this.world, axis ? x + 2.5 : x, 1.2, axis ? z : z + 2.5);
        this._box(axis ? 4.5 : .13, .13, axis ? .13 : 4.5, m, this.world, axis ? x + 2.5 : x, .55, axis ? z : z + 2.5);
      }
    }
    // Wide carved entrance steps sit below the courtyard level.
    for (let i = 0; i < 4; i++) this._box(12, .28, 2.3, this.materials.stone, this.world, 0, -.28 - i * .22, 20 + i * 1.5);
  }
  _roof(parent, w, depth, y, scale = 1) {
    // Swept roof surfaces, layered eaves, and raised ridge endcaps.
    const roof = new THREE.Group(); parent.add(roof); roof.position.y = y;
    const points = [];
    for (let side of [-1, 1]) {
      const verts = [], uvs = [], indices = [];
      for (let i = 0; i <= 12; i++) {
        const t = i / 12, z = side * t * depth / 2;
        const yy = 1.65 * (1 - t) + .7 * Math.pow(t, 5);
        for (let end of [-1, 1]) { verts.push(end * (w / 2 + .45 * t), yy, z); uvs.push((end + 1) / 2, t); }
        if (i < 12) { const k = i * 2; indices.push(k, k + 1, k + 2, k + 1, k + 3, k + 2); }
      }
      const g = new THREE.BufferGeometry(); g.setAttribute('position', new THREE.Float32BufferAttribute(verts, 3)); g.setAttribute('uv', new THREE.Float32BufferAttribute(uvs, 2)); g.setIndex(indices); g.computeVertexNormals();
      const mat = this.materials.roof.clone(); mat.side = THREE.DoubleSide;
      this._mesh(g, mat, roof);
      const edge = new THREE.CatmullRomCurve3([new THREE.Vector3(-w / 2 - .45, .7, side * depth / 2), new THREE.Vector3(0, .55, side * depth / 2), new THREE.Vector3(w / 2 + .45, .7, side * depth / 2)]);
      this._mesh(new THREE.TubeGeometry(edge, 20, .13, 5, false), this.materials.darkgold, roof);
      for (let i = 0; i <= Math.floor(w * 2); i++) {
        const x = -w / 2 + i * .5;
        const path = new THREE.CatmullRomCurve3([new THREE.Vector3(x, 1.68, 0), new THREE.Vector3(x, .79, side * depth * .29), new THREE.Vector3(x, .75, side * depth / 2)]);
        this._mesh(new THREE.TubeGeometry(path, 8, .045, 4, false), this.materials.roof, roof, 0, 0, 0, false);
      }
    }
    this._box(w + .6, .18, .2, this.materials.gold, roof, 0, 1.73, 0);
    for (let side of [-1, 1]) {
      const path = new THREE.CatmullRomCurve3([new THREE.Vector3(side * (w / 2 - .4), 1.75, 0), new THREE.Vector3(side * (w / 2 + .2), 1.9, 0), new THREE.Vector3(side * (w / 2 + .45), 2.35, 0)]);
      this._mesh(new THREE.TubeGeometry(path, 10, .11, 6, false), this.materials.gold, roof);
    }
    return roof;
  }
  _pavilion(x, z, scale = 1, main = false) {
    const g = new THREE.Group(); this.world.add(g); g.position.set(x, 0, z); g.scale.setScalar(scale);
    this._box(10, .65, 7, this.materials.stone, g, 0, .16, 0);
    this._box(9.2, .24, 6.3, this.materials.edge, g, 0, .62, 0);
    for (let xx of [-3.7, 3.7]) for (let zz of [-2.3, 2.3]) {
      this._cyl(.21, .3, 5, this.materials.redwood, g, xx, 3, zz);
      this._cyl(.4, .4, .25, this.materials.gold, g, xx, .85, zz);
      this._box(.75, .4, .75, this.materials.gold, g, xx, 5.25, zz);
    }
    this._box(8, .4, .28, this.materials.redwood, g, 0, 5, 2.3);
    this._box(8, .4, .28, this.materials.redwood, g, 0, 5, -2.3);
    this._box(7.7, 3.9, .25, this.materials.wood, g, 0, 2.8, -2.4);
    for (let xx of [-2.5, 0, 2.5]) {
      this._box(1.6, 2.7, .08, this._mat('screen', 0x5d655b), g, xx, 2.9, -2.2);
      for (let iy = 0; iy < 7; iy++) this._box(1.7, .05, .1, this.materials.redwood, g, xx, 1.6 + iy * .42, -2.13);
      for (let ix = 0; ix < 4; ix++) this._box(.05, 2.7, .1, this.materials.redwood, g, xx - .65 + ix * .43, 2.9, -2.13);
    }
    this._roof(g, 11, 8, 5.3);
    if (main) { this._box(5, .85, .25, this.materials.black, g, 0, 4.65, 2.5); this._inscription(g, '四 方 阵', 0, 4.65, 2.66, 4.2, .6); }
    for (let xx of [-3.5, 3.5]) this._lantern(g, xx, 4.55, 2.5, .65);
    // Three broad steps lead from the arena into the main hall.
    for (let i = 0; i < 3; i++) this._box(7, .23, .8, this.materials.stone, g, 0, .45 - i * .2, 3.5 + i * .7);
  }
  _inscription(parent, text, x, y, z, width, height) {
    const c = document.createElement('canvas'); c.width = 768; c.height = 160;
    const ctx = c.getContext('2d'); ctx.fillStyle = '#d8bb77'; ctx.textAlign = 'center'; ctx.textBaseline = 'middle'; ctx.font = '80px serif'; ctx.fillText(text, 384, 80);
    const tex = new THREE.CanvasTexture(c); tex.colorSpace = THREE.SRGBColorSpace;
    this._mesh(new THREE.PlaneGeometry(width, height), new THREE.MeshBasicMaterial({ map: tex, transparent: true }), parent, x, y, z, false);
  }
  _gate(x, z, s) {
    const g = new THREE.Group(); this.world.add(g); g.position.set(x, 0, z); g.scale.setScalar(s);
    for (let side of [-1, 1]) { this._cyl(.28, .4, 6, this.materials.redwood, g, side * 4.5, 3, 0); this._box(1, .4, 1, this.materials.stone, g, side * 4.5, .3, 0); }
    this._box(10, .5, .5, this.materials.redwood, g, 0, 5.5, 0); this._roof(g, 11, 3.2, 5.8);
  }
  _lantern(parent, x, y, z, s = 1) {
    const g = new THREE.Group(); parent.add(g); g.position.set(x, y, z); g.scale.setScalar(s);
    const mat = this._mat('lantern', 0xba4a2f, .7); mat.emissive.setHex(0xd55b28); mat.emissiveIntensity = 1.1;
    this._mesh(new THREE.SphereGeometry(.36, 12, 8), mat, g, 0, -.4, 0).scale.set(1, 1.35, 1);
    for (let side of [-1, 1]) this._cyl(.26, .26, .09, this.materials.gold, g, 0, -.4 + side * .45, 0);
    this._cyl(.022, .022, .45, this.materials.gold, g, 0, .25, 0);
    this._cyl(.025, .025, .35, this.materials.redwood, g, 0, -1.05, 0);
  }
  _lanternPost(x, z, forge) {
    this._box(1.2, .25, 1.2, this.materials.stone, this.world, x, .2, z);
    this._cyl(.15, .22, 3.8, forge ? this.materials.black : this.materials.redwood, this.world, x, 2.1, z);
    this._box(1.5, .14, .2, this.materials.gold, this.world, x, 4, z);
    this._lantern(this.world, x, 3.7, z, 1);
    const light = new THREE.PointLight(forge ? 0xff5c27 : 0xffa057, 17, 11, 2); light.position.set(x, 3, z); this.world.add(light);
  }
  _moon(valley) {
    const c = document.createElement('canvas'); c.width = c.height = 512;
    const ctx = c.getContext('2d'); const grad = ctx.createRadialGradient(256, 256, 0, 256, 256, 256);
    grad.addColorStop(0, valley ? '#d9d7b3' : '#a9433d'); grad.addColorStop(.7, valley ? '#b2bda0' : '#b45348'); grad.addColorStop(.88, valley ? '#c4cfb0' : '#eb9071'); grad.addColorStop(.91, '#e6a589'); grad.addColorStop(.96, '#b9654a66'); grad.addColorStop(1, '#9c443000');
    ctx.fillStyle = grad; ctx.fillRect(0, 0, 512, 512);
    ctx.globalCompositeOperation = 'source-atop';
    for (let i = 0; i < 170; i++) { ctx.fillStyle = `rgba(18,14,19,${Math.random() * .1})`; ctx.beginPath(); ctx.arc(Math.random() * 512, Math.random() * 512, 5 + Math.random() * 36, 0, TAU); ctx.fill(); }
    const tex = new THREE.CanvasTexture(c); tex.colorSpace = THREE.SRGBColorSpace;
    const moon = new THREE.Sprite(new THREE.SpriteMaterial({ map: tex, transparent: true, fog: false, depthWrite: false, color: 0xffffff }));
    moon.position.set(valley ? -7 : 7, 25, -72); moon.scale.set(27, 27, 1); this.world.add(moon);
    if (!valley) {
      // The small, dark occluding disk creates the unmistakable red eclipse.
      const eclipse = this._mesh(new THREE.CircleGeometry(9.4, 80), new THREE.MeshBasicMaterial({ color: 0x231a25, fog: false }), this.world, 7.5, 26.1, -71.6, false);
      eclipse.rotation.y = 0;
    }
  }
  _mountains(forge, valley) {
    const colors = forge ? [0x221a22, 0x30212a, 0x3c2a2c] : valley ? [0x122729, 0x1b3436, 0x254344] : [0x172530, 0x1e303d, 0x283e47];
    for (let layer = 0; layer < 3; layer++) {
      const vertices = [], indices = [];
      for (let i = 0; i <= 34; i++) {
        const x = (i - 17) * 7, h = 9 + Math.sin(i * 1.91 + layer * 4) * 5 + Math.sin(i * 4.2) * 3 + layer * 4;
        vertices.push(x, -5, -52 - layer * 18, x, h, -52 - layer * 18);
        if (i < 34) { let k = i * 2; indices.push(k, k + 1, k + 2, k + 1, k + 3, k + 2); }
      }
      const geo = new THREE.BufferGeometry(); geo.setAttribute('position', new THREE.Float32BufferAttribute(vertices, 3)); geo.setIndex(indices); geo.computeVertexNormals();
      this._mesh(geo, new THREE.MeshBasicMaterial({ color: colors[2 - layer], side: THREE.DoubleSide }), this.world, 0, 0, 0, false);
    }
    const ground = this._mesh(new THREE.PlaneGeometry(250, 250), this._mat('earth', forge ? 0x20161b : 0x172a2b), this.world, 0, -2, 0, false); ground.rotation.x = -Math.PI / 2;
    for (let i = 0; i < 18; i++) {
      const a = i * TAU / 18, r = 33 + (i % 4) * 5;
      this._mesh(new THREE.DodecahedronGeometry(2.5 + (i % 3) * 1.2, 0), this.materials.edge, this.world, Math.sin(a) * r, -.3, Math.cos(a) * r);
    }
  }
  _cherry(x, z, scale = 1) {
    const g = new THREE.Group(); this.world.add(g); g.position.set(x, 0, z); g.scale.setScalar(scale);
    const trunk = this._mat('cherrywood', 0x3a2c30);
    this._beam(new THREE.Vector3(0, 0, 0), new THREE.Vector3(.3, 5, -.4), .37, trunk, g);
    const branches = [[-3, 6.5, 0], [2.8, 7.6, .4], [-.8, 8.4, -1.6], [1.7, 6.5, 2.2], [-3.5, 5.7, 2.5]];
    const geo = new THREE.IcosahedronGeometry(1.2, 1), mat = this._mat('blossom', 0xc78089);
    const blossoms = new THREE.InstancedMesh(geo, mat, branches.length * 9); let index = 0; const d = new THREE.Object3D();
    for (let [bx, by, bz] of branches) {
      this._beam(new THREE.Vector3(.2, 3.5, 0), new THREE.Vector3(bx, by, bz), .15, trunk, g);
      for (let j = 0; j < 9; j++) {
        d.position.set(bx + Math.sin(j * 2.4) * 1.6, by + Math.cos(j * 4.3) * .65, bz + Math.cos(j * 1.9) * 1.3);
        d.scale.set(1.1 + (j % 2) * .25, .5 + (j % 3) * .12, .8); d.rotation.set(j, j * 2, 0); d.updateMatrix(); blossoms.setMatrixAt(index, d.matrix);
        blossoms.setColorAt(index++, new THREE.Color(j % 3 === 0 ? 0xe1b0aa : j % 3 === 1 ? 0xbf6f80 : 0xa9536f));
      }
    }
    blossoms.castShadow = true; g.add(blossoms); this.collision.push({ x, z, r: .8 * scale });
    this._box(3.3, .35, 3.3, this.materials.stone, g, 0, .1, 0);
  }
  _bamboo() {
    const bambooMat = this.materials.bamboo, leavesMat = this._mat('bambooleaf', 0x3c6753);
    const g = new THREE.Group(); this.world.add(g);
    for (let i = 0; i < 55; i++) {
      const side = i % 2 ? 1 : -1, x = side * (21 + Math.random() * 15), z = (Math.random() - .5) * 65, height = 8 + Math.random() * 10;
      const stem = this._cyl(.08, .13, height, bambooMat, g, x, height / 2 - 1, z, 6); stem.rotation.z = side * Math.random() * .12;
      for (let j = 1; j < 6; j++) this._cyl(.14, .14, .07, this.materials.gold, g, x, j * height / 6 - 1, z, 6);
      for (let j = 0; j < 3; j++) {
        const leaves = this._mesh(new THREE.ConeGeometry(1.7, 3.5, 4), leavesMat, g, x + (j - 1) * .9, height - 1 - j * 1.7, z); leaves.scale.set(1, .4, .6); leaves.rotation.z = (j - 1) * .6;
      }
    }
    for (let i = 0; i < 8; i++) {
      const rock = this._mesh(new THREE.DodecahedronGeometry(1.4 + i % 3, 0), this._mat('moss', 0x33463d), this.world, (i % 2 ? 1 : -1) * (16 + i % 3), 1, (i - 4) * 4.5); rock.scale.y = .65;
    }
  }
  _forge() {
    const glow = new THREE.MeshStandardMaterial({ color: 0xef6b2a, emissive: 0xff4411, emissiveIntensity: 2.4 });
    for (let i = 0; i < 9; i++) {
      const a = i * TAU / 9;
      const crack = this._box(.035, .02, 9 + i % 4, glow, this.world, Math.sin(a) * 12, .09, Math.cos(a) * 12, false); crack.rotation.y = a + .2;
    }
    const g = new THREE.Group(); g.position.set(0, 0, -18); this.world.add(g);
    this._cyl(3.5, 4.6, 1.5, this.materials.edge, g, 0, .5, 0, 8);
    this._cyl(2.4, 3.3, 5, this.materials.black, g, 0, 3.5, 0, 8);
    this._cyl(1.6, 2.3, 4, this.materials.edge, g, 0, 8, 0, 8);
    this._mesh(new THREE.TorusGeometry(2.7, .22, 6, 8), this.materials.gold, g, 0, 3.2, 0).rotation.x = Math.PI / 2;
    this._box(2.6, 2.5, .2, glow, g, 0, 2.9, 3.05);
    for (let i = -2; i <= 2; i++) this._box(.12, 2.8, .25, this.materials.black, g, i * .52, 2.9, 3.2);
    for (let side of [-1, 1]) {
      for (let zz of [-10, 6]) { const p = this._cyl(.65, .9, 7, this.materials.black, this.world, side * 17, 3.5, zz, 8); this._cyl(.9, .9, .4, this.materials.gold, this.world, side * 17, 5.7, zz, 8); }
      const chain = this._beam(new THREE.Vector3(side * 16, 6, -10), new THREE.Vector3(side * 4, 9, -18), .07, this.materials.black, this.world);
      const basin = this._cyl(1.2, .7, 1.2, this.materials.black, this.world, side * 12, .8, -10, 8);
      this._cyl(1.06, 1.06, .06, glow, this.world, side * 12, 1.44, -10, 12);
      const light = new THREE.PointLight(0xff5821, 35, 20, 2); light.position.set(side * 12, 2.2, -10); this.world.add(light);
      this.collision.push({ x: side * 12, z: -10, r: 1.45 });
    }
    const light = new THREE.PointLight(0xff5d20, 110, 35, 2); light.position.set(0, 5, -15); this.world.add(light);
    this._inscription(g, '炼 铁 狱', 0, 6.1, 2.35, 3.7, .8);
  }
  _mist(forge, valley) {
    const c = document.createElement('canvas'); c.width = c.height = 128;
    const ctx = c.getContext('2d'), grad = ctx.createRadialGradient(64, 64, 0, 64, 64, 64);
    grad.addColorStop(0, 'rgba(180,200,205,.13)'); grad.addColorStop(1, 'rgba(180,200,205,0)'); ctx.fillStyle = grad; ctx.fillRect(0, 0, 128, 128);
    const texture = new THREE.CanvasTexture(c);
    this.mists = [];
    for (let i = 0; i < 9; i++) {
      const sprite = new THREE.Sprite(new THREE.SpriteMaterial({ map: texture, color: forge ? 0x9c7b70 : valley ? 0x6c9b81 : 0x7a9fb1, transparent: true, opacity: .45, depthWrite: false }));
      sprite.position.set((i % 3 - 1) * 16, .5 + i % 2, -13 + Math.floor(i / 3) * 17); sprite.scale.set(30, 5, 1); this.world.add(sprite); this.mists.push(sprite);
    }
  }

  _fighter(clothColor, trimColor, hero = false) {
    const root = new THREE.Group();
    const cloth = new THREE.MeshStandardMaterial({ color: clothColor, roughness: .9 });
    const trim = new THREE.MeshStandardMaterial({ color: trimColor, roughness: .75 });
    const armor = new THREE.MeshStandardMaterial({ color: hero ? 0x6c8584 : 0x625b5a, roughness: .45, metalness: .5 });
    const f = { root, cloth, trim, hero, hp: 100, maxHp: 100, stamina: 100, rage: 0, attack: null, dodge: 0, jump: 0, vy: 0, hit: 0, dead: false, respawn: 0, aiTimer: 0, combo: 0, comboTimer: 0, velocity: new THREE.Vector3(), attackCooldown: 0, weapon: 'sword', walk: 0, guard: false, name: hero ? '孟星魂' : '夜行客' };
    f.body = new THREE.Group(); root.add(f.body);
    this._cyl(.35, .29, .68, cloth, f.body, 0, 1.63, 0, 8);
    this._cyl(.42, .29, .6, trim, f.body, 0, 1.07, 0, 8);
    this._cyl(.36, .36, .14, this.materials.black, f.body, 0, 1.3, 0, 8);
    this._box(.18, .16, .08, this.materials.gold, f.body, 0, 1.3, .35);
    const chest = this._box(.51, .3, .12, armor, f.body, 0, 1.78, .29); chest.rotation.z = -.12;
    this._box(.055, .6, .08, trim, f.body, -.14, 1.7, .34).rotation.z = -.25;
    this._box(.055, .6, .08, trim, f.body, .14, 1.7, .34).rotation.z = .25;
    for (let side of [-1, 1]) {
      const leg = new THREE.Group(); leg.position.set(side * .19, 1.07, 0); f.body.add(leg);
      this._cyl(.13, .15, .47, this.materials.black, leg, 0, -.24, 0, 7);
      const calf = new THREE.Group(); calf.position.y = -.48; leg.add(calf);
      this._cyl(.105, .13, .4, trim, calf, 0, -.2, 0, 7);
      this._box(.23, .19, .39, this.materials.black, calf, 0, -.42, .075);
      this._box(.14, .27, .06, armor, calf, 0, -.17, .105);
      if (side < 0) { f.leftLeg = leg; f.leftCalf = calf; } else { f.rightLeg = leg; f.rightCalf = calf; }
      const arm = new THREE.Group(); arm.position.set(side * .43, 1.95, 0); f.body.add(arm);
      this._mesh(new THREE.SphereGeometry(.19, 8, 6), armor, arm, 0, -.02, 0);
      this._cyl(.125, .155, .43, cloth, arm, 0, -.25, 0, 7);
      const forearm = new THREE.Group(); forearm.position.y = -.45; arm.add(forearm);
      this._cyl(.09, .12, .34, trim, forearm, 0, -.17, 0, 7);
      this._cyl(.1, .1, .16, armor, forearm, 0, -.24, 0, 7);
      this._mesh(new THREE.SphereGeometry(.1, 7, 5), this.materials.skin, forearm, 0, -.38, 0);
      if (side < 0) { f.rightArm = arm; f.rightForearm = forearm; } else { f.leftArm = arm; f.leftForearm = forearm; }
    }
    f.head = new THREE.Group(); f.head.position.y = 2.17; f.body.add(f.head);
    this._cyl(.125, .13, .21, this.materials.skin, f.head, 0, -.05, 0, 8);
    const face = this._mesh(new THREE.SphereGeometry(.235, 10, 8), this.materials.skin, f.head, 0, .19, .015); face.scale.set(.86, 1.16, .9);
    const hair = this._mesh(new THREE.SphereGeometry(.244, 10, 8, 0, TAU, 0, Math.PI * .6), this.materials.hair, f.head, 0, .26, -.025); hair.rotation.x = -.15;
    this._mesh(new THREE.SphereGeometry(.105, 8, 6), this.materials.hair, f.head, 0, .53, -.03).scale.set(.8, 1.25, .8);
    this._cyl(.11, .11, .055, this.materials.gold, f.head, 0, .47, -.03, 8);
    this._box(.055, .025, .025, this.materials.hair, f.head, -.08, .21, .207);
    this._box(.055, .025, .025, this.materials.hair, f.head, .08, .21, .207);
    const nose = this._mesh(new THREE.ConeGeometry(.04, .1, 4), this.materials.skin, f.head, 0, .15, .225); nose.rotation.x = Math.PI / 2;
    this._cyl(.245, .245, .1, trim, f.head, 0, -.03, 0, 9);
    f.scarf = this._box(.2, .65, .035, trim, f.body, .21, 1.67, -.33); f.scarf.rotation.x = -.2;
    // The scabbard stays visible at the waist when the weapon is drawn.
    const sheath = this._box(.11, 1.15, .13, this.materials.black, f.body, .42, .83, -.2); sheath.rotation.z = -.42;
    this._equip(f, hero ? this.weapon : ['sword', 'blade', 'spear'][this.enemies.length % 3]);
    return f;
  }
  _equip(f, name) {
    f.weapon = name;
    if (f.weaponGroup) { if (this.originalSword?.parent === f.weaponGroup) f.weaponGroup.remove(this.originalSword); f.rightForearm.remove(f.weaponGroup); f.weaponGroup.traverse(o => o.geometry?.dispose()); }
    const g = new THREE.Group(); f.rightForearm.add(g); g.position.set(0, -.4, 0); g.rotation.x = -.45; f.weaponGroup = g;
    const steel = this._mat('steel', 0xc9dddd, .24, .88), bladeMat = this._mat('bladesteel', 0xb9d2d3, .25, .9);
    if (name === 'spear') {
      this._cyl(.035, .035, 2.9, this.materials.wood, g, 0, -.5, 0, 7);
      this._cyl(.043, .043, .25, this.materials.gold, g, 0, -1.95, 0, 7);
      this._mesh(new THREE.ConeGeometry(.105, .65, 4), steel, g, 0, -2.35, 0).rotation.z = Math.PI;
      const tassel = this._mesh(new THREE.ConeGeometry(.18, .46, 6), this._mat('tassel', 0xb34c40), g, 0, -1.95, 0); tassel.rotation.z = Math.PI;
      f.tipLength = 2.6;
    } else {
      this._cyl(.045, .045, .3, this.materials.wood, g, 0, .06, 0, 8);
      this._cyl(.065, .065, .06, this.materials.gold, g, 0, .25, 0, 8);
      this._box(name === 'blade' ? .4 : .31, .06, .1, this.materials.gold, g, 0, -.13, 0);
      if (name === 'blade') {
        const shape = new THREE.Shape(); shape.moveTo(-.065, 0); shape.lineTo(-.075, -1.14); shape.quadraticCurveTo(.2, -1.7, .24, -1.51); shape.lineTo(.25, -.36); shape.lineTo(.16, 0); shape.closePath();
        const mesh = this._mesh(new THREE.ExtrudeGeometry(shape, { depth: .045, bevelEnabled: true, bevelSize: .015, bevelThickness: .01, bevelSegments: 1, steps: 1 }), bladeMat, g, 0, -.16, -.025);
      } else {
        this._box(.13, 1.28, .045, steel, g, 0, -.8, 0);
        this._mesh(new THREE.ConeGeometry(.095, .24, 4), steel, g, 0, -1.55, 0).rotation.z = Math.PI;
        this._box(.018, 1.28, .05, this.materials.gold, g, 0, -.8, 0);
      }
      f.tipLength = name === 'blade' ? 1.8 : 1.7;
    }
    f.tip = new THREE.Object3D(); f.tip.position.y = -f.tipLength; g.add(f.tip);
    if (f.hero && name === 'sword' && this.originalSword) {
      for (const object of g.children) if (object.isMesh) object.visible = false;
      this.originalSword.rotation.x = Math.PI / 2; g.add(this.originalSword);
    }
  }
  _resetFighter(f, x, z, hp = 100) {
    f.root.position.set(x, this._groundHeight(x, z), z); f.hp = hp; f.maxHp = hp; f.stamina = 100;
    f.dead = false; f.respawn = 0; f.dodge = 0; f.attack = null; f.hit = 0; f.vy = 0; f.jump = 0;
    f.guard = false; f.velocity.set(0, 0, 0); f.root.rotation.z = 0; f.root.scale.setScalar(1); f.aiTimer = .8 + Math.random();
  }
  start({ map = 'sifang', weapon = 'sword', difficulty = 'normal' } = {}) {
    this._unlockAudio(); this.pointer = null;
    if (map !== this.map) this._buildWorld(map);
    this.weapon = WEAPONS[weapon] ? weapon : 'sword'; this.difficulty = difficulty;
    for (const e of this.enemies) this._disposeGroup(e.root);
    this.enemies = []; this._clearEffects(); this._resetFighter(this.hero, 0, map === 'sifang' ? 5.5 : 7, 100); this._equip(this.hero, this.weapon);
    this.hero.root.rotation.y = Math.PI; this.hero.rage = 0; this.hero.combo = 0;
    const positions = map === 'sifang' ? [[-4, -3], [4, -4], [0, -5.5]] : [[-6, -5], [7, -7], [1, -12]];
    const colors = [[0x763f3e, 0x292e35], [0x3e5357, 0x9b8c65], [0x5e5571, 0x262e3a]];
    for (let i = 0; i < 3; i++) {
      const f = this._fighter(colors[i][0], colors[i][1]); f.name = ['萧无名', '冷燕', '铁卫'][i]; f.id = i;
      this._resetFighter(f, ...positions[i], difficulty === 'hard' ? 115 : 90); this.scene.add(f.root); this.enemies.push(f);
      this._nameplate(f);
      f.root.rotation.y = Math.atan2(-positions[i][0], 7 - positions[i][1]);
    }
    this.running = true; this.paused = false; this.time = 180; this.kills = 0; this.deaths = 0; this.totalDamage = 0; this.matchElapsed = 0;
    this.locked = null; this.keys.clear(); this.cameraAngle = 0; this.cameraPitch = .48; this.cameraDistance = 10;
    this.cameraTarget.copy(this.hero.root.position); this.camera.position.set(0, 6, 17);
    this._emit('试炼开始 · 击败五名对手', 'info'); this._hud();
  }
  menu(map) {
    this.running = false; this.paused = false; this.keys.clear(); this.locked = null; this.pointer = null;
    for (const e of this.enemies) this._disposeGroup(e.root);
    this.enemies = []; this._clearEffects();
    if (map && map !== this.map) this._buildWorld(map);
    this._resetFighter(this.hero, 3, 2, 100); this.hero.root.rotation.y = -.45; this.hero.root.scale.setScalar(1.38);
    this._equip(this.hero, this.weapon);
  }
  pause(value = true) {
    this.paused = !!value; this.keys.clear(); this.hero.guard = false; this.pointer = null;
    if (this.audio?.state === 'running' && value) this.audio.suspend(); else if (!value) this.audio?.resume();
    this._hud();
  }
  setWeapon(weapon) {
    if (!WEAPONS[weapon]) return; this.weapon = weapon; this._equip(this.hero, weapon);
    if (this.running) { this._emit(`已切换 · ${WEAPONS[weapon].name}`, 'info'); this._hud(); }
  }
  setMuted(value) { this.muted = !!value; if (this.master) this.master.gain.value = this.muted ? 0 : .35; }
  setQuality(value) {
    this.quality = value; this.renderer.setPixelRatio(Math.min(devicePixelRatio || 1, value === 'low' ? 1 : 1.75));
    this.renderer.shadowMap.enabled = value !== 'low'; this.resize();
  }
  action(name, active = true) {
    if (['forward', 'back', 'left', 'right'].includes(name)) { if (active && this.running && !this.paused) this.keys.add(name); else this.keys.delete(name); return; }
    if (name === 'guard') { this.hero.guard = active && this.running && !this.paused && !this.hero.dead && this.hero.stamina > 5; return; }
    if (!active || !this.running || this.paused || this.hero.dead) return;
    this._unlockAudio();
    if (name === 'attack') this._beginAttack(this.hero);
    else if (name === 'dodge') this._dodge();
    else if (name === 'jump' && this.hero.jump <= .01) { this.hero.vy = 8.8; this.hero.jump = .01; this._sound('step'); }
    else if (name === 'lock') { this.locked = this.locked ? null : this._nearest(); this._emit(this.locked ? `锁定 · ${this.locked.name}` : '解除锁定', 'info'); this._hud(); }
    else if (name === 'fury') this._fury();
    else if (name === 'weapon1' || name === 'sword') this.setWeapon('sword');
    else if (name === 'weapon2' || name === 'blade') this.setWeapon('blade');
    else if (name === 'weapon3' || name === 'spear') this.setWeapon('spear');
  }
  _bind() {
    const bind = (el, event, fn, opts) => { el.addEventListener(event, fn, opts); this._listeners.push(() => el.removeEventListener(event, fn, opts)); };
    const map = { KeyW: 'forward', ArrowUp: 'forward', KeyS: 'back', ArrowDown: 'back', KeyA: 'left', ArrowLeft: 'left', KeyD: 'right', ArrowRight: 'right', KeyJ: 'attack', KeyK: 'guard', ShiftLeft: 'dodge', ShiftRight: 'dodge', KeyL: 'dodge', Space: 'jump', KeyQ: 'lock', KeyE: 'fury', Digit1: 'weapon1', Digit2: 'weapon2', Digit3: 'weapon3' };
    bind(window, 'keydown', e => { if (this.paused || document.querySelector('dialog[open]') || /INPUT|TEXTAREA|SELECT/.test(document.activeElement?.tagName)) return; const a = map[e.code]; if (!a || !this.running) return; e.preventDefault(); if (!e.repeat || ['forward', 'back', 'left', 'right', 'guard'].includes(a)) this.action(a, true); });
    bind(window, 'keyup', e => { const a = map[e.code]; if (a) this.action(a, false); });
    bind(window, 'blur', () => { this.keys.clear(); this.hero.guard = false; this.pointer = null; });
    bind(this.canvas, 'contextmenu', e => e.preventDefault());
    this.pointer = null;
    bind(this.canvas, 'pointerdown', e => {
      this._unlockAudio(); this.pointer = { x: e.clientX, y: e.clientY, startX: e.clientX, startY: e.clientY, button: e.button, moved: false };
      this.canvas.setPointerCapture?.(e.pointerId);
      if (e.button === 2) this.action('guard', true);
    });
    bind(this.canvas, 'pointermove', e => {
      if (!this.pointer) return;
      const dx = e.clientX - this.pointer.x, dy = e.clientY - this.pointer.y;
      if (Math.hypot(e.clientX - this.pointer.startX, e.clientY - this.pointer.startY) > 5) this.pointer.moved = true;
      if (this.pointer.moved && this.running && !this.paused) { this.cameraAngle -= dx * .005; this.cameraPitch = clamp(this.cameraPitch + dy * .003, .22, .95); }
      this.pointer.x = e.clientX; this.pointer.y = e.clientY;
    });
    bind(this.canvas, 'pointerup', e => { if (this.pointer && !this.pointer.moved && this.pointer.button === 0) this.action('attack'); if (e.button === 2) this.action('guard', false); this.pointer = null; });
    bind(this.canvas, 'pointercancel', () => { this.pointer = null; this.action('guard', false); });
    bind(this.canvas, 'lostpointercapture', () => { this.pointer = null; this.action('guard', false); });
    bind(this.canvas, 'wheel', e => { if (!this.running) return; e.preventDefault(); this.cameraDistance = clamp(this.cameraDistance + e.deltaY * .008, 6, 15); }, { passive: false });
    bind(window, 'resize', () => this.resize());
  }
  resize() {
    const w = this.canvas.clientWidth || window.innerWidth, h = this.canvas.clientHeight || window.innerHeight;
    this.renderer.setSize(w, h, false); this.camera.aspect = w / Math.max(1, h); this.camera.updateProjectionMatrix();
  }

  _nearest(range = Infinity) {
    let best = null, distance = range;
    for (const e of this.enemies) { if (e.dead) continue; const d = e.root.position.distanceTo(this.hero.root.position); if (d < distance) { best = e; distance = d; } }
    return best;
  }
  _face(f, target, dt = 1) {
    const p = f.root.position, angle = Math.atan2(target.x - p.x, target.z - p.z);
    f.root.rotation.y += Math.atan2(Math.sin(angle - f.root.rotation.y), Math.cos(angle - f.root.rotation.y)) * Math.min(1, dt * 12);
  }
  _beginAttack(f) {
    if (f.dead || f.dodge > 0 || f.attackCooldown > 0 || f.stamina < 8) return;
    if (f.attack) { if (f.attack.t > .16) f.attack.queued = true; return; }
    f.guard = false; f.stamina = Math.max(0, f.stamina - (f.weapon === 'blade' ? 15 : 10));
    const combo = f.comboTimer > 0 ? (f.combo % 3) + 1 : 1; f.combo = combo; f.comboTimer = 1.1;
    const spec = WEAPONS[f.weapon];
    f.attack = { t: 0, duration: spec.duration * (combo === 3 ? 1.15 : 1), hit: false, queued: false, combo };
    if (f.hero) {
      const aim = this.locked && !this.locked.dead ? this.locked : this._nearest(spec.reach + 1.3);
      if (aim) this._face(f, aim.root.position);
    }
    this._sound('swing', combo === 3 ? .8 : 1);
  }
  _dodge() {
    const f = this.hero; if (f.dodge > 0 || f.stamina < 24 || f.attack || f.jump > .3) return;
    f.guard = false; f.stamina -= 24; f.dodge = .43; f.invuln = .37;
    const dir = this._moveDirection();
    f.dodgeDir = dir.lengthSq() > .01 ? dir : new THREE.Vector3(Math.sin(f.root.rotation.y), 0, Math.cos(f.root.rotation.y));
    this._sound('dodge');
  }
  _fury() {
    const f = this.hero;
    if (f.rage < 100) { this._emit('怒气不足 · 命中敌人积攒怒气', 'info'); return; }
    if (f.attack || f.dodge > 0) return;
    f.rage = 0; f.invuln = 1.1; f.attack = { t: 0, duration: .95, hit: false, queued: false, combo: 3, fury: true };
    this._emit('绝学 · 流星破空', 'info'); this._sound('fury');
    for (let i = 0; i < 3; i++) {
      const ring = this._mesh(new THREE.TorusGeometry(1.1 + i * .5, .04, 5, 70), new THREE.MeshBasicMaterial({ color: 0xe5c58b, transparent: true, opacity: .8 }), this.scene, f.root.position.x, .3 + i * .35, f.root.position.z, false);
      ring.rotation.x = Math.PI / 2; this.effects.push({ mesh: ring, life: .85, max: .85, expand: 6 });
    }
  }
  _moveDirection() {
    const x = (this.keys.has('right') ? 1 : 0) - (this.keys.has('left') ? 1 : 0);
    const z = (this.keys.has('forward') ? 1 : 0) - (this.keys.has('back') ? 1 : 0);
    const a = this.cameraAngle;
    return new THREE.Vector3(Math.cos(a) * x - Math.sin(a) * z, 0, -Math.sin(a) * x - Math.cos(a) * z).normalize();
  }
  _move(f, dir, speed, dt) {
    if (dir.lengthSq() < .001) { f.velocity.multiplyScalar(Math.exp(-dt * 14)); return; }
    const desired = dir.clone().multiplyScalar(speed), blend = 1 - Math.exp(-dt * 15);
    f.velocity.lerp(desired, blend); f.root.position.addScaledVector(f.velocity, dt);
    const bound = this.map === 'sifang' ? 6.4 : 16.7; f.root.position.x = clamp(f.root.position.x, -bound, bound); f.root.position.z = clamp(f.root.position.z, -bound, bound);
    for (const c of this.collision) {
      const dx = f.root.position.x - c.x, dz = f.root.position.z - c.z, d = Math.hypot(dx, dz), min = c.r + .42;
      if (d < min && d > .001) { f.root.position.x = c.x + dx / d * min; f.root.position.z = c.z + dz / d * min; }
    }
    f.walk += dt * speed * 2;
    f.root.position.y = this._groundHeight(f.root.position.x, f.root.position.z) + f.jump;
  }
  _tickHero(dt) {
    const f = this.hero;
    if (f.dead) {
      f.respawn -= dt; if (f.respawn <= 0) { this._resetFighter(f, 0, this.map === 'sifang' ? 5.5 : 12, 100); f.rage = Math.max(0, f.rage - 20); f.invuln = 2; this._emit('重返战场', 'info'); } return;
    }
    let dir = this._moveDirection(), speed = 5.9;
    if (f.guard) { speed = 2.2; f.stamina = Math.max(0, f.stamina - dt * 6); if (f.stamina <= 0) f.guard = false; }
    if (f.attack) speed *= .28;
    if (f.dodge > 0) { dir = f.dodgeDir; speed = 15 * Math.max(.4, f.dodge / .43); f.dodge -= dt; }
    else if (this.locked && !this.locked.dead) this._face(f, this.locked.root.position, dt);
    else if (dir.lengthSq() > .001 && !f.attack) this._face(f, f.root.position.clone().add(dir), dt);
    this._move(f, dir, speed, dt);
    if (f.jump > 0 || f.vy > 0) { f.vy -= dt * 23; f.jump += f.vy * dt; if (f.jump <= 0) { f.jump = 0; f.vy = 0; this._sound('step'); } }
    f.root.position.y = this._groundHeight(f.root.position.x, f.root.position.z) + f.jump;
    f.stamina = Math.min(100, f.stamina + dt * (f.guard ? 0 : f.attack || f.dodge > 0 ? 3 : 20));
    if (dir.lengthSq() > 0 && f.jump === 0 && f.dodge <= 0) { f.stepTimer = (f.stepTimer || 0) - dt; if (f.stepTimer < 0) { this._sound('step', .6); f.stepTimer = .3; } }
  }
  _tickEnemy(f, dt) {
    if (f.dead) {
      f.respawn -= dt;
      if (f.respawn <= 0) {
        const a = Math.random() * TAU, radius = this.map === 'sifang' ? 5.5 : 13; this._resetFighter(f, Math.sin(a) * radius, Math.cos(a) * radius, this.difficulty === 'hard' ? 115 : 90); f.invuln = .6;
      }
      return;
    }
    f.aiTimer -= dt; f.stamina = Math.min(100, f.stamina + dt * 13);
    const delta = this.hero.root.position.clone().sub(f.root.position); delta.y = 0; const distance = delta.length();
    if (this.hero.dead) {
      const target = new THREE.Vector3(Math.sin(this.elapsed * .13 + f.id * 2) * 7, 0, Math.cos(this.elapsed * .13 + f.id * 2) * 7);
      const dir = target.sub(f.root.position); dir.y = 0; dir.normalize(); this._move(f, dir, 1.7, dt); this._face(f, f.root.position.clone().add(dir), dt); return;
    }
    this._face(f, this.hero.root.position, dt);
    const reach = WEAPONS[f.weapon].reach * .78;
    let dir = new THREE.Vector3(), speed = this.difficulty === 'hard' ? 2.8 : 2.3;
    if (!f.attack && distance > reach) {
      dir.copy(delta).normalize();
      // Circling avoids a single stack of opponents and leaves room to read attacks.
      if (distance < 6) { const side = f.id % 2 ? 1 : -1; dir.add(new THREE.Vector3(-dir.z, 0, dir.x).multiplyScalar(side * .36)); dir.normalize(); }
    } else if (!f.attack && distance < 1.5) { dir.copy(delta).normalize().negate(); speed *= .65; }
    this._move(f, dir, speed, dt);
    // Other combatants have physical space; the three AIs coordinate naturally.
    for (const other of this.enemies) {
      if (other === f || other.dead) continue; const push = f.root.position.clone().sub(other.root.position); push.y = 0; const d = push.length();
      if (d > .01 && d < 1.25) f.root.position.addScaledVector(push.normalize(), (1.25 - d) * dt * 3);
    }
    if (distance < reach + .25 && f.aiTimer <= 0 && !f.attack) {
      this._beginAttack(f); f.aiTimer = (this.difficulty === 'hard' ? .65 : 1.05) + Math.random() * .8 + f.id * .13;
    }
    f.guard = !f.attack && this.hero.attack && distance < 4 && (Math.floor(this.elapsed * 1.5 + f.id) % 5 === 0);
  }
  _tickFighter(f, dt) {
    f.hit = Math.max(0, f.hit - dt); f.invuln = Math.max(0, (f.invuln || 0) - dt);
    f.attackCooldown = Math.max(0, f.attackCooldown - dt); f.comboTimer = Math.max(0, f.comboTimer - dt);
    if (f.dead) {
      f.body.rotation.z = mix(f.body.rotation.z, Math.PI / 2, Math.min(1, dt * 8)); f.body.position.y = mix(f.body.position.y, -.55, Math.min(1, dt * 8));
      f.root.visible = f.respawn > 1; return;
    }
    f.root.visible = true; f.body.rotation.z = mix(f.body.rotation.z, 0, Math.min(1, dt * 10)); f.body.position.y = 0;
    const moving = f.velocity.length() > .3, stride = moving ? Math.sin(f.walk) * .65 : Math.sin(this.elapsed * 1.8 + (f.id || 0)) * .035;
    f.leftLeg.rotation.x = stride; f.rightLeg.rotation.x = -stride;
    f.leftCalf.rotation.x = Math.max(0, -stride) * .65; f.rightCalf.rotation.x = Math.max(0, stride) * .65;
    f.body.position.y = moving ? Math.abs(Math.sin(f.walk)) * .055 : Math.sin(this.elapsed * 2) * .015;
    f.body.rotation.x = f.dodge > 0 ? -.65 : 0;
    f.leftArm.rotation.set(-stride * .45, 0, -.1); f.rightArm.rotation.set(stride * .3, 0, .12);
    f.leftForearm.rotation.x = -.15; f.rightForearm.rotation.x = -.1;
    if (f.guard) {
      f.rightArm.rotation.set(-1.25, -.35, -.2); f.rightForearm.rotation.x = -.65;
      f.leftArm.rotation.set(-1.25, .4, .2); f.leftForearm.rotation.x = -.7;
    }
    if (f.attack) {
      const attack = f.attack; attack.t += dt; const p = clamp(attack.t / attack.duration, 0, 1);
      const swing = Math.sin(p * Math.PI), side = attack.combo % 2 ? 1 : -1;
      f.rightArm.rotation.set(-1.15 - swing * .65, side * (1.3 - p * 2.7), side * (.8 - p * 1.8));
      f.rightForearm.rotation.x = -.15 - swing * .5;
      f.leftArm.rotation.x = -.35 - swing * .6; f.body.rotation.y = side * Math.sin(p * TAU) * .38;
      if (attack.fury) { f.body.rotation.y = p * TAU * 2; f.rightArm.rotation.z = -1.5; }
      const hitAt = attack.fury ? .35 : .34;
      if (!attack.hit && p > hitAt) { attack.hit = true; this._resolveAttack(f, attack); this._slash(f, attack); }
      if (p >= 1) {
        const queued = attack.queued; f.attack = null; f.body.rotation.y = 0; f.comboTimer = .8;
        if (f.hero && queued && attack.combo < 3) this._beginAttack(f);
        else if (attack.combo === 3 || !f.hero) f.attackCooldown = f.hero ? .13 : .4;
      }
    } else f.body.rotation.y = mix(f.body.rotation.y, 0, Math.min(1, dt * 10));
    f.scarf.rotation.x = -.28 + Math.sin(this.elapsed * 4 + f.walk) * .18 - (moving ? .5 : 0);
    f.cloth.emissive.setHex(f.hit > 0 ? 0x7f332b : f.invuln > 0 && f.hero ? 0x253c45 : 0x000000);
    f.cloth.emissiveIntensity = f.hit > 0 ? .65 : .25;
    if (f.healthFill) {
      f.healthFill.scale.x = Math.max(.01, f.hp / f.maxHp); f.healthFill.position.x = -(1 - f.hp / f.maxHp) * .45;
      f.nameplate.quaternion.copy(f.root.quaternion).invert().multiply(this.camera.quaternion); f.nameplate.visible = this.running && !f.dead;
    }
  }
  _resolveAttack(attacker, attack) {
    if (!this.running) return;
    const spec = WEAPONS[attacker.weapon], targets = attacker.hero ? this.enemies : [this.hero];
    const fury = !!attack.fury, reach = fury ? 7 : spec.reach;
    for (const target of targets) {
      if (!this.running) break;
      if (target.dead || target.invuln > 0) continue;
      const delta = target.root.position.clone().sub(attacker.root.position); delta.y = 0;
      const distance = delta.length(); if (distance > reach || Math.abs(target.root.position.y - attacker.root.position.y) > 1.9) continue;
      const forward = new THREE.Vector3(Math.sin(attacker.root.rotation.y), 0, Math.cos(attacker.root.rotation.y));
      if (!fury && forward.dot(delta.clone().normalize()) < (attacker.weapon === 'spear' ? .64 : -.05)) continue;
      let damage = Math.round((attacker.hero ? spec.damage : this.difficulty === 'hard' ? 17 : 11) * (attack.combo === 3 ? 1.55 : attack.combo === 2 ? 1.16 : 1));
      if (fury) damage = 62;
      const targetFacing = new THREE.Vector3(Math.sin(target.root.rotation.y), 0, Math.cos(target.root.rotation.y));
      const guarding = target.guard && targetFacing.dot(delta.clone().normalize().negate()) > -.1;
      if (guarding) {
        const cost = damage * 1.25;
        if (target.stamina >= cost) { target.stamina -= cost; damage = Math.max(1, Math.round(damage * .12)); this._emit(target.hero ? '格挡' : '对手格挡', 'hit'); this._sound('guard'); }
        else { target.stamina = 0; target.guard = false; this._emit(target.hero ? '架势崩溃' : '破防', 'info'); }
      }
      target.hp = Math.max(0, target.hp - damage); target.hit = .19;
      if (attacker.hero) { this.totalDamage += damage; attacker.rage = Math.min(100, attacker.rage + (guarding ? 4 : 12)); }
      else this.hero.rage = Math.min(100, this.hero.rage + 6);
      const hitPoint = target.root.position.clone().add(new THREE.Vector3(0, 1.45, 0)); this._sparks(hitPoint, guarding ? 0xe9cd87 : 0xcfae86, 12);
      this._sound(guarding ? 'guard' : 'hit');
      if (attacker.hero) this._emit(`${damage}`, 'hit', damage, hitPoint);
      else { this._emit(`−${damage}`, 'hit', -damage, hitPoint); this.cameraShake = .14; }
      // A small physical recoil keeps weight without taking away control.
      const knock = delta.normalize().multiplyScalar(fury ? 1.2 : guarding ? .05 : .25); target.root.position.add(knock);
      if (target.hp <= 0) this._kill(target, attacker);
    }
    this._hud();
  }
  _kill(target, attacker) {
    target.dead = true; target.guard = false; target.attack = null; target.respawn = target.hero ? 3 : 3.6; target.velocity.set(0, 0, 0);
    if (target.hero) { this.deaths++; this._emit('胜败乃兵家常事 · 三息后重返战场', 'info'); }
    else { this.kills++; this._emit(`击败 ${target.name}`, 'kill'); this.hero.hp = Math.min(100, this.hero.hp + 16); this.hero.stamina = Math.min(100, this.hero.stamina + 25); }
    if (this.locked === target) this.locked = null;
    if (this.kills >= 5 || this.deaths >= 5) this._finish(this.kills >= 5);
  }
  _finish(win) {
    if (!this.running) return;
    this.running = false; this.keys.clear();
    for (const f of [this.hero, ...this.enemies]) { f.attack = null; f.guard = false; f.velocity.set(0, 0, 0); }
    const result = { win, kills: this.kills, deaths: this.deaths, damage: this.totalDamage, time: Math.round(this.matchElapsed) };
    this._hud(); this.onEnd(result);
  }
  _slash(f, attack) {
    const color = attack.fury ? 0xf5d391 : f.hero ? 0xd4eee9 : 0xe49b7c;
    const reach = WEAPONS[f.weapon].reach * .65;
    const mesh = this._mesh(new THREE.TorusGeometry(reach, attack.combo === 3 ? .055 : .032, 4, 40, Math.PI * 1.25), new THREE.MeshBasicMaterial({ color, transparent: true, opacity: .9, depthWrite: false }), this.scene, f.root.position.x, 1.4 + f.root.position.y, f.root.position.z, false);
    mesh.rotation.set(Math.PI / 2 + (attack.combo === 3 ? .35 : -.15), 0, -f.root.rotation.y - Math.PI * .15);
    this.effects.push({ mesh, life: .23, max: .23 });
  }
  _sparks(position, color, count = 12) {
    const geometry = new THREE.SphereGeometry(.035, 4, 3), material = new THREE.MeshBasicMaterial({ color, transparent: true, opacity: 1 });
    const batch = { geometry, material, remaining: count };
    for (let i = 0; i < count; i++) {
      const mesh = new THREE.Mesh(geometry, material); mesh.position.copy(position); this.scene.add(mesh);
      this.particles.push({ mesh, batch, velocity: new THREE.Vector3((Math.random() - .5) * 7, Math.random() * 5, (Math.random() - .5) * 7), life: .3 + Math.random() * .3, max: .6 });
    }
  }
  _clearEffects() {
    for (const e of this.effects) { this.scene.remove(e.mesh); e.mesh.geometry.dispose(); e.mesh.material.dispose(); }
    for (const p of this.particles) { this.scene.remove(p.mesh); if (--p.batch.remaining === 0) { p.batch.geometry.dispose(); p.batch.material.dispose(); } }
    this.effects = []; this.particles = [];
  }
  _tickEffects(dt) {
    for (let i = this.effects.length - 1; i >= 0; i--) {
      const e = this.effects[i]; e.life -= dt; e.mesh.material.opacity = Math.max(0, e.life / e.max * .9);
      if (e.expand) e.mesh.scale.addScalar(dt * e.expand);
      if (e.life <= 0) { this.scene.remove(e.mesh); e.mesh.geometry.dispose(); e.mesh.material.dispose(); this.effects.splice(i, 1); }
    }
    for (let i = this.particles.length - 1; i >= 0; i--) {
      const p = this.particles[i]; p.life -= dt; p.velocity.y -= dt * 10; p.mesh.position.addScaledVector(p.velocity, dt); p.mesh.scale.setScalar(Math.max(.05, p.life / p.max));
      if (p.life <= 0) { this.scene.remove(p.mesh); if (--p.batch.remaining === 0) { p.batch.geometry.dispose(); p.batch.material.dispose(); } this.particles.splice(i, 1); }
    }
  }
  _nameplate(f) {
    const g = new THREE.Group(); f.root.add(g); g.position.y = 3.05; f.nameplate = g;
    this._box(.98, .09, .025, new THREE.MeshBasicMaterial({ color: 0x10191c, transparent: true, opacity: .85 }), g, 0, 0, 0, false);
    f.healthFill = this._box(.9, .045, .03, new THREE.MeshBasicMaterial({ color: 0xb86a58 }), g, 0, 0, .02, false);
    const c = document.createElement('canvas'); c.width = 256; c.height = 64; const ctx = c.getContext('2d'); ctx.fillStyle = '#ddd5b9'; ctx.textAlign = 'center'; ctx.font = '28px serif'; ctx.fillText(f.name, 128, 42);
    const texture = new THREE.CanvasTexture(c);
    this._mesh(new THREE.PlaneGeometry(1.5, .375), new THREE.MeshBasicMaterial({ map: texture, transparent: true, depthWrite: false }), g, 0, .25, 0, false);
  }
  _emit(text, type = 'info', amount, point) {
    let x, y;
    if (point) { const p = point.clone().project(this.camera); x = (p.x + 1) * .5; y = (-p.y + 1) * .5; }
    this.onEvent({ text, type, amount, x, y });
  }
  _hud() {
    const f = this.hero, e = this.locked && !this.locked.dead ? this.locked : this.running ? this._nearest(12) : null;
    this.onUpdate({ hp: f.hp, maxHp: f.maxHp, stamina: f.stamina, rage: f.rage, kills: this.kills || 0, deaths: this.deaths || 0, time: this.time ?? 180, enemy: e ? { name: e.name, hp: e.hp, maxHp: e.maxHp } : null, combo: f.comboTimer > 0 ? f.combo : 0, locked: !!this.locked, position: { x: f.root.position.x, z: f.root.position.z }, enemies: this.enemies.filter(e => !e.dead).map(e => ({ x: e.root.position.x, z: e.root.position.z })), weapon: this.weapon, paused: this.paused });
  }
  _tickCamera(dt) {
    if (!this.running && !this.paused) {
      const t = this.elapsed * .045;
      const ground = this.originalMap ? this._groundHeight(3.5, 2) : 0;
      const desired = this.originalMap ? new THREE.Vector3(7.5 + Math.sin(t) * .4, 5.5 + ground, 11) : new THREE.Vector3(11.8 + Math.sin(t) * 1.3, 6.3 + ground, 15.5 + Math.cos(t) * .7);
      this.camera.position.lerp(desired, 1 - Math.exp(-dt * 1.8)); this.camera.lookAt(-1.3, 2.1 + ground, 1);
      return;
    }
    const p = this.hero.root.position;
    const target = p.clone().add(new THREE.Vector3(0, 1.45, 0));
    this.cameraTarget.lerp(target, 1 - Math.exp(-dt * 8));
    const distance = this.cameraDistance, height = Math.sin(this.cameraPitch) * distance + 1.8;
    const offset = new THREE.Vector3(Math.sin(this.cameraAngle) * distance, height, Math.cos(this.cameraAngle) * distance);
    const cameraPos = this.cameraTarget.clone().add(offset);
    if (this.originalMap) {
      const direction = cameraPos.clone().sub(this.cameraTarget), distance = direction.length(); direction.normalize();
      this.raycaster.set(this.cameraTarget, direction);
      const obstruction = this.raycaster.intersectObjects(this.groundMeshes, false).find(h => h.distance < distance);
      if (obstruction) cameraPos.copy(this.cameraTarget).addScaledVector(direction, Math.max(2.7, obstruction.distance - .65));
    }
    if (this.cameraShake > 0) { this.cameraShake -= dt; cameraPos.x += (Math.random() - .5) * this.cameraShake * 2; cameraPos.y += (Math.random() - .5) * this.cameraShake; }
    this.camera.position.lerp(cameraPos, 1 - Math.exp(-dt * 9)); this.camera.lookAt(this.cameraTarget);
    this.heroLight.position.copy(p).add(new THREE.Vector3(2, 5, 3));
  }
  _frame() {
    if (this.disposed) return;
    this.raf = requestAnimationFrame(this._frame);
    const dt = Math.min(.045, this.clock.getDelta()); this.elapsed += dt;
    if (!this.paused) {
      if (this.running) {
        this.time = Math.max(0, this.time - dt); this.matchElapsed += dt;
        this._tickHero(dt); for (const e of this.enemies) this._tickEnemy(e, dt);
        for (const f of [this.hero, ...this.enemies]) { if (!this.running) break; this._tickFighter(f, dt); }
        if (this.time <= 0) this._finish(this.kills > this.deaths);
        this.updateAccum += dt; if (this.updateAccum > .08) { this.updateAccum = 0; this._hud(); }
      } else if (this.hero) {
        this.hero.velocity.set(0, 0, 0); this._tickFighter(this.hero, dt);
        if (!this.hero.dead) { this.hero.rightArm.rotation.set(-.35, -.25, .08); this.hero.leftArm.rotation.set(.05, 0, -.15); }
      }
      this._tickEffects(dt);
      for (const p of this.petals || []) {
        p.mesh.position.x += dt * (.25 + Math.sin(this.elapsed + p.phase) * .3); p.mesh.position.y -= dt * p.speed * (this.map === 'forge' ? -1 : 1); p.mesh.rotation.z += dt * .4;
        if (p.mesh.position.y < .2) p.mesh.position.y = 10; if (p.mesh.position.y > 13) p.mesh.position.y = .5;
        if (p.mesh.position.x > 20) p.mesh.position.x = -20;
      }
      for (let i = 0; i < (this.mists?.length || 0); i++) this.mists[i].position.x += Math.sin(this.elapsed * .1 + i) * dt * .12;
    }
    this._tickCamera(dt); this.renderer.render(this.scene, this.camera);
  }
  _unlockAudio() {
    if (this.muted) return;
    try {
      if (!this.audio) {
        this.audio = new (window.AudioContext || window.webkitAudioContext)(); this.master = this.audio.createGain(); this.master.gain.value = .35; this.master.connect(this.audio.destination);
      }
      if (this.audio.state === 'suspended') this.audio.resume();
    } catch (_) { /* Browsers without Web Audio still have fully playable combat. */ }
  }
  _sound(type, pitch = 1) {
    if (!this.audio || this.muted || this.paused) return;
    const ctx = this.audio, now = ctx.currentTime;
    try {
      const gain = ctx.createGain(); gain.connect(this.master);
      if (type === 'swing' || type === 'dodge' || type === 'step' || type === 'hit') {
        const duration = type === 'step' ? .07 : type === 'hit' ? .12 : .23;
        const buffer = ctx.createBuffer(1, Math.ceil(ctx.sampleRate * duration), ctx.sampleRate), data = buffer.getChannelData(0);
        for (let i = 0; i < data.length; i++) data[i] = (Math.random() * 2 - 1) * Math.pow(1 - i / data.length, type === 'hit' ? 3 : 1.5);
        const noise = ctx.createBufferSource(); noise.buffer = buffer;
        const filter = ctx.createBiquadFilter(); filter.type = type === 'swing' ? 'bandpass' : 'lowpass'; filter.frequency.setValueAtTime(type === 'step' ? 450 : type === 'hit' ? 1000 : 1800 * pitch, now); filter.Q.value = .65;
        noise.connect(filter); filter.connect(gain); gain.gain.setValueAtTime(type === 'step' ? .12 : type === 'hit' ? .35 : .22, now); gain.gain.exponentialRampToValueAtTime(.001, now + duration); noise.start(now); noise.stop(now + duration); noise.onended = () => { gain.disconnect(); filter.disconnect(); };
      } else {
        const osc = ctx.createOscillator(); osc.type = type === 'guard' ? 'triangle' : 'sine'; osc.frequency.setValueAtTime(type === 'guard' ? 780 : 160, now); osc.frequency.exponentialRampToValueAtTime(type === 'guard' ? 300 : 55, now + .3); gain.gain.setValueAtTime(type === 'guard' ? .18 : .4, now); gain.gain.exponentialRampToValueAtTime(.001, now + .5); osc.connect(gain); osc.start(now); osc.stop(now + .5); osc.onended = () => gain.disconnect();
      }
    } catch (_) { /* Sound is optional; a suspended device must never halt the render loop. */ }
  }
  dispose() {
    this.disposed = true; cancelAnimationFrame(this.raf); for (const fn of this._listeners) fn();
    this._clearEffects(); this.scene.traverse(o => { o.geometry?.dispose(); if (o.material) for (const m of Array.isArray(o.material) ? o.material : [o.material]) { m.map?.dispose(); m.dispose(); } });
    if (this.originalSword && !this.originalSword.parent) this._disposeGroup(this.originalSword);
    this.renderer.dispose(); this.audio?.close();
  }
}
