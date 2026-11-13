#!/usr/bin/env python3
"""Convert enhanced-character textures to WebP and rewrite the references.

Why: the imported characters ship 1024-4096 px PNG/JPG atlases (126 MB total,
12 MB in the boot path). WebP keeps them visually identical at ~5-10% of the
bytes, which is the difference between a usable and an unusable page on a
3 Mbit link.

Safety rules:
  * alpha is preserved (RGBA in, RGBA out),
  * every conversion is measured with PSNR; anything below MIN_PSNR is retried
    at a higher quality and finally left as PNG,
  * the original file is deleted only after no text file references it.

    python3 scripts/convert_textures_webp.py [--apply]
"""
import io
import json
import os
import re
import sys
from pathlib import Path

from PIL import Image
import numpy as np

ROOT = Path(__file__).resolve().parents[1]
DIST = ROOT / 'dist'
APPLY = '--apply' in sys.argv
MIN_PSNR = 36.0
SCAN_EXT = ('.json', '.js', '.mjs', '.html', '.css')
TARGETS = [DIST / 'assets/enhanced', DIST / 'assets/menu']


def candidates():
    for base in TARGETS:
        for dirpath, _, files in os.walk(base):
            for name in files:
                if Path(name).suffix.lower() in ('.png', '.jpg', '.jpeg'):
                    yield Path(dirpath) / name


def psnr(a, b, mask=None, step=3):
    """PSNR over visible pixels only.

    Fully transparent texels keep arbitrary colour in most atlases; counting
    them made clean encodings look catastrophic (a mask scored 6.8 dB).
    """
    x, y = a[::step, ::step].astype(np.float32), b[::step, ::step].astype(np.float32)
    if mask is not None:
        keep = mask[::step, ::step] > 8
        if keep.any():
            x, y = x[keep], y[keep]
    mse = np.mean((x - y) ** 2)
    return 99.0 if mse == 0 else 10 * np.log10(255 ** 2 / mse)


def encode(im, budget):
    """Lossy first; fall back to lossless only when lossy visibly degrades.

    method=4 keeps the whole-library pass to a few minutes; lossless is reserved
    for the small mask/detail atlases where lossy WebP struggles with hard edges.
    """
    has_alpha = im.mode in ('RGBA', 'LA') or (im.mode == 'P' and 'transparency' in im.info)
    work = im.convert('RGBA' if has_alpha else 'RGB')
    original = np.asarray(work.convert('RGB'))
    alpha = np.asarray(work.split()[-1]) if has_alpha else None

    def attempt(quality, lossless):
        buf = io.BytesIO()
        work.save(buf, 'WEBP', quality=quality, method=4, lossless=lossless)
        reopened = Image.open(io.BytesIO(buf.getvalue()))
        decoded = np.asarray(reopened.convert('RGB'))
        alpha_error = 0
        if has_alpha:
            alpha_error = float(np.abs(np.asarray(reopened.convert('RGBA').split()[-1]).astype(np.int16)
                                       - alpha.astype(np.int16)).mean())
        return buf.getvalue(), quality, lossless, psnr(original, decoded, alpha) - alpha_error * 2

    result = attempt(90, False)
    if result[3] < 34.0:
        # Masks and razor-sharp alpha edges: lossless is both smaller and exact.
        lossless = attempt(100, True)
        if lossless[3] >= result[3] or len(lossless[0]) < budget:
            result = lossless
    return result, has_alpha


_text_cache = None


def text_files():
    global _text_cache
    if _text_cache is None:
        _text_cache = []
        for dirpath, _, files in os.walk(DIST):
            for f in files:
                if f.endswith(SCAN_EXT):
                    path = Path(dirpath) / f
                    try:
                        _text_cache.append((path, path.read_text(encoding='utf-8', errors='ignore')))
                    except OSError:
                        pass
    return _text_cache


def references(name):
    pattern = re.compile(re.escape(name))
    return [path for path, text in text_files() if pattern.search(text)]


def rewrite(name, replacement):
    global _text_cache
    pattern = re.compile(re.escape(name))
    changed = 0
    updated_cache = []
    for path, text in text_files():
        updated = pattern.sub(replacement, text)
        if updated != text:
            path.write_text(updated, encoding='utf-8')
            changed += 1
        updated_cache.append((path, updated))
    _text_cache = updated_cache
    return changed


total_before = total_after = 0
converted = kept = 0
report = []
for path in sorted(candidates()):
    before = path.stat().st_size
    if before < 20_000:  # tiny icons/masks: not worth the risk
        kept += 1
        continue
    try:
        im = Image.open(path)
        payload, quality, lossless, score = encode(im, before)[0]
    except Exception as error:  # noqa: BLE001 - report and keep the original
        report.append((path, before, before, f'skip: {error}'))
        kept += 1
        continue
    if score < MIN_PSNR:
        report.append((path, before, before, f'kept png (psnr {score:.1f})'))
        kept += 1
        continue
    target = path.with_suffix('.webp')
    total_before += before
    total_after += len(payload)
    converted += 1
    report.append((path, before, len(payload), f'q{quality}{" lossless" if lossless else ""} psnr {score:.1f}'))
    if converted % 20 == 0:
        print(f'  …{converted} converted, {total_before/1e6:.0f}MB -> {total_after/1e6:.1f}MB', flush=True)
    if not APPLY:
        continue
    target.write_bytes(payload)
    changed = rewrite(path.name, target.name)
    if changed or not references(path.name):
        path.unlink()
        # Stale precompressed sidecars would otherwise linger for a dead file.
        for suffix in ('.br', '.gz'):
            side = Path(str(path) + suffix)
            if side.exists(): side.unlink()

print(f'{converted} converted, {kept} kept')
print(f'{total_before/1e6:.1f} MB -> {total_after/1e6:.2f} MB ({100*total_after/max(total_before,1):.0f}%)')
worst = sorted(report, key=lambda r: r[3])[:6]
print('lowest-margin conversions:')
for path, b, a, note in sorted(report, key=lambda r: r[2] / max(r[1], 1), reverse=True)[:6]:
    print(f'  {path.relative_to(DIST)} {b/1e6:.2f}->{a/1e6:.3f}MB {note}')
if not APPLY:
    print('\n(dry run — pass --apply to write)')