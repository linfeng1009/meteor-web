# 2026-11-10 Local model hair springs

- Scope: user-authorized offline converted character meshes and archived rig metadata; no uploads or external actions.
- Source positions and hierarchy can recover a plausible visual chain when source files are gone. They do not restore original vertex weights or rigid-body physics; state that distinction.
- Preserve the original body skeleton and inverse bind matrices; append visual bones in a private rendering skeleton. Protect any hair vertex shared with a non-hair material.
- Per-joint angular limits accumulate along long chains. Add an animated-head-space direction cone, carry most driver motion into both current and previous tips, and increase damping for restrained motion.
- Fit body proxy radii to rest clearance and reapply angle limits after collision pushes to avoid explosive authored-rest conflicts.
- Validate actual hair vertices against a rigid reference at the same pose, not just bone angles. Check native joints and attachments remain numerically identical.
- Avoid strict equality assertions that print entire cyclic THREE skeletons. Compare bone-reference predicates and numeric transforms instead; huge failure diffs can exhaust memory.
- Serial heap-limited tests require realistic file-level timeouts for long mission simulations. Retain initial logs and rerun only affected files after a failure.

Evidence: E-001 local binding audit; E-002 actual motion and preservation invariants; E-003 vertex-displacement probe. Findings F-001/F-002/F-003 validated; path_type=callflow. Full project evidence remains in the local case report.

This journal is retained in the writable project case directory rather than modifying the installed skill package.
