import * as THREE from './vendor/three.module.js';

// 月蝶剑特效层（纯表现，不参与判定）
// 三件事：挥剑留下的剑光轨迹、绕剑飞舞的蝶群、命中瞬间的冰环与蝶爆。
// 全部使用加法混合 + 顶点色/纯色几何，不依赖贴图和后期 Bloom，
// 所以在当前 NoToneMapping、无 EffectComposer 的渲染管线里也能出光。
const TRAIL_LIFE = .26;
const TRAIL_MAX = 26;
const HOT = new THREE.Color(0xd8fbff);
const COOL = new THREE.Color(0x2fa8dc);
const BUTTERFLY_TINT = 0xbdf0ff;

function makeButterflyGeometry() {
  const wing = new THREE.Shape();
  wing.moveTo(0, 0);
  wing.bezierCurveTo(.09, .2, .3, .27, .44, .16);
  wing.bezierCurveTo(.53, .07, .48, -.09, .27, -.14);
  wing.bezierCurveTo(.13, -.17, .03, -.1, 0, 0);
  return new THREE.ShapeGeometry(wing, 6);
}

function makeButterfly(tint, scale) {
  const geometry = makeButterflyGeometry();
  const material = new THREE.MeshBasicMaterial({ color: tint, transparent: true, opacity: .9, blending: THREE.AdditiveBlending,
    depthWrite: false, side: THREE.DoubleSide, toneMapped: false });
  const group = new THREE.Group();
  const left = new THREE.Mesh(geometry, material), right = new THREE.Mesh(geometry, material);
  right.scale.x = -1;
  group.add(left, right);
  group.scale.setScalar(scale);
  return { group, left, right, material };
}

export class ButterflySwordVfx {
  constructor(scene, { quality = 'high' } = {}) {
    this.scene = scene; this.quality = quality;
    this.sword = null; this.enabled = true; this.time = 0;
    this.samples = []; this.bursts = [];
    this.butterflies = []; this.lastTip = new THREE.Vector3(); this.hasLastTip = false;
    this._v = new THREE.Vector3();

    // 剑光：一条随采样生成的条带，宽度就是刃长（从握把到剑尖扫过的面积）。
    this.trailGeometry = new THREE.BufferGeometry();
    this.trailPositions = new Float32Array(TRAIL_MAX * 2 * 3);
    this.trailColors = new Float32Array(TRAIL_MAX * 2 * 3);
    this.trailGeometry.setAttribute('position', new THREE.BufferAttribute(this.trailPositions, 3));
    this.trailGeometry.setAttribute('color', new THREE.BufferAttribute(this.trailColors, 3));
    const index = [];
    for (let i = 0; i < TRAIL_MAX - 1; i++) { const a = i * 2, b = a + 1, c = a + 2, d = a + 3; index.push(a, c, b, b, c, d); }
    this.trailGeometry.setIndex(index);
    this.trailMaterial = new THREE.MeshBasicMaterial({ vertexColors: true, transparent: true, opacity: .6,
      blending: THREE.AdditiveBlending, depthWrite: false, side: THREE.DoubleSide, toneMapped: false });
    this.trailMesh = new THREE.Mesh(this.trailGeometry, this.trailMaterial);
    this.trailMesh.frustumCulled = false; this.trailMesh.renderOrder = 6; this.trailMesh.visible = false;
    this.scene.add(this.trailMesh);
    this.trailGeometry.setDrawRange(0, 0);

    const count = this.quality === 'low' ? 4 : 9;
    for (let i = 0; i < count; i++) {
      const b = makeButterfly(BUTTERFLY_TINT, .07 + (i % 3) * .018);
      const angle = i / count * Math.PI * 2;
      b.orbit = { radius: .5 + (i % 4) * .16, speed: .5 + (i % 5) * .12, phase: angle, z: -2.2 + (i % 6) * 1.15, lift: .12 + (i % 3) * .1 };
      b.material.opacity = 0;
      b.group.visible = false;
      this.scene.add(b.group);
      this.butterflies.push(b);
    }
  }

