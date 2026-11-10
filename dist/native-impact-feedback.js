import * as THREE from './vendor/three.module.js';

// Presentation-only Web adapters. These short freezes, spark geometry and
// camera amplitudes are not recovered Meteor.exe constants or native EF VFX.
// Native attack windows, damage, reaction poses and WAV selection remain owned
// by the combat host. A freeze returned here applies only to the two actors;
// it must not pause the mission clock, projectiles or unrelated fighters.
export const IMPACT_FEEDBACK_ADAPTER = Object.freeze({
  hit: Object.freeze({ hitstop: .032, cameraImpulse: .012, lifetime: .15, radius: .34, count: 7 }),
  guard: Object.freeze({ hitstop: .022, cameraImpulse: .008, lifetime: .13, radius: .28, count: 6 }),
  knockdown: Object.freeze({ hitstop: .05, cameraImpulse: .024, lifetime: .18, radius: .5, count: 9 }),
  maxEffects: 12
});

export class NativeImpactFeedback {
  constructor(scene) {
    this.scene = scene; this.active = []; this.cameraOffset = new THREE.Vector3(); this.disposed = false;
  }
  emit({ point, direction = null, guarded = false, knockdown = false, local = true } = {}) {
    if (this.disposed || !point || ![point.x, point.y, point.z].every(Number.isFinite)) return null;
    const profile = guarded ? IMPACT_FEEDBACK_ADAPTER.guard : knockdown ? IMPACT_FEEDBACK_ADAPTER.knockdown : IMPACT_FEEDBACK_ADAPTER.hit;
    if (this.active.length >= IMPACT_FEEDBACK_ADAPTER.maxEffects) this._remove(0);
    const vertices = new Float32Array(profile.count * 6), geometry = new THREE.BufferGeometry();
    geometry.setAttribute('position', new THREE.BufferAttribute(vertices, 3));
    const material = new THREE.LineBasicMaterial({ color: guarded ? 0xffe8a6 : 0xffb66d, transparent: true, opacity: 1,
      blending: THREE.AdditiveBlending, depthWrite: false, depthTest: true, toneMapped: false });
    const mesh = new THREE.LineSegments(geometry, material); mesh.position.copy(point); mesh.frustumCulled = false;
    const angle = direction && Math.hypot(direction.x, direction.z) > 1e-6 ? Math.atan2(direction.x, direction.z) : 0;
    mesh.rotation.y = angle; this.scene.add(mesh);
    const effect = { mesh, profile, age: 0, local: !!local, vertices, direction: new THREE.Vector3(Math.sin(angle), 0, Math.cos(angle)) };
    this.active.push(effect); this._draw(effect);
    return { hitstop: profile.hitstop, cameraImpulse: local ? profile.cameraImpulse : 0 };
  }
  _draw(effect) {
    const { profile, vertices, mesh } = effect, progress = Math.min(1, effect.age / profile.lifetime);
    // Deterministic needles radiate from the actual contact, with a slight
    // outward drift. No full-screen flash or silhouette replacement is used.
    for (let i = 0; i < profile.count; i++) {
      const a = i * Math.PI * 2 / profile.count + .17, spread = profile.radius * (.36 + progress * 1.8);
      const x = Math.cos(a), y = Math.sin(a), z = Math.sin(i * 2.4) * .42, k = i * 6;
      const inner = spread * (.1 + progress * .52), outer = spread * (1 - progress * .28);
      vertices[k] = x * inner; vertices[k + 1] = y * inner; vertices[k + 2] = z * inner;
      vertices[k + 3] = x * outer; vertices[k + 4] = y * outer; vertices[k + 5] = z * outer;
    }
    mesh.geometry.attributes.position.needsUpdate = true; mesh.material.opacity = (1 - progress) ** 1.4;
  }
  update(dt) {
    const step = Number.isFinite(dt) ? Math.max(0, dt) : 0; this.cameraOffset.set(0, 0, 0);
    for (let i = this.active.length - 1; i >= 0; i--) {
      const effect = this.active[i]; effect.age += step;
      if (effect.age >= effect.profile.lifetime) { this._remove(i); continue; }
      this._draw(effect);
      if (effect.local) {
        const decay = (1 - effect.age / effect.profile.lifetime) ** 2, pulse = Math.sin(effect.age * 100 + .9);
        const amplitude = effect.profile.cameraImpulse * decay * pulse;
        this.cameraOffset.addScaledVector(effect.direction, amplitude); this.cameraOffset.y += amplitude * .4;
      }
    }
    // Simultaneous multi-target contacts must never multiply into a large shake.
    this.cameraOffset.clampLength(0, IMPACT_FEEDBACK_ADAPTER.knockdown.cameraImpulse);
  }
  _remove(index) {
    const [effect] = this.active.splice(index, 1); if (!effect) return;
    effect.mesh.removeFromParent(); effect.mesh.geometry.dispose(); effect.mesh.material.dispose();
  }
  clear() {
    while (this.active.length) this._remove(this.active.length - 1);
    this.cameraOffset.set(0, 0, 0);
  }
  dispose() { this.clear(); this.disposed = true; }
}
