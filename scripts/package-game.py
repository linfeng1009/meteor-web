"""Package the complete browser runtime, including converted character assets."""
from pathlib import Path
from hashlib import sha256
import json
import posixpath
import re
import tempfile
import zipfile

ROOT = Path(__file__).resolve().parents[1]


def digest(data):
    return sha256(data).hexdigest()


def main():
    package = json.loads((ROOT / 'package.json').read_text())
    name = f"meteor-web-v{package['version']}"
    output = ROOT / 'artifacts'
    output.mkdir(exist_ok=True)
    target = output / f'{name}.zip'
    runtime_files = {
        path.relative_to(ROOT).as_posix(): path
        for path in (ROOT / 'dist').rglob('*')
        if path.is_file() and path.name != '.DS_Store'
    }
    for filename in ['server.mjs', '启动游戏.command', '停止游戏.command']:
        path = ROOT / filename
        if not path.is_file():
            raise FileNotFoundError(filename)
        runtime_files[filename] = path
    runtime_package = {
        'name': package['name'], 'version': package['version'],
        'private': True, 'type': 'module',
        'scripts': {'start': 'node server.mjs', 'dev': 'node server.mjs'},
    }
    generated = {
        'package.json': (json.dumps(runtime_package, ensure_ascii=False, indent=2) + '\n').encode(),
        '运行说明.txt': (
            '流星蝴蝶剑 Web 本地运行包\n\n'
            '请先完整解压，再运行。需要 Node.js 20 或更新版本。\n'
            'macOS：双击「启动游戏.command」，保留终端窗口。\n'
            '其他系统：在解压目录运行 npm start，打开 http://localhost:4173/ 。\n\n'
            'dist 包含游戏运行文件、人物转换网格、贴图、原骨架与动作、地图和声音。\n'
            'YS-胡桃、YS-影、RE0-爱蜜莉雅、豆包与春田的转换网格及原贴图已包含。\n'
            '运行不需要原始 PMX、Blender、Downloads 目录或 npm 安装依赖。\n'
            '不能直接双击 index.html 启动；请使用上述 HTTP 服务。\n'
        ).encode(),
    }
    records = []
    with tempfile.NamedTemporaryFile(dir=output, suffix='.zip', delete=False) as temporary:
        temp_path = Path(temporary.name)
    try:
        with zipfile.ZipFile(temp_path, 'w', zipfile.ZIP_DEFLATED, compresslevel=6) as archive:
            for filename, path in sorted(runtime_files.items()):
                data = path.read_bytes()
                info = zipfile.ZipInfo.from_file(path, arcname=f'{name}/{filename}')
                archive.writestr(info, data, compress_type=zipfile.ZIP_DEFLATED, compresslevel=6)
                records.append({'path': filename, 'bytes': len(data), 'sha256': digest(data)})
            for filename, data in generated.items():
                archive.writestr(f'{name}/{filename}', data)
                records.append({'path': filename, 'bytes': len(data), 'sha256': digest(data)})
            inventory = {
                'version': package['version'], 'files': records,
                'runtimeAssetsIncluded': 'Complete dist tree; independent of Git staging and ignore rules.',
                'originalPmxRequired': False,
            }
            archive.writestr(f'{name}/package-manifest.json', json.dumps(inventory, ensure_ascii=False, indent=2))

        with zipfile.ZipFile(temp_path) as archive:
            def read(filename):
                return archive.read(f'{name}/{filename}')

            included = {record['path'] for record in records}
            for record in records:
                data = read(record['path'])
                if len(data) != record['bytes'] or digest(data) != record['sha256']:
                    raise ValueError(f"Archive integrity failure: {record['path']}")
            # Check local module imports in the actual archive, including new
            # untracked runtime files that a Git-based packer could omit.
            imports = re.compile(r"(?:\bfrom\s*|\bimport\s*\(\s*|\bimport\s*)(['\"])(\./[^'\"]+)\1")
            for filename in sorted(included):
                if not filename.endswith(('.js', '.mjs')):
                    continue
                for match in imports.finditer(read(filename).decode()):
                    relative = match[2].split('?')[0].split('#')[0]
                    required = posixpath.normpath(posixpath.join(posixpath.dirname(filename), relative))
                    if required not in included:
                        raise FileNotFoundError(f'{filename} imports missing packaged module {required}')
            characters = []
            for family in ['hutao', 'raiden', 'emilia', 'doubao', 'springfield']:
                base = f'dist/assets/enhanced/{family}'
                manifest = json.loads(read(f'{base}/manifest.json'))
                if manifest.get('appearance') != family:
                    raise ValueError(f'{family}: packaged appearance identifier mismatch')
                mesh_path = posixpath.normpath(f"{base}/{manifest['mesh']}")
                skin = json.loads(read(mesh_path))
                mesh_directory = posixpath.dirname(mesh_path)
                textures = sorted({
                    material[field]
                    for material in skin['materials']
                    for field in ['texture', 'normal', 'roughnessMap']
                    if material.get(field) not in [None, '', 'null']
                })
                for texture in textures:
                    data = read(posixpath.normpath(f'{mesh_directory}/{texture}'))
                    if not (data.startswith(b'\x89PNG\r\n\x1a\n') or data.startswith(b'\xff\xd8\xff')):
                        raise ValueError(f'{family}: invalid packaged PNG/JPEG {texture}')
                characters.append({'id': family, 'label': manifest['label'], 'mesh': mesh_path, 'textures': len(textures)})
        temp_path.replace(target)
    finally:
        temp_path.unlink(missing_ok=True)
    summary = {
        'archive': str(target.relative_to(ROOT)), 'version': package['version'],
        'bytes': target.stat().st_size, 'sha256': digest(target.read_bytes()),
        'verifiedFiles': len(records), 'characters': characters,
        'originalPmxRequired': False,
    }
    target.with_suffix('.verification.json').write_text(json.dumps(summary, ensure_ascii=False, indent=2) + '\n')
    target.with_suffix('.zip.sha256').write_text(f"{summary['sha256']}  {target.name}\n")
    print(json.dumps(summary, ensure_ascii=False, indent=2))


if __name__ == '__main__':
    main()