  bind(sword, { tipLocal = [0, 0, 20.05], baseLocal = [0, 0, 1.4] } = {}) {
    this.sword = sword || null;
    this.tipLocal = new THREE.Vector3(...tipLocal);
    this.baseLocal = new THREE.Vector3(...baseLocal);
    this.samples.length = 0; this.hasLastTip = false;
    this.trailMesh.visible = false; this.trailGeometry.setDrawRange(0, 0);
  }

  setVisible(visible) {
    this.enabled = !!visible;
    if (!this.enabled) {
      this.samples.length = 0; this.trailMesh.visible = false; this.trailGeometry.setDrawRange(0, 0);
      for (const b of this.butterflies) { b.group.visible = false; b.material.opacity = 0; }
      this.clearBursts();
    }
  }

  setQuality(quality) { this.quality = quality; }

  _world(local, out) {
    return this.sword ? this.sword.localToWorld(out.copy(local)) : out.copy(local);
  }

  update(dt, { attacking = false, visible = true, camera = null } = {}) {
    const step = Number.isFinite(dt) ? Math.max(0, Math.min(.05, dt)) : 0;
    this.time += step;
    const active = this.enabled && visible && !!this.sword;
    // 飘带与呼吸光挂在模型自身，与特效应互相独立，所以无条件更新。
    this.sword?.userData?.update?.(this.time);
    if (!active) {
      if (this.trailMesh.visible) { this.samples.length = 0; this.trailMesh.visible = false; this.trailGeometry.setDrawRange(0, 0); }
      for (const b of this.butterflies) { b.group.visible = false; b.material.opacity = 0; }
      this.updateBursts(step);
      return;
    }

    const tip = this._world(this.tipLocal, new THREE.Vector3());
    const base = this._world(this.baseLocal, new THREE.Vector3());
    let tipSpeed = 0;
    if (this.hasLastTip && step > 0) tipSpeed = tip.distanceTo(this.lastTip) / step;
    this.lastTip.copy(tip); this.hasLastTip = true;

    // —— 剑光 ——
    const emit = attacking || tipSpeed > 16;
    if (emit) {
      this.samples.push({ tip: tip.clone(), base: base.clone(), age: 0 });
      if (this.samples.length > TRAIL_MAX - 2) this.samples.shift();
    }
    for (let i = this.samples.length - 1; i >= 0; i--) {
      const sample = this.samples[i]; sample.age += step;
      if (sample.age >= TRAIL_LIFE) this.samples.splice(i, 1);
    }
    this._writeTrail();

    // —— 蝶群 ——
    const flap = Math.sin(this.time * 17);
    for (let i = 0; i < this.butterflies.length; i++) {
      const b = this.butterflies[i], o = b.orbit;
      const angle = o.phase + this.time * o.speed;
      const local = this._v.set(Math.cos(angle) * o.radius, Math.sin(angle * 1.3) * o.radius * .5,
        o.z + Math.sin(angle * .8) * .55 + Math.sin(this.time * .7 + o.phase) * o.lift);
      this._world(local, b.group.position);
      if (camera) b.group.quaternion.copy(camera.quaternion);
      b.left.rotation.y = flap * .9; b.right.rotation.y = -flap * .9;
      // 攻击时蝶群变亮，平时压到一半，避免平时抢戏。
      b.material.opacity = (attacking ? .7 : .25) * (.7 + .3 * Math.sin(this.time * 3 + o.phase));
      b.group.visible = true;
    }

    this.updateBursts(step);
  }

  _writeTrail() {
    const count = this.samples.length;
    if (count < 2) { this.trailMesh.visible = false; this.trailGeometry.setDrawRange(0, 0); return; }
    const positions = this.trailPositions, colors = this.trailColors;
    for (let i = 0; i < count; i++) {
      const sample = this.samples[i], fade = Math.pow(1 - sample.age / TRAIL_LIFE, 1.5);
      const k = i * 6;
      positions[k] = sample.base.x; positions[k + 1] = sample.base.y; positions[k + 2] = sample.base.z;
      positions[k + 3] = sample.tip.x; positions[k + 4] = sample.tip.y; positions[k + 5] = sample.tip.z;
      // 加法混合下颜色趋零即隐去，所以尾端直接把 RGB 收到黑色，不需要 alpha 贴图。
      const c = COOL.clone().lerp(HOT, fade * .85);
      colors[k] = c.r * fade * .35; colors[k + 1] = c.g * fade * .35; colors[k + 2] = c.b * fade * .35;
      colors[k + 3] = c.r * fade; colors[k + 4] = c.g * fade; colors[k + 5] = c.b * fade;
    }
    this.trailGeometry.attributes.position.needsUpdate = true;
    this.trailGeometry.attributes.color.needsUpdate = true;
    this.trailGeometry.setDrawRange(0, (count - 1) * 6);
    this.trailMesh.visible = true;
  }

