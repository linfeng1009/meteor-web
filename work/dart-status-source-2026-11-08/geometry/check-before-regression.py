"""Run the new binding checks against the retained old module in isolation."""
from pathlib import Path
from tempfile import TemporaryDirectory
import subprocess

HERE = Path(__file__).resolve().parent
PROJECT = HERE.parents[2]
dist_url = (PROJECT / 'dist').as_uri() + '/'
with TemporaryDirectory(prefix='binding-before-', dir=HERE) as folder:
    folder = Path(folder)
    old = folder / 'before.mjs'
    old.write_text((HERE / 'native-effect-transforms-before.js.txt').read_text()
                   .replace("'./vendor/three.module.js'", repr(dist_url + 'vendor/three.module.js')))
    test = (PROJECT / 'tests/native-effect-transforms.test.mjs').read_text()
    test = test.replace('../dist/native-effect-transforms.js', old.as_uri()).replace('../dist/', dist_url)
    script = folder / 'binding-before.test.mjs'
    script.write_text(test)
    result = subprocess.run(['node', '--test', str(script)], cwd=PROJECT, capture_output=True, text=True)
    (HERE / 'transform-tests-before.tap').write_text(result.stdout + result.stderr)
    if result.returncode != 1 or '# tests 4\n' not in result.stdout or '# fail 4\n' not in result.stdout:
        raise SystemExit('Expected four binding regressions in the old module; inspect archived TAP.')
    print('Retained old module fails all4 meaningful binding checks; production files unchanged.')
