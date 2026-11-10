# 2026-11-10 Self-contained character import

- Scope: user-authorized local model conversion; no network uploads and no source deletion.
- Copy all source formats and attribution into a project-owned archive before retargeting. Record per-file lengths and hashes; build against that archive, never against the transient download directory.
- A dense single-atlas model can contain abrupt root/leg and torso/arm auto-rig weights even though every vertex is numerically valid. Validate actual deformed edges across jump/attack samples, not just finite bounds.
- Keep duplicate UV-seam positions under common influences. Smooth a body displacement field instead of directly smoothing source positions; lock the authored head and hair, retaining facial shape and texture detail.
- A color/height fabric mask can stabilize a short dark skirt when no separate material exists. Treat it as an explicit model-specific approximation, not cloth physics.
- Reopen the finished authoring file and check packed bytes/actions/libraries. Blender loads packed images lazily: checking has_data before reading dimensions/pixels can falsely report a missing texture.
- Verify the actual runtime package, including converted JPEG/PNG assets. Missing PMX, Blender and original source folders should not affect gameplay.
- Evidence: E-001 archived hashes; E-002 native-matrix/packed-image audit; E-003 sampled mesh strain; E-004 full regression and package integrity; E-005 visible in-game character/actions. Findings F-001/F-002/F-003 validated; path_type=callflow.

This anonymized journal is stored in the writable project case instead of modifying the installed skill package.
