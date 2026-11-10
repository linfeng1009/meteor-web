import * as THREE from './vendor/three.module.js';

// SetScene arguments are preserved from the original PST. Particle placement,
// size conversion and the camera-local volume are browser presentation choices;
// they do not participate in combat, visibility queries or scene collision.
export const NATIVE_WEATHER_PROVENANCE = 'Original PST SetScene snow/density/wind/speed/size; browser particle presentation, not the recovered native snow renderer.';
const fields = Object.freeze({ snow: 1, snowdensity: 1, winddir: 3, snowspeed: 2, snowsize: 2 });
export function validNativeWeatherSetting(name, values) {
  return fields[name] === values.length && values.every(Number.isFinite);
}

export class NativeWeather {
  constructor(scene) { this.scene = scene; this.settings = {}; this.points = null; this.clock = 0; }
  set(name, ...values) {
    if (!validNativeWeatherSetting(name, values)) return false;
    this.settings[name] = [...values];
    if (name === 'snow' || name === 'snowdensity' || name === 'snowsize') this.rebuild();
    return true;
  }
  rebuild() {
    this.remove();
    if (!this.settings.snow?.[0]) return;
    const count = Math.max(0, Math.min(2000, Math.trunc(this.settings.snowdensity?.[0] ?? 200)));
    const positions = new Float32Array(count * 3);
    this.offsets = Array.from({ length: count }, (_, i) => {
      // Stable offsets avoid per-frame random draws. Three.js construction may generate random UUIDs.
      const frac = n => n - Math.floor(n);
      return new THREE.Vector3(frac((i + 1) * .754877666) * 40 - 20, frac((i + 1) * .569840296) * 22 - 4, frac((i + 1) * .438289) * 40 - 20);
    });
    const geometry = new THREE.BufferGeometry(); geometry.setAttribute('position', new THREE.BufferAttribute(positions, 3));
    const material = new THREE.PointsMaterial({ color: 0xe8eff5, size: Math.max(.025, Math.min(.16, (this.settings.snowsize?.[0] ?? 5) * .014)), transparent: true, opacity: .7, depthWrite: false, sizeAttenuation: true });
    this.points = new THREE.Points(geometry, material); this.points.frustumCulled = false; this.points.name = 'PST snow';
    this.scene.add(this.points); this.update(0, new THREE.Vector3());
  }
  update(dt, center) {
    if (!this.points || !center) return;
    this.clock += Math.max(0, dt);
    const positions = this.points.geometry.attributes.position, wind = this.settings.winddir || [0, 0, 0];
    const speed = this.settings.snowspeed || [20, 100], wrap = (x, span) => ((x % span) + span) % span;
    for (let i = 0; i < this.offsets.length; i++) {
      const p = this.offsets[i], fall = (speed[0] + (speed[1] - speed[0]) * ((i % 17) / 16)) * .04;
      positions.setXYZ(i, center.x + wrap(p.x + wind[0] * .015 * this.clock + 20, 40) - 20,
        center.y + wrap(p.y - fall * this.clock + 4, 22) - 4,
        center.z + wrap(p.z - wind[1] * .015 * this.clock + 20, 40) - 20);
    }
    positions.needsUpdate = true;
  }
  remove() { if (!this.points) return; this.points.removeFromParent(); this.points.geometry.dispose(); this.points.material.dispose(); this.points = null; }
  clear() { this.remove(); this.settings = {}; this.offsets = []; this.clock = 0; }
  dispose() { this.clear(); }
}
