# Original native characters

These files are extracted from the user-provided local `lxhdj_` client, read-only. Geometry, skin weights, skeleton hierarchy, animation rotations, root positions and weapon attachment transforms come from the actual SKC, BNC, AMB and POS files.

`native-character.js` is an independently written Three.js loader. The public [AMB structure reader](https://github.com/IceRiverr/Meteor/blob/master/Tools/AmbToTxt/compile_amb.cpp) was inspected only to cross-check fixed-width dummy-parent names; no third-party implementation code was copied. Its repository license was not established. Original game assets remain the property of their original rights holders, 昱泉国际 / Interserv.

## API

```js
import { loadNativeCharacter, NATIVE_CHARACTERS } from './native-character.js';
const actor = await loadNativeCharacter(0, { scale: 0.08 });
scene.add(actor.group);
actor.update(dt, 'run');                 // Original Pose 144
actor.playPose(262, { loop: false });    // Original sword attack
actor.update(dt);
actor.setPoseFrame(0, 9767.5);           // Exact Common AMB source/frame, interpolated
const rawRoot = actor.sampleRoot(0, 9767.5); // Native unscaled x/y/z
const hand = actor.getAttachment('d_wpnR');
```

- IDs 0–19 are supported, with separate original skins, skeletons, personal animations and textures. The Common AMB fetch and parse are cached once across all instances.
- `NATIVE_CHARACTERS` and `roster.json` expose IDs, names and original biography image paths. Names were visually read from each local `image/P00{id+1}.JPG`; ID 8's supplied image reads 子與, represented as 子与.
- Default model faces Three.js **+Z**. Native space is Z-up and faces -Y; the conversion is a rotation of -π/2 around X.
- Default scale 0.08 yields a standing character around 2.9 metres, matching this prototype's existing actor proportions. The original source data is unscaled.
- By default horizontal root translation is locked, so the engine can accumulate `sampleRoot` deltas exactly once. Bone-pelvis height and all original rotations remain animated. To play absolute root translation, use `setPoseFrame(source, frame, { rootMotion: true })` or `loadNativeCharacter(id, { inPlace: false })`.
- `getAttachment` returns the native-space Bone object. A weapon parented there inherits the original native scale and axis convention; a weapon already converted to Three.js coordinates needs its inverse coordinate transform at the binding layer.
- `setPoseFrame` selects externally driven animation and remains fixed until another call or `playPose`. `update(dt, { source, frame })` can also drive exact frames.
- `dispose()` releases this actor's geometry, materials and skeleton. Shared cached textures stay reusable.

## Verified data formats

**SKC** contains static-skin material records, indexed triangle geometry and per-vertex weighted bone references. The native UVs already use bottom-to-top V coordinates; they must not be flipped again for Three.js texture uploads. TGA textures were converted to PNG with alpha retained.

**BNC** contains local pivots and WXYZ quaternions for 30 named bones and 6 named dummies. Parent names can be literal names or `b{index}` / `d{index}` aliases.

**AMB** begins with ASCII `BANIM`, then four little-endian int32 values: bone count, dummy count, frame count and FPS. Actual Common data has 17,061 frames at 30 FPS. Each frame is 698 bytes: int32 -1 marker, int32 sequential frame index, float32 root position[3], 30 WXYZ float32 quaternions, then 6 records of 5-byte parent alias + float32 position[3] + WXYZ float32 quaternion. Weapon-dummy parents can change per frame, including to NULL; the loader applies those changes.

**POS** defines source 0 as Common AMB and source 1 as the character's own AMB, with original start, end and loop ranges. The local p0 POS contains 479 nonempty poses. `pose-reference.json` records externally cross-checked action IDs and direction labels; it does not claim the direction table came from disassembling the EXE.

## Evidence

- `manifest.json`: original input hashes, byte counts, per-character geometry and texture dependencies.
- `E-character-extraction.json`: complete AMB frame sequence validation, exact byte-consumption checks, quaternion finite/norm checks and SKC weight/index validation.
- `E-character-runtime.json`: 20 real SkinnedMeshes and 220 original action samples tested using the bundled Three.js CPU skinning; all transformed bounds and hand attachment positions are finite. Automatic frame advance and external frame preservation were tested.
- `preview.html?id=0`: live original-model browser preview; IDs 0–19 can be substituted.
- Root-agent visual QA screenshot: `artifacts/original-meng.png` (the first capture identified UV inversion, subsequently corrected).

Executable import tables do not apply to these data files. Their equivalent dependency anchors are SKC texture and bone references, BNC aliases, and BANIM header/frame layouts. Meteor.exe analysis is tracked separately by the parent case.
