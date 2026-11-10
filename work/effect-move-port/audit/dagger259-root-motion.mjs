// Original d_base samples, mapped through the current yaw0 native-space adapter.
// This reconstruction excludes obstacles and is not a public-input damage test.
import { readFile, writeFile } from 'node:fs/promises';
import { createHash } from 'node:crypto';
import * as THREE from '../../../dist/vendor/three.module.js';
import { loadNativeCharacter } from '../../../dist/native-character.js';
const dist = new URL('../../../dist/', import.meta.url), here = new URL('./', import.meta.url);
const originalFetch = globalThis.fetch, originalLoad = THREE.TextureLoader.prototype.load;
globalThis.fetch = async input => {
  try { return new Response(await readFile(new URL(input instanceof Request ? input.url : input, dist)), { status: 200 }); }
  catch { return new Response('', { status: 404 }); }
};
THREE.TextureLoader.prototype.load = function (_url, done) { const texture = new THREE.Texture(); done?.(texture); return texture; };
try {
  const character = await loadNativeCharacter(0, { scale: .08, inPlace: true, appearance: 'original' });
  const baseline = character.sampleSceneMotion(0, 9531);
  const delta = frame => {
    const p = character.sampleSceneMotion(0, frame);
    return [(p.x-baseline.x)*.08, (p.z-baseline.z)*.08, -(p.y-baseline.y)*.08];
  };
  const staticProbe = JSON.parse(await readFile(new URL('dagger259-direction-probe.json', here)));
  const samples = [9531,9540,9550,9551,9552,9553,9554,9558,9561].map(frame => ({
    frame, source: 0, nativeDBase: character.sampleSceneMotion(0, frame), worldDelta: delta(frame)
  }));
  const projectedAttackCenters = staticProbe.sampledBounds.map(sample => {
    const rootDelta = delta(sample.frame);
    return { frame: sample.frame, effectTime: sample.time, rootDelta,
      staticEffectCenter: sample.center,
      worldCenter: sample.center.map((value, i) => value + rootDelta[i]) };
  });
  const sources = [];
  for (const path of ['assets/original/characters/common/character.amb','assets/original/characters/p0/p0.bnc','assets/original/characters/p0/p0.pos','assets/native/combat/P0.POS', 'assets/original/sounds/definitions/pos259.ef']) {
    sources.push({ path: `dist/${path}`, sha256: createHash('sha256').update(await readFile(new URL(path, dist))).digest('hex') });
  }
  const result = { scope: 'Original P0 d_base, source0; yaw0 SCALE .08 with no world obstruction. Projected centers combine original motion with the existing static contact probe; no gameplay acceptance is claimed.',
    samples, projectedAttackCenters, sources,
    parentIntegrationEvidence: { path: 'work/effect-move-port/integration-second.tap', reportedTargetForwardZ: 5, reportedDamage: 794, sourceReaction: 109, followup: 349,
      boundary: 'Parent real-actor CPU fixture, ordinary input, source d_base movement; retaliation/navigation paused. Not a browser test.' } };
  await writeFile(new URL('dagger259-root-motion.json', here), JSON.stringify(result, null, 2)+'\n');
  console.log(JSON.stringify({ samples, firstProjectedCenter: projectedAttackCenters[0], lastProjectedCenter: projectedAttackCenters.at(-1) },null,2));
  character.dispose();
} finally {
  globalThis.fetch = originalFetch;
  THREE.TextureLoader.prototype.load = originalLoad;
}
