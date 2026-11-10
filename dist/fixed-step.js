// Web simulation cadence, not a claim about the original EXE tick rate.
export const SIMULATION_STEP = 1 / 60;
export class FixedStepClock {
  constructor({ step = SIMULATION_STEP, maxSteps = 15 } = {}) {
    if (!(step > 0) || !Number.isFinite(step) || !Number.isSafeInteger(maxSteps) || maxSteps < 1) throw new Error('Invalid fixed-step clock');
    this.step = step; this.maxSteps = maxSteps; this.accumulator = 0; this.droppedSeconds = 0;
  }
  reset() { this.accumulator = 0; }
  advance(seconds, update) {
    if (!Number.isFinite(seconds) || seconds <= 0) return 0;
    // Catch up short stalls, but bound work after sleep/background suspension.
    const accepted = Math.min(seconds, this.step * this.maxSteps);
    this.droppedSeconds += seconds - accepted;
    this.accumulator += accepted;
    let count = 0;
    while (this.accumulator + 1e-10 >= this.step && count < this.maxSteps) {
      this.accumulator = Math.max(0, this.accumulator - this.step); count++;
      if (update(this.step) === false) { this.reset(); break; }
    }
    return count;
  }
}
