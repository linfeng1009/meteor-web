"""Run unchanged default importer in an isolated output root; never writes dist."""
from contextlib import redirect_stdout
from datetime import datetime, timezone
from hashlib import sha256
from importlib.util import module_from_spec, spec_from_file_location
from io import StringIO
from pathlib import Path
from tempfile import TemporaryDirectory
import json
import subprocess
import sys

sys.dont_write_bytecode = True
HERE = Path(__file__).resolve().parent
PROJECT = HERE.parents[2]

def digest(path):
    return sha256(path.read_bytes()).hexdigest()

def main():
    importer = PROJECT / 'scripts/import-rage-vfx.py'
    installed = PROJECT / 'dist/assets/original/rage-vfx'
    result = {'observedAt': datetime.now(timezone.utc).isoformat(),
              'scope': 'Offline default importer with ROOT redirected to a temporary mirror; unchanged extraction code, no include-pose flags, no dist writes.',
              'importerPath': str(importer), 'importerSha256': digest(importer),
              'installedManifestSha256Before': digest(installed / 'manifest.json')}
    with TemporaryDirectory(prefix='default-import-', dir=HERE) as scratch:
        mirror = Path(scratch)
        (mirror / 'dist/assets/original/sounds').mkdir(parents=True)
        for name in ['native-combat.js', 'native-move-catalog.js']:
            (mirror / 'dist' / name).symlink_to(PROJECT / 'dist' / name)
        (mirror / 'dist/assets/native').symlink_to(PROJECT / 'dist/assets/native', target_is_directory=True)
        for name in ['weapon-models', 'sounds/definitions']:
            (mirror / 'dist/assets/original' / name).symlink_to(PROJECT / 'dist/assets/original' / name, target_is_directory=True)
        spec = spec_from_file_location('readonly_default_import', importer)
        module = module_from_spec(spec)
        spec.loader.exec_module(module)
        module.ROOT = mirror
        stdout = StringIO()
        argv = sys.argv
        try:
            sys.argv = [str(importer)]
            with redirect_stdout(stdout):
                module.main()
        finally:
            sys.argv = argv
        generated = mirror / 'dist/assets/original/rage-vfx'
        manifest = json.loads((generated / 'manifest.json').read_text())
        requested = json.loads((mirror / 'work/rage-vfx/requested-effects.json').read_text())
        effect_ids = set(manifest['effects'])
        textures = manifest['textures']
        requested_ids = {row['id'] for row in requested}
        compare = [{'path': str(path.relative_to(generated)), 'sha256': digest(path),
                    'installedMatches': (installed / path.relative_to(generated)).is_file()
                    and digest(path) == digest(installed / path.relative_to(generated))}
                   for path in sorted(generated.rglob('*')) if path.is_file()]
        source_checks = []
        for effect_id, effect in manifest['effects'].items():
            path = PROJECT / 'dist/assets/original' / effect['source']
            source_checks.append({'id': effect_id, 'path': str(path),
                                  'sha256': digest(path), 'manifestMatches': effect['sha256'] == digest(path)})
        node = '''import {readFileSync} from 'node:fs';
import {parsePos,decodeNativeText} from './dist/native-combat.js';
import {NATIVE_MOVE_CATALOG} from './dist/native-move-catalog.js';
const poses=parsePos(decodeNativeText(readFileSync('dist/assets/native/combat/P0.POS')));
const chain=[];let id=259;while(poses.has(id)&&!chain.some(p=>p.id===id)){const p=poses.get(id);chain.push({id,start:p.start,end:p.end,link:p.link??null,effectId:p.raw.fields.effectid??null,attackCount:p.attacks.length});id=p.link;}
process.stdout.write(JSON.stringify({dagger:NATIVE_MOVE_CATALOG.find(m=>m.poseId===259),chain,pendingDarts:NATIVE_MOVE_CATALOG.filter(m=>[201,551,203].includes(m.poseId))}));'''
        catalog = json.loads(subprocess.run(['node', '--input-type=module', '-e', node], cwd=PROJECT, check=True, capture_output=True, text=True).stdout)
        result.update(extraction=json.loads(stdout.getvalue()), requested=requested,
                      requestedMissing=sorted(requested_ids-effect_ids), effectIds=sorted(effect_ids),
                      catalog=catalog, files=compare, sourceFiles=source_checks,
                      enabledPendingDartEffects=sorted(effect_ids & {'pos201','pos551','pos203','pos204'}),
                      textureCount=len(textures), textureImageCount=sum('url' in t for t in textures.values()),
                      iflCount=sum('frames' in t for t in textures.values()),
                      generatedManifestSha256=digest(generated/'manifest.json'))
    result['installedManifestSha256After'] = digest(installed / 'manifest.json')
    result['ok'] = (all(f['installedMatches'] for f in result['files'])
                    and all(f['manifestMatches'] for f in result['sourceFiles'])
                    and not result['requestedMissing'] and not result['enabledPendingDartEffects']
                    and result['installedManifestSha256Before'] == result['installedManifestSha256After']
                    and result['catalog']['dagger'].get('pending') is None
                    and [p['id'] for p in result['catalog']['chain']] == [259,349])
    (HERE/'default-import-reproduction.json').write_text(json.dumps(result,ensure_ascii=False,indent=2)+'\n')
    print(json.dumps({k:result[k] for k in ['ok','extraction','textureImageCount','iflCount','requestedMissing','enabledPendingDartEffects','catalog','generatedManifestSha256']},ensure_ascii=False))
    if not result['ok']:
        raise SystemExit(1)

if __name__ == '__main__':
    main()
