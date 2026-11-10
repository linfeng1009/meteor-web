// RAF cadence measures delivered frames; CPU timings are not GPU timings.
export class FrameMeter {
  constructor(size = 180) { this.intervals = new Float64Array(size); this.reset(); }
  reset() { this.count = 0; this.cursor = 0; this.last = null; this.publishAt = 0; this.cpu = 0; this.world = 0; this.camera = 0; this.render = 0; this.samples = 0; this.latest = null; }
  sample(timestamp, timings = {}) {
    if (!Number.isFinite(timestamp)) return null;
    const delta = this.last === null ? 0 : timestamp - this.last; this.last = timestamp;
    // Ignore background suspension, rather than displaying a misleading 1 FPS.
    if (delta > 1000 || delta < 0) { this.reset(); this.last = timestamp; return null; }
    if (delta > 0) { this.intervals[this.cursor] = delta; this.cursor = (this.cursor + 1) % this.intervals.length; this.count = Math.min(this.count + 1, this.intervals.length); }
    for (const key of ['cpu', 'world', 'camera', 'render']) this[key] += timings[key] || 0;
    this.samples++;
    if (!this.count || timestamp < this.publishAt) return null;
    this.publishAt = timestamp + 500;
    const sorted = Array.from(this.intervals.subarray(0, this.count)).sort((a, b) => a - b);
    const mean = sorted.reduce((sum, n) => sum + n, 0) / sorted.length;
    this.latest = { fps: 1000 / mean, frameMs: mean, p95Ms: sorted[Math.ceil(sorted.length * .95) - 1],
      cpuMs: this.cpu / this.samples, worldMs: this.world / this.samples, cameraMs: this.camera / this.samples, renderMs: this.render / this.samples };
    this.cpu = this.world = this.camera = this.render = this.samples = 0;
    return this.latest;
  }
}

// Conservative 60Hz budget with hysteresis. Never change simulation cadence.
export class RenderScaleController {
  constructor(maximum = 2) { this.reset(maximum); }
  reset(maximum) { this.maximum = maximum; this.minimum = Math.min(maximum, .75); this.ratio = maximum; this.slow = this.fast = 0; }
  update(stats, active = true) {
    if (!active || !stats || stats.frameMs > 80 || stats.cpuMs > 22) { this.slow = this.fast = 0; return this.ratio; }
    this.slow = stats.fps < 52 ? this.slow + 1 : 0;
    this.fast = stats.fps > 58 && stats.p95Ms < 22 ? this.fast + 1 : 0;
    if (this.slow >= 3) { this.ratio = Math.max(this.minimum, Math.round((this.ratio - .15) * 100) / 100); this.slow = this.fast = 0; }
    else if (this.fast >= 12) { this.ratio = Math.min(this.maximum, Math.round((this.ratio + .05) * 100) / 100); this.slow = this.fast = 0; }
    return this.ratio;
  }
}

export function createFrameOverlay(document) {
  const element = document.createElement('output');
  element.id = 'frame-meter'; element.setAttribute('aria-label', '实时帧率');
  // Deliberately not aria-live: continuous announcements interfere with play.
  element.style.cssText = 'position:fixed;bottom:66px;left:16px;z-index:12;pointer-events:none;padding:7px 10px;border-radius:5px;background:#091216cc;color:#c9eed9;font:12px/1.5 monospace;white-space:pre;font-variant-numeric:tabular-nums';
  element.textContent = 'FPS 测量中…'; document.body.append(element);
  return { update(stats, renderer) {
    element.textContent = `${Math.round(stats.fps)} FPS · ${stats.frameMs.toFixed(1)} ms\nP95 ${stats.p95Ms.toFixed(1)} ms · 渲染倍率 ${renderer.getPixelRatio().toFixed(2)}×`;
    element.title = `逻辑 ${stats.worldMs.toFixed(2)} ms / 镜头 ${stats.cameraMs.toFixed(2)} ms / 渲染提交 ${stats.renderMs.toFixed(2)} ms；${renderer.info.render.calls} 次绘制 / ${renderer.info.render.triangles} 三角形。CPU 不含 GPU 执行时间。`;
  }, setVisible(value) { element.hidden = !value; }, dispose() { element.remove(); } };
}
