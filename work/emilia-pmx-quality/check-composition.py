"""Read-only independent check of source alpha overlay vs the exported map."""
from pathlib import Path
from PIL import Image, ImageChops, ImageStat
import hashlib, json
ROOT = Path(__file__).resolve().parents[2]
SOURCE = Path('/Users/dulinfeng/Downloads/Emilia_v1/tex')
OUTPUT = ROOT / 'dist/assets/enhanced/emilia/textures/cloth-composed.png'
base = Image.open(SOURCE / 'CLOTH.png').convert('RGBA')
overlay = Image.open(SOURCE / 'SDW.png').convert('RGBA')
actual = Image.open(OUTPUT).convert('RGBA')
expected = Image.alpha_composite(base, overlay)
difference = ImageChops.difference(expected, actual)
report = dict(sourceSize=list(base.size), overlaySize=list(overlay.size), outputSize=list(actual.size), differenceExtrema=difference.getextrema(), meanAbsoluteChannelError=ImageStat.Stat(difference).mean, outputAlpha=actual.getchannel('A').getextrema(), method='Independent Pillow straight-alpha SDW over original CLOTH (PNG channel space)', inputHashes={name:hashlib.sha256((SOURCE/name).read_bytes()).hexdigest() for name in ['CLOTH.png','SDW.png']}, outputHash=hashlib.sha256(OUTPUT.read_bytes()).hexdigest())
assert all(hi == 0 for lo, hi in report['differenceExtrema']), report
assert base.size == overlay.size == actual.size == (2048, 2048)
(ROOT / 'work/emilia-pmx-quality/composition-audit.json').write_text(json.dumps(report, indent=2))
print(json.dumps(report, indent=2))
