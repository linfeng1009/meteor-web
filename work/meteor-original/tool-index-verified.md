# Tool paths verified after bootstrap, 2026-10-22

The automatic index refresh is delayed by its `ghidraRun --version` GUI launcher probe. These paths were verified directly after the manifest bootstrap completed installation.

| Tool | Verified absolute path | Verification |
|---|---|---|
| Ghidra headless | /opt/homebrew/Cellar/ghidra/12.1.4/libexec/support/analyzeHeadless | file exists in installed Homebrew 12.1.4 bottle |
| Ghidra launcher | /opt/homebrew/bin/ghidraRun | symlink to ../Cellar/ghidra/12.1.4/bin/ghidraRun |
| Java 21 | /opt/homebrew/opt/openjdk@21/libexec/openjdk.jdk/Contents/Home/bin/java | file exists in installed Homebrew 21.0.13 bottle |