  burst(point, { guarded = false, knockdown = false, camera = null } = {}) {
    if (!this.enabled || !point) return;
    const scale = knockdown ? 1.5 : guarded ? .8 : 1.15;
    const ringGeometry = new THREE.RingGeometry(.14, .2, 26);
    const ringMaterial = new THREE.MeshBasicMaterial({ color: guarded ? 0xffe6a8 : 0x9fe8ff, transparent: true, opacity: .7,
      blending: THREE.AdditiveBlending, depthWrite: false, side: THREE.DoubleSide, toneMapped: false });
    const ring = new THREE.Mesh(ringGeometry, ringMaterial);
    ring.position.copy(point); ring.scale.setScalar(scale); ring.renderOrder = 7;
    if (camera) ring.quaternion.copy(camera.quaternion);
    this.scene.add(ring);
    this.bursts.push({ mesh: ring, age: 0, life: .3, kind: 'ring', scale });

    // 3~5 只蝶从命中点散开，给"冰蝶炸开"的读感。
    const count = this.quality === 'low' ? 2 : (knockdown ? 5 : 3);
    for (let i = 0; i < count; i++) {
      const b = makeButterfly(guarded ? 0xfff0c8 : BUTTERFLY_TINT, .085);
      b.group.position.copy(point); b.material.opacity = .7;
      const angle = (i / count) * Math.PI * 2 + Math.random() * .4;
      const velocity = new THREE.Vector3(Math.cos(angle) * (1.1 + Math.random() * .8), .5 + Math.random() * 1.1, Math.sin(angle) * (1.1 + Math.random() * .8));
      this.scene.add(b.group);
      this.bursts.push({ kind: 'butterfly', butterfly: b, age: 0, life: .5 + Math.random() * .25, velocity });
    }
  }

  updateBursts(dt) {
    for (let i = this.bursts.length - 1; i >= 0; i--) {
      const burst = this.bursts[i]; burst.age += dt;
      const progress = Math.min(1, burst.age / burst.life);
      if (burst.kind === 'ring') {
        const mesh = burst.mesh;
        mesh.scale.setScalar(burst.scale * (.35 + progress * 2.5));
        mesh.material.opacity = .7 * (1 - progress) ** 1.6;
      } else {
        const b = burst.butterfly, velocity = burst.velocity;
        b.group.position.addScaledVector(velocity, dt);
        velocity.multiplyScalar(1 - 2.2 * dt); velocity.y -= 1.4 * dt;
        const flap = Math.sin(burst.age * 26);
        b.left.rotation.y = flap; b.right.rotation.y = -flap;
        b.material.opacity = .7 * (1 - progress) ** 1.3;
      }
      if (progress >= 1) { this._removeBurst(burst); this.bursts.splice(i, 1); }
    }
  }

  _removeBurst(burst) {
    if (burst.kind === 'ring') {
      burst.mesh.removeFromParent(); burst.mesh.geometry.dispose(); burst.mesh.material.dispose();
    } else {
      const b = burst.butterfly;
      b.group.removeFromParent(); b.left.geometry.dispose(); b.material.dispose();
    }
  }

  clearBursts() { while (this.bursts.length) this._removeBurst(this.bursts.pop()); }

  dispose() {
    this.clearBursts();
    this.trailMesh.removeFromParent(); this.trailGeometry.dispose(); this.trailMaterial.dispose();
    for (const b of this.butterflies) { b.group.removeFromParent(); b.left.geometry.dispose(); b.material.dispose(); }
    this.butterflies.length = 0; this.samples.length = 0; this.sword = null;
  }
}