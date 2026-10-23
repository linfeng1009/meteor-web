#!/usr/bin/env python3
"""Inventory a local Meteor Blade client and import a bounded, traceable Web subset.

No client program is executed. PAK files are opened as ZIP data containers. JPEG,
audio, geometry and original script bytes are preserved. BMP/TGA Web derivatives
are lossless PNGs; no image is resized. Requires Pillow for those derivatives.
"""
from __future__ import annotations

import argparse
from collections import Counter
import hashlib
from io import BytesIO
import json
import math
from pathlib import Path, PurePosixPath
import re
import shlex
import struct
import sys
import zipfile

from PIL import Image

# Both strings decode under GBK but produce unrelated characters. Their source
# first-comment bytes decode as 五雷塔 / 圓滿樓 in Big5; retain that explicit evidence.
SCRIPT_ENCODINGS = {'level/sn16_.pst': 'big5', 'level/sn18_.pst': 'big5'}


def digest(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def file_digest(path: Path) -> str:
    h = hashlib.sha256()
    with path.open('rb') as stream:
        for chunk in iter(lambda: stream.read(1024 * 1024), b''):
            h.update(chunk)
    return h.hexdigest()


def atomic_write(path: Path, data: bytes):
    path.parent.mkdir(parents=True, exist_ok=True)
    if path.is_file() and path.read_bytes() == data:
        return
    temporary = path.with_name(path.name + '.import-tmp')
    temporary.write_bytes(data)
    temporary.replace(path)


def text_bytes(data: bytes, preferred: str | None = None) -> tuple[str, str]:
    if all(c < 128 for c in data):
        return data.decode('ascii'), 'ascii'
    for encoding in [preferred, 'utf-8-sig', 'gbk', 'big5', 'gb18030']:
        if encoding:
            try:
                return data.decode(encoding), encoding
            except UnicodeDecodeError:
                pass
    # Mixed legacy files are identified rather than silently called UTF-8.
    candidates = [(data.decode(e, errors='replace'), e) for e in ['gbk', 'big5']]
    return min(candidates, key=lambda pair: pair[0].count('\ufffd'))


def clean_reference(name: str) -> str:
    return name.replace('\\', '/').split('/')[-1].lower()


def parse_gmb(data: bytes, strict_finite: bool = True) -> dict:
    if data[:10] != b'GMDL V1.00':
        raise ValueError('unsupported GMB header')
    offset = 10

    def unpack(fmt: str):
        nonlocal offset
        size = struct.calcsize('<' + fmt)
        if offset + size > len(data):
            raise ValueError('truncated GMB')
        values = struct.unpack_from('<' + fmt, data, offset)
        offset += size
        return values[0] if len(values) == 1 else values

    def string() -> str:
        nonlocal offset
        n = unpack('i')
        if not 0 <= n <= 65536 or offset + n > len(data):
            raise ValueError('invalid GMB string')
        value = text_bytes(data[offset:offset + n].rstrip(b'\0'))[0]
        offset += n
        return value

    nt = unpack('i')
    if not 0 <= nt < 4096:
        raise ValueError('invalid GMB texture count')
    textures = [string() for _ in range(nt)]
    ns = unpack('i')
    if not 0 <= ns < 4096:
        raise ValueError('invalid GMB shader count')
    shaders = []
    for _ in range(ns):
        shaders.append(dict(texture=unpack('i'), mode=string(), twoSide=bool(unpack('B')),
                            blend=string(), opacity=unpack('f')))
    count, dummies, vertex_count, face_count = unpack('4i')
    if not 0 <= count <= 10000 or not 0 <= vertex_count <= 5000000 or not 0 <= face_count <= 5000000:
        raise ValueError('invalid GMB geometry count')
    objects = []
    total_v = total_f = 0
    bounds_min = [math.inf] * 3
    bounds_max = [-math.inf] * 3
    invalid_vertices = []
    for _ in range(count):
        name = string()
        nv, nf = unpack('2i')
        if nv < 0 or nf < 0 or total_v + nv > vertex_count or total_f + nf > face_count:
            raise ValueError('invalid GMB object count')
        lo, hi = [math.inf] * 3, [-math.inf] * 3
        for vertex_index in range(nv):
            values = unpack('6f4B2f')
            if not all(math.isfinite(v) for v in values[:6] + values[10:]):
                if strict_finite:
                    raise ValueError('nonfinite GMB vertex')
                invalid_vertices.append(dict(object=name, vertex=vertex_index, byteOffset=offset - 36,
                                             nonfiniteComponents=[i for i, v in enumerate(values) if isinstance(v, float) and not math.isfinite(v)]))
            for axis, value in enumerate(values[:3]):
                if math.isfinite(value):
                    lo[axis] = min(lo[axis], value)
                    hi[axis] = max(hi[axis], value)
        used = set()
        for _ in range(nf):
            shader, a, b, c, *_ = unpack('4i3f')
            if not -1 <= shader < ns or any(i < 0 or i >= nv for i in [a, b, c]):
                raise ValueError('invalid GMB face reference')
            used.add(shader)
        if nv:
            for axis in range(3):
                bounds_min[axis] = min(bounds_min[axis], lo[axis])
                bounds_max[axis] = max(bounds_max[axis], hi[axis])
        objects.append(dict(name=name, vertices=nv, triangles=nf, shaders=sorted(used),
                            bounds=dict(min=[v if math.isfinite(v) else None for v in lo],
                                        max=[v if math.isfinite(v) else None for v in hi]) if nv else None))
        total_v += nv
        total_f += nf
    if offset != len(data) or total_v != vertex_count or total_f != face_count:
        raise ValueError('GMB geometry totals/trailing bytes do not match')
    return dict(format='GMB', textures=textures, shaders=shaders, objectCount=count,
                dummyCount=dummies, vertexCount=vertex_count, triangleCount=face_count,
                bounds=dict(min=[v if math.isfinite(v) else None for v in bounds_min],
                            max=[v if math.isfinite(v) else None for v in bounds_max]),
                objects=objects, bytesConsumed=offset, renderable=not invalid_vertices,
                invalidVertexCount=len(invalid_vertices), invalidVertexSamples=invalid_vertices[:16])


def parse_gmc(data: bytes) -> dict:
    text, encoding = text_bytes(data)
    body = re.sub(r'#[^\r\n]*', '', text)
    textures = re.search(r'Textures\s+(\d+)\s*\{([^}]+)\}', body, re.I)
    objects = []
    for match in re.finditer(r'Object\s+(\S+)\s*\{([^}]+)\}', body, re.I):
        block = match.group(2)
        points = [[float(v) for v in m] for m in re.findall(r'^\s*v\s+([\deE.+-]+)\s+([\deE.+-]+)\s+([\deE.+-]+)', block, re.M)]
        faces = re.findall(r'^\s*f\s+(-?\d+)\s+(\d+)\s+(\d+)\s+(\d+)', block, re.M)
        if not all(math.isfinite(v) for p in points for v in p):
            raise ValueError('nonfinite GMC vertex')
        if any(any(int(i) >= len(points) for i in face[1:]) for face in faces):
            raise ValueError('invalid GMC face index')
        objects.append(dict(name=match.group(1), vertices=len(points), triangles=len(faces),
                            bounds=dict(min=[min(p[a] for p in points) for a in range(3)],
                                        max=[max(p[a] for p in points) for a in range(3)]) if points else None))
    return dict(format='GMC', encoding=encoding, textures=textures.group(2).split() if textures else [],
                objectCount=len(objects), vertexCount=sum(o['vertices'] for o in objects),
                triangleCount=sum(o['triangles'] for o in objects), objects=objects)


def parse_des(data: bytes) -> dict:
    text, encoding = text_bytes(data)
    header = re.search(r'SceneObjects\s+(\d+)\s+Dumm?eyObjects\s+(\d+)', text, re.I)
    objects = []
    # Balanced braces retain the nested Custom blocks; simple .*?} loses flags.
    for match in re.finditer(r'Object\s+(\S+)\s*\{', text):
        start = match.end()
        depth, end = 1, start
        while depth and end < len(text):
            depth += (text[end] == '{') - (text[end] == '}')
            end += 1
        block = text[start:end - 1]
        fields = {}
        for key in ['Position', 'Quaternion', 'TextureAnimation']:
            field = re.search(rf'{key}:\s*([^\r\n]+)', block, re.I)
            if field:
                fields[key[0].lower() + key[1:]] = [float(v) for v in field.group(1).split()]
        properties = dict((m.group(1).lower(), m.group(2).strip()) for m in re.finditer(r'^\s*(\w+)\s*=\s*([^\r\n}]+)', block, re.M))
        objects.append(dict(name=match.group(1), **fields, properties=properties))
    return dict(format='DES', encoding=encoding, sceneObjects=int(header.group(1)) if header else None,
                dummyObjects=int(header.group(2)) if header else None, objects=objects)


def parse_pst(data: bytes, preferred: str | None = None) -> dict:
    text, encoding = text_bytes(data, preferred)
    name = re.match(r'\s*//\s*([^\r\n]+)', text)
    ints = {m.group(1): int(m.group(2)) for m in re.finditer(r'^\s*int\s+(\w+)\s*=\s*(-?\d+)\s*;', text, re.M)}
    strings = {m.group(1): m.group(2) for m in re.finditer(r'^\s*string\s+(\w+)\s*=\s*"([^"\r\n]*)"\s*;', text, re.M)}
    functions = re.findall(r'^\s*(\w+)\s*\([^\r\n]*\)\s*\{', text, re.M)
    return dict(format='PST', encoding=encoding, comment=name.group(1).strip() if name else None,
                integers=ints, strings=strings, functions=functions,
                includes=re.findall(r'#include\s+"([^"]+)"', text),
                npcScripts=list(dict.fromkeys(re.findall(r'AddNPC\("([^"]+)"\)', text))))


def parse_wp(data: bytes) -> dict:
    lines = text_bytes(data)[0].splitlines()
    points = []
    i = 1
    declared = int(lines[0].split()[1]) if lines else 0
    while i < len(lines):
        if not lines[i].strip():
            i += 1
            continue
        if not lines[i].startswith('Pos '):
            raise ValueError('unexpected waypoint line')
        position = list(map(float, lines[i].split()[1:]))
        size = float(lines[i + 1].split()[1])
        count = int(lines[i + 2].split()[1])
        links = []
        for line in lines[i + 3:i + 3 + count]:
            target, flag, distance = line.split()
            links.append(dict(target=int(target), flag=int(flag), distance=float(distance)))
        points.append(dict(id=len(points), position=position, size=size, links=links))
        i += 3 + count
    if len(points) != declared or any(link['target'] >= declared for p in points for link in p['links']):
        raise ValueError('waypoint count/index mismatch')
    return dict(format='WP', count=declared, coordinateSystem='native Z up; no visual offset applied', points=points)


def parse_cob(data: bytes) -> dict:
    # The full collision semantics remain a reverse engineering task.
    return dict(format='COB', signature=data[:10].rstrip(b'\0').decode('ascii', errors='replace'),
                size=len(data), headerHex=data[:64].hex(), semanticsParsed=False)


def parse_resource_names(data: bytes) -> list[dict]:
    strings = []
    for offset in range(len(data) - 4):
        n = struct.unpack_from('<I', data, offset)[0]
        if 2 <= n <= 80 and offset + 4 + n <= len(data):
            value = data[offset + 4:offset + 4 + n]
            if value.endswith(b'\0') and not any(c < 32 for c in value[:-1]):
                try:
                    strings.append(dict(offset=offset, value=value[:-1].decode('big5')))
                except UnicodeDecodeError:
                    pass
    result = []
    for previous, current in zip(strings, strings[1:]):
        if re.fullmatch(r'W\d+_\d+[abrl]?', current['value'], re.I):
            if previous['offset'] + 4 + len(previous['value'].encode('big5')) + 1 == current['offset']:
                result.append(dict(name=previous['value'], modelId=current['value'].lower(),
                                   nameOffset=previous['offset'], modelOffset=current['offset'],
                                   evidence='adjacent int32 byte-length-prefixed Big5 strings in Meteor.res; not a full RES parser'))
    return result


class Importer:
    def __init__(self, source: Path, output: Path, dry_run: bool = False):
        self.source, self.output, self.dry_run = source, output, dry_run
        try:
            self.previous_assets = json.loads((output / 'manifest.json').read_text()).get('assets', [])
        except (FileNotFoundError, json.JSONDecodeError):
            self.previous_assets = []
        self.files = sorted(p for p in source.rglob('*') if p.is_file())
        self.sources = {p.relative_to(source).as_posix(): dict(path=p.relative_to(source).as_posix(),
                       bytes=p.stat().st_size, sha256=file_digest(p)) for p in self.files}
        self.archives = {}
        self.archive_index = {}
        self.assets = []
        self.warnings = []
        for path in self.files:
            if path.suffix.lower() == '.pak' and zipfile.is_zipfile(path):
                rel = path.relative_to(source).as_posix()
                archive = zipfile.ZipFile(path)
                self.archives[rel.lower()] = archive
                members = {}
                for info in archive.infolist():
                    if not info.is_dir():
                        members.setdefault(clean_reference(info.filename), []).append(info)
                self.archive_index[rel.lower()] = members

    def read(self, path: str, archive: str | None = None):
        if archive:
            key = archive.lower()
            options = self.archive_index[key].get(clean_reference(path), [])
            if not options:
                raise FileNotFoundError(f'{archive}::{path}')
            info = options[0]
            data = self.archives[key].read(info)
            source = dict(self.sources[next(r for r in self.sources if r.lower() == key)], archiveMember=info.filename,
                          memberSha256=digest(data), memberBytes=len(data), memberCrc32=f'{info.CRC:08x}')
            return data, source
        found = next((r for r in self.sources if r.lower() == path.lower()), None)
        if found is None:
            raise FileNotFoundError(path)
        return (self.source / found).read_bytes(), dict(self.sources[found])

    def write(self, url: str, data: bytes, source: dict | list | None = None, transform: str = 'byte copy'):
        url = PurePosixPath(url.lower()).as_posix()
        if '..' in PurePosixPath(url).parts or url.startswith('/'):
            raise ValueError('unsafe output path')
        dest = self.output / url
        if not self.dry_run:
            atomic_write(dest, data)
        record = dict(url=url, bytes=len(data), sha256=digest(data), transform=transform)
        if source:
            record['sources' if isinstance(source, list) else 'source'] = source
        self.assets.append(record)
        return record

    def json(self, url: str, value, source=None):
        return self.write(url, (json.dumps(value, ensure_ascii=False, indent=2, allow_nan=False) + '\n').encode(), source, 'parsed metadata JSON')

    def raw(self, path: str, url: str, archive: str | None = None):
        data, source = self.read(path, archive)
        return self.write(url, data, source)

    def image(self, path: str, directory: str, archive: str | None = None):
        data, source = self.read(path, archive)
        name = clean_reference(path)
        with Image.open(BytesIO(data)) as im:
            width, height = im.size
            if name.endswith(('.jpg', '.jpeg', '.png')):
                record = self.write(f'{directory}/{name}', data, source)
            else:
                # Also retain the exact original mask/texture bytes for verification.
                self.write(f'{directory}/native/{name}', data, source)
                encoded = BytesIO()
                im.save(encoded, format='PNG', optimize=False)
                record = self.write(f'{directory}/{Path(name).stem}.png', encoded.getvalue(), source, 'lossless PNG; original dimensions and palette/alpha preserved')
            return dict(record, width=width, height=height, reference=name)

    def texture(self, reference: str, directory: str, archives: list[str], loose_directories: list[str]):
        name = clean_reference(reference)
        data = source = origin = None
        for archive in archives:
            if archive.lower() in self.archives and name in self.archive_index[archive.lower()]:
                data, source = self.read(name, archive)
                origin = archive
                break
        if data is None:
            for prefix in loose_directories:
                try:
                    data, source = self.read(f'{prefix}/{name}')
                    origin = None
                    break
                except FileNotFoundError:
                    pass
        if data is None:
            self.warnings.append(f'missing texture {reference} for {directory}')
            return dict(reference=reference, missing=True)
        native_path = name if origin else source['path']
        if name.endswith('.ifl'):
            sequence = self.write(f'{directory}/{name}', data, source)
            frames = []
            for line in text_bytes(data)[0].splitlines():
                frame = line.split()[0] if line.split() else ''
                if Path(frame).suffix.lower() in ('.jpg', '.bmp', '.png', '.tga'):
                    frames.append(self.texture(frame, directory, archives, loose_directories))
            return dict(reference=reference, sequence=sequence['url'], frames=frames,
                        url=next((f.get('url') for f in frames if f.get('url')), None))
        record = self.image(native_path, directory, origin)
        record['reference'] = reference
        mask_name = str(Path(name).with_suffix('.bmp'))
        if name.endswith(('.jpg', '.jpeg')):
            for archive in archives:
                if archive.lower() in self.archives and mask_name in self.archive_index[archive.lower()]:
                    record['alphaMask'] = self.image(mask_name, directory, archive)['url']
                    break
        return record

    def close(self):
        for archive in self.archives.values():
            archive.close()


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--source', required=True, type=Path, help='read-only local client directory')
    parser.add_argument('--output', required=True, type=Path, help='Web asset output directory')
    parser.add_argument('--maps', default='all', help='all (default), or comma-separated actual scene IDs')
    parser.add_argument('--dry-run', action='store_true', help='calculate exact output size without creating or changing files')
    parser.add_argument('--inventory', type=Path, default=Path(__file__).resolve().parents[1] / 'work/meteor-original/evidence/resource-inventory.json')
    args = parser.parse_args()
    source, output = args.source.resolve(), args.output.resolve()
    if not source.is_dir() or output == source or source in output.parents:
        parser.error('source must exist, and output must be outside the read-only source directory')
    importer = Importer(source, output, args.dry_run)
    try:
        menu_data, menu_source = importer.read('menu.res')
        menu, menu_encoding = text_bytes(menu_data)
        menu_lines = menu.splitlines()
        start = menu_lines.index('钟乳洞')
        menu_names = {f'sn{i + 1:02d}': name for i, name in enumerate(menu_lines[start:start + 20])}
        res_data, res_source = importer.read('Meteor.res')
        weapon_names = parse_resource_names(res_data)
        all_maps = []
        for directory in sorted(p for p in source.iterdir() if p.is_dir() and re.fullmatch(r'sn\d+', p.name, re.I)):
            scene = directory.name.lower()
            record = dict(id=scene, files=[], name=None, nameEvidence=[])
            script_path = f'Level/{scene}_.pst'
            try:
                data, ref = importer.read(script_path)
                level = parse_pst(data, SCRIPT_ENCODINGS.get(script_path.lower()))
                record['level'] = dict(level, source=ref)
                if level['comment'] and '\ufffd' not in level['comment']:
                    record['name'] = level['comment']
                    record['nameEvidence'].append(dict(source=ref, field='first comment', encoding=level['encoding'], value=level['comment']))
            except FileNotFoundError:
                pass
            menu_name = menu_names.get(scene)
            if menu_name:
                record['nameEvidence'].append(dict(source=menu_source, encoding=menu_encoding, field=f'map list ordinal {int(scene[2:])}', value=menu_name))
                if not re.match(r'第.+个$', menu_name):
                    record['name'] = menu_name
            for path in sorted(directory.iterdir()):
                ext = path.suffix.lower()
                if ext not in ('.gmb', '.gmc', '.des', '.cob', '.pst'):
                    continue
                ref = importer.sources[path.relative_to(source).as_posix()]
                item = dict(ref)
                try:
                    item['parsed'] = {'.gmb': parse_gmb, '.gmc': parse_gmc, '.des': parse_des,
                                      '.cob': parse_cob, '.pst': parse_pst}[ext](path.read_bytes())
                except (ValueError, struct.error) as error:
                    item['parseError'] = str(error)
                    if ext == '.gmb' and str(error) == 'nonfinite GMB vertex':
                        item['parsed'] = parse_gmb(path.read_bytes(), strict_finite=False)
                record['files'].append(item)
            wp_path = f'Level/{scene}.wp'
            try:
                data, ref = importer.read(wp_path)
                record['waypoints'] = dict(parse_wp(data), source=ref)
            except FileNotFoundError:
                pass
            all_maps.append(record)

        selected_ids = ([m['id'] for m in all_maps] if args.maps.strip().lower() == 'all'
                        else [k.strip().lower() for k in args.maps.split(',') if k.strip()])
        selected_maps = []
        scene_sources = []
        for scene in selected_ids:
            original = next(m for m in all_maps if m['id'] == scene)
            model_file = next(i for i in original['files'] if i['path'].lower().endswith(f'/{scene}.gmb'))
            entry = dict(id=scene, name=original['name'], nameEvidence=original['nameEvidence'], textures=[],
                         available='parseError' not in model_file)
            if not entry['available']:
                entry['unavailableReason'] = model_file['parseError']
            directory = f'maps/{scene}'
            for ext, field in [('gmb', 'model'), ('des', 'description'), ('cob', 'collision'), ('pst', 'sceneScript')]:
                path = f'{scene}/{scene}.{ext}'
                try:
                    entry[field] = importer.raw(path, f'{directory}/{scene}.{ext}')['url']
                except FileNotFoundError:
                    continue
            if entry.get('sceneScript'):
                scene_path = f'{scene}/{scene}.pst'
                data, ref = importer.read(scene_path)
                decoded, encoding = text_bytes(data)
                entry['sceneFile'] = scene_path
                entry['sceneScriptUtf8'] = importer.write(f'{directory}/{scene}.pst.utf8.txt', decoded.replace('\r\n', '\n').encode(), ref,
                                                         f'decode {encoding} to UTF-8; CRLF to LF')['url']
            entry['scriptSources'] = []
            for script_file in (f for f in original['files'] if f['path'].lower().endswith('.pst')):
                path = script_file['path']
                data, ref = importer.read(path)
                decoded, encoding = text_bytes(data)
                raw = importer.write(f'{directory}/{Path(path).name}', data, ref)['url']
                utf8 = importer.write(f'{directory}/{Path(path).name}.utf8.txt', decoded.replace('\r\n', '\n').encode(), ref,
                                      f'decode {encoding} to UTF-8; CRLF to LF')['url']
                source_record = dict(source=ref, raw=raw, utf8=utf8, encoding=encoding)
                entry['scriptSources'].append(source_record)
                scene_sources.append(source_record)
            model = model_file['parsed']
            used_shaders = {s for obj in model['objects'] for s in obj['shaders'] if s >= 0}
            used_textures = {model['shaders'][s]['texture'] for s in used_shaders}
            for index, reference in enumerate(model['textures']):
                if index not in used_textures:
                    entry['textures'].append(dict(reference=reference, unused=True))
                else:
                    entry['textures'].append(importer.texture(reference, f'{directory}/textures',
                                            [f'{scene}.pak', 'TexturePatch.pak', 'ctexture.pak'], ['texture', scene]))
            for path, field in [(f'Level/{scene}_.pst', 'levelScript'), (f'Level/{scene}.wp', 'waypoints')]:
                try:
                    entry[field] = importer.raw(path, f'{directory}/{Path(path).name}')['url']
                    if field == 'levelScript':
                        entry['levelScriptUtf8'] = f'scripts/level/{scene}_.pst.utf8.txt'
                except FileNotFoundError:
                    pass
            metadata = dict(original)
            metadata_sources = [{k: v for k, v in f.items() if k not in ('parsed', 'parseError')} for f in original['files']]
            metadata_sources += [original[k]['source'] for k in ('level', 'waypoints') if k in original]
            entry['metadata'] = importer.json(f'{directory}/metadata.json', metadata, metadata_sources)['url']
            entry['stats'] = {k: model[k] for k in ['objectCount', 'vertexCount', 'triangleCount', 'bounds']}
            selected_maps.append(entry)

        weapons = []
        for model_id, kind, npc in [('w0_0', 'sword', 'Sword'), ('w5_0', 'blade', 'Blade'), ('w7_0', 'spear', 'Lance')]:
            directory = f'weapons/{model_id}'
            data, ref = importer.read(f'cmodel/{model_id}.gmc')
            parsed = parse_gmc(data)
            evidence = next((w for w in weapon_names if w['modelId'] == model_id), None)
            npc_data, npc_source = importer.read(f'Level/{npc}.pst')
            weapons.append(dict(id=model_id, type=kind,
                name=evidence['name'] if evidence else None, resourceEvidence=dict(evidence or {}, source=res_source),
                npcEvidence=dict(parse_pst(npc_data), source=npc_source),
                model=importer.write(f'{directory}/{model_id}.gmc', data, ref)['url'],
                description=importer.raw(f'cmodel/{model_id}.des', f'{directory}/{model_id}.des')['url'],
                textures=[importer.texture(t, f'{directory}/textures', ['ctexture.pak', 'TexturePatch.pak'], ['texture', 'cmodel']) for t in parsed['textures']],
                stats={k: parsed[k] for k in ['objectCount', 'vertexCount', 'triangleCount']}))

        ui = []
        for path in sorted((source / 'image').iterdir()):
            if path.suffix.lower() in ('.jpg', '.jpeg', '.bmp', '.png', '.tga'):
                record = importer.image(path.relative_to(source).as_posix(), 'ui/image')
                ui.append(dict(record, id=f'image/{path.name}'))
        for name in sorted(importer.archive_index.get('uitexture.pak', {})):
            if Path(name).suffix in ('.jpg', '.jpeg', '.bmp', '.png', '.tga'):
                record = importer.image(name, 'ui/texture', 'UITexture.pak')
                ui.append(dict(record, id=f'UITexture/{name}'))
        # Paired grayscale BMP/JPEG files are the client's explicit alpha/color pairs.
        for name in sorted(importer.archive_index.get('uitexture.pak', {})):
            if not name.endswith(('.jpg', '.jpeg')):
                continue
            mask = str(Path(name).with_suffix('.bmp'))
            if mask not in importer.archive_index['uitexture.pak']:
                continue
            rgb_data, rgb_source = importer.read(name, 'UITexture.pak')
            mask_data, mask_source = importer.read(mask, 'UITexture.pak')
            with Image.open(BytesIO(rgb_data)) as rgb, Image.open(BytesIO(mask_data)) as alpha:
                if rgb.size != alpha.size:
                    continue
                rgba = rgb.convert('RGBA')
                rgba.putalpha(alpha.convert('L'))
                encoded = BytesIO()
                rgba.save(encoded, format='PNG', optimize=False)
                record = importer.write(f'ui/texture/{Path(name).stem}.rgba.png', encoded.getvalue(),
                                        [rgb_source, mask_source], 'JPG color + paired BMP luminance alpha; original dimensions')
                ui.append(dict(record, id=f'UITexture/{name}+{mask}', width=rgb.width, height=rgb.height, derivedAlpha=True))

        effects = []
        for name in sorted(importer.archive_index.get('waves.pak', {})):
            if name.endswith('.wav'):
                effects.append(dict(importer.raw(name, f'sounds/effects/{name}', 'waves.pak'), id=Path(name).stem))
        effect_definitions = []
        for path in sorted((source / 'SFX').iterdir()):
            if path.suffix.lower() not in ('.ef', '.lst'):
                continue
            rel = path.relative_to(source).as_posix()
            data, ref = importer.read(rel)
            record = importer.write(f'sounds/definitions/{path.name}', data, ref)
            wavs = [s.decode('ascii') for s in re.findall(rb'[A-Za-z0-9_./\\-]+\.wav', data, re.I)]
            effect_definitions.append(dict(record, id=path.stem, signature=data[:11].decode('ascii', errors='replace'),
                                           soundReferences=list(dict.fromkeys(wavs))))
        music = []
        for name in ['menu.mp3', 's1.mp3', 's6.mp3', 's10.mp3']:
            music.append(dict(importer.raw(f'music/{name}', f'sounds/music/{name}'), id=Path(name).stem))
        scripts = []
        for directory in ['Level', 'PScriptLib']:
            for path in sorted((source / directory).iterdir()):
                if path.suffix.lower() not in ('.pst', '.wp', '.h'):
                    continue
                rel = path.relative_to(source).as_posix()
                data, ref = importer.read(rel)
                raw = importer.write(f'scripts/{rel}', data, ref)
                text, encoding = text_bytes(data, SCRIPT_ENCODINGS.get(rel.lower()))
                decoded = importer.write(f'scripts/{directory}/{path.name}.utf8.txt', text.replace('\r\n', '\n').encode(), ref, f'decode {encoding} to UTF-8; CRLF to LF')
                scripts.append(dict(source=ref, raw=raw['url'], utf8=decoded['url'], encoding=encoding))
        scripts.extend(scene_sources)
        importer.raw('menu.res', 'ui/menu.res')
        importer.write('ui/menu.utf8.txt', menu.encode(), menu_source, f'decode {menu_encoding} to UTF-8')

        pak_inventory = []
        for rel, archive in sorted(importer.archives.items()):
            source_ref = importer.sources[next(r for r in importer.sources if r.lower() == rel)]
            pak_inventory.append(dict(source_ref, container='ZIP', members=[dict(name=i.filename, bytes=i.file_size,
                 compressedBytes=i.compress_size, crc32=f'{i.CRC:08x}') for i in archive.infolist()]))
        cmodel_inventory = []
        for path in sorted((source / 'cmodel').iterdir()):
            if path.suffix.lower() in ('.gmb', '.gmc'):
                try:
                    parsed = (parse_gmb if path.suffix.lower() == '.gmb' else parse_gmc)(path.read_bytes())
                    cmodel_inventory.append(dict(source=importer.sources[path.relative_to(source).as_posix()], parsed=parsed))
                except ValueError as error:
                    cmodel_inventory.append(dict(path=path.name, error=str(error)))
        fingerprint = digest('\n'.join(f'{r}:{v["sha256"]}' for r, v in sorted(importer.sources.items())).encode())
        map_variants = []
        for scene in (m['id'] for m in all_maps):
            for extension in ['gmb', 'gmc', 'des', 'cob', 'pst']:
                loose_path = f'{scene}/{scene}.{extension}'
                loose_ref = next((v for k, v in importer.sources.items() if k.lower() == loose_path), None)
                if not loose_ref:
                    continue
                variant = dict(scene=scene, extension=extension, selected='loose', loose=loose_ref)
                try:
                    _, packed_ref = importer.read(f'{scene}.{extension}', f'{scene}.pak')
                    variant['packed'] = packed_ref
                    variant['identical'] = loose_ref['sha256'] == packed_ref['memberSha256']
                except (FileNotFoundError, KeyError):
                    variant['packed'] = None
                    variant['identical'] = None
                map_variants.append(variant)
        inventory = dict(schemaVersion=1, sourceRoot=str(source), sourceFingerprint=fingerprint,
            files=list(importer.sources.values()), archives=pak_inventory, maps=all_maps,
            cmodels=cmodel_inventory, resourceWeaponStrings=weapon_names, textEncodingOverrides=SCRIPT_ENCODINGS,
            mapVariants=map_variants,
            stats=dict(fileCount=len(importer.files), bytes=sum(v['bytes'] for v in importer.sources.values()),
                       extensions=dict(Counter(p.suffix.lower() for p in importer.files)), mapCount=len(all_maps), zipPakCount=len(pak_inventory)))
        if not args.dry_run:
            atomic_write(args.inventory, (json.dumps(inventory, ensure_ascii=False, indent=2, allow_nan=False) + '\n').encode())
            report = ['# 本地资源来源与变体对照', '',
                f'只读分析客户端 `{source.name}`。源文件 {len(importer.files)} 个，共 {inventory["stats"]["bytes"]:,} 字节；识别 {len(pak_inventory)} 个 ZIP 格式 PAK。未运行客户端程序、安装程序或下载的工具。', '',
                f'完整源清单指纹（按路径排序的文件 SHA-256）：`{fingerprint}`。', '',
                '## 地图来源', '',
                '中文名称来自本地 `menu.res` 的地图序列及 `Level/snXX_.pst` 首行注释，GBK / Big5 编码分别记录在 JSON 证据中。没有名称证据的场景保持空值；本包没有识别到“蝴蝶谷”，`sn01` 实际为“钟乳洞”。', '',
                '| 场景 | 本地证据名称 | GMB 顶点 / 三角形 | 导入可用性 |',
                '| --- | --- | --- | --- |']
            for scene in all_maps:
                geometry = next((f for f in scene['files'] if f['path'].lower().endswith('.gmb')), {})
                parsed = geometry.get('parsed', {})
                counts = f'{parsed.get("vertexCount", "?")} / {parsed.get("triangleCount", "?")}'
                report.append(f'| {scene["id"]} | {scene["name"] or "未确认"} | {counts} | {geometry.get("parseError", "数据可解析")} |')
            report += ['', '## 独立目录与 PAK 内同名文件', '',
                '本次明确选择独立目录中的模型、描述、碰撞及场景脚本；贴图优先取对应场景 PAK。该选择是可复现的导入策略，不是对原程序文件覆盖优先级的结论。独立 DES 与 PAK 内的差异说明该下载包不能被视为已验证的官方纯净版本。', '',
                '| 场景 / 格式 | 独立文件 SHA-256 | PAK 成员 SHA-256 | 是否相同 |',
                '| --- | --- | --- | --- |']
            for variant in map_variants:
                packed_hash = variant['packed']['memberSha256'] if variant['packed'] else '无同名条目'
                status = '相同' if variant['identical'] is True else '不同' if variant['identical'] is False else '仅独立文件'
                report.append(f'| {variant["scene"]} / {variant["extension"]} | `{variant["loose"]["sha256"]}` | `{packed_hash}` | {status} |')
            report += ['', '## 导入边界', '',
                'GMB / GMC 解析校验顶点、三角形索引、计数及文件边界；DES 保留位置、四元数和 Custom 属性；WP 保留原生 Z 向上坐标和连接图；PST 原字节与 UTF-8 阅读副本均保留。COB 仅识别 `COL V1.0` 等头部并原样复制，尚未实现其空间单元语义。', '',
                '`sn22.gmb` 含非有限顶点，输出保留原字节与错误偏移，manifest 明确 `available: false`，不能交给渲染器。贴图未缩放；JPEG、音乐和音效保持源字节，BMP / TGA 另生成无损 PNG。UI 配对 BMP / JPEG 的合成另有明确转换记录。', '',
                '本地持有和公开下载不构成素材再发行或商业授权；权利仍归原权利人。', '',
                '## 复现', '', '```sh',
                f'python3 scripts/import-original.py --source {shlex.quote(str(source))} --output dist/assets/original --maps all',
                '```', '']
            atomic_write(args.inventory.with_name('resource-source-report.md'), '\n'.join(report).encode())
        # Deduplicate records generated by a shared texture or IFL sequence.
        assets = sorted({a['url']: a for a in importer.assets}.values(), key=lambda a: a['url'])
        current_urls = {a['url'] for a in assets}
        for old in importer.previous_assets if not args.dry_run else []:
            url = old.get('url', '')
            stale = output / url
            if url not in current_urls and url and '..' not in PurePosixPath(url).parts and not url.startswith('/'):
                if stale.is_file() and file_digest(stale) == old.get('sha256'):
                    stale.unlink()  # Only a prior, unchanged importer-owned artifact.
        manifest = dict(schemaVersion=1, source=dict(label=source.name, fingerprint=fingerprint,
            fileCount=len(importer.files), bytes=inventory['stats']['bytes'], policy='read-only data extraction; no executable run'),
            maps=selected_maps, mapCatalog=[dict(id=m['id'], name=m['name'], nameEvidence=m['nameEvidence']) for m in all_maps],
            weapons=weapons, ui=ui, sounds=dict(effects=effects, music=music, effectDefinitions=effect_definitions), scripts=scripts,
            assets=assets, stats=dict(assetCount=len(assets), bytes=sum(a['bytes'] for a in assets), mapCount=len(selected_maps),
            weaponCount=len(weapons), uiCount=len(ui), soundCount=len(effects), scriptCount=len(scripts),
            effectDefinitionCount=len(effect_definitions), availableMapCount=sum(m['available'] for m in selected_maps)),
            missingRequestedResources=[dict(name='蝴蝶谷', status='not identified in this local client; sn01 is 钟乳洞, not 蝴蝶谷')],
            limitations=['COB is copied and identified; collision cell semantics are not implemented by this importer.',
                        'Map DES loose-file versions differ from packed copies; loose client versions are selected and hashed explicitly.',
                        'Names without menu/script evidence remain null; archive member names are retained verbatim as provenance.',
                        'Copyright and redistribution permission are not inferred from local possession.'],
            warnings=importer.warnings)
        manifest_data = (json.dumps(manifest, ensure_ascii=False, indent=2, allow_nan=False) + '\n').encode()
        if not args.dry_run:
            atomic_write(output / 'manifest.json', manifest_data)
        print(json.dumps(dict(manifest=str(output / 'manifest.json'), inventory=str(args.inventory),
                              **manifest['stats'], manifestBytes=len(manifest_data), dryRun=args.dry_run,
                              warnings=importer.warnings), ensure_ascii=False, indent=2))
    finally:
        importer.close()


if __name__ == '__main__':
    main()
