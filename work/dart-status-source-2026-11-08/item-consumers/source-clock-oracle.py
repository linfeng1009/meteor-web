"""Independent arithmetic trace of inspected original item loop; not EXE execution."""
import hashlib
import json
from pathlib import Path
import struct

HERE = Path(__file__).resolve().parent
STEP = struct.unpack('<f', struct.pack('<I', 0x3E4CCCCD))[0]
records = json.loads((HERE / 'original-item-records.json').read_text())['records']

def trace(record):
    params = {p['words'][0]: p['words'][1] for p in record['parameters']}
    words = record['effects'][0]['words']
    remaining, counter = params[2], words[9]
    threshold = words[3] * 10
    rate_step = params[8] * STEP
    elapsed, ticks, states = 0, [], []
    while elapsed < 10000:
        elapsed += 1
        # 004d50b1 FCOMP / TEST AH,41 / JP continuing branch:
        # ordered finite remaining <= rate*dt deletes before effect processing.
        if remaining <= rate_step:
            states.append({'step': elapsed, 'nominalSeconds': round(elapsed / 5, 6),
                           'expired': True, 'remainingBefore': remaining, 'counterBefore': counter})
            break
        remaining -= int(rate_step)
        # 004d4e98 CMP counter,period*10 / JC accumulating branch.
        if counter < threshold:
            counter = int(counter + 10 * STEP)
        else:
            ticks.append(elapsed)
            counter = 0
        if elapsed <= 17:
            states.append({'step': elapsed, 'nominalSeconds': round(elapsed / 5, 6),
                           'remaining': remaining, 'counter': counter,
                           'ticked': elapsed in ticks})
    return {'id': record['id'], 'sourcePeriodWord': words[3], 'sourceLifetime': params[2],
            'rate': params[8], 'firstTickStep': ticks[0] if ticks else None,
            'tickSteps': ticks, 'nominalTickSeconds': [round(n / 5, 6) for n in ticks],
            'tickCount': len(ticks), 'nominalExpirySeconds': elapsed / 5,
            'states': states}

result = {'source': '004abe80 timer5Hz → 004b1d60 fixedfloat.2 → 004b24e0 → 004d5020 → 004d4e30',
          'clockBits': '0x3e4ccccd', 'clockFloat32': STEP,
          'modelBoundary': 'Independent source arithmetic only. Item insertion phase, OS timer stalls, actor death, client rendering and game gameplay are not simulated.',
          'traces': [trace(r) for r in records if r['id'] in [11, 12]]}
assert result['traces'][0]['firstTickStep'] == 16
assert result['traces'][0]['tickCount'] == 4
assert result['traces'][1]['firstTickStep'] == 11
assert result['traces'][1]['tickCount'] == 27
(HERE / 'source-clock-oracle.json').write_text(json.dumps(result, ensure_ascii=False, indent=2) + '\n')
print(json.dumps([{k: t[k] for k in ['id', 'firstTickStep', 'tickCount', 'nominalExpirySeconds']}
                  for t in result['traces']], ensure_ascii=False))
