// AMB1 retains every BANIM byte. It groups each 32-bit track by byte lane
// after encoding its second differences so gzip can see repeated values.
const headerSize = 21;
const signatureSize = 4;

export function animationPackLayout(buffer) {
  const view = new DataView(buffer);
  if (view.byteLength < headerSize ||
    new TextDecoder().decode(new Uint8Array(buffer, 0, 5)) !== 'BANIM') throw new Error('Invalid BANIM header');
  const bones = view.getUint32(5, true), dummies = view.getUint32(9, true), frames = view.getUint32(13, true);
  const stride = 20 + bones * 16 + dummies * 33;
  if (!bones || bones > 512 || dummies > 512 || !frames || headerSize + stride * frames !== view.byteLength) {
    throw new Error('Invalid BANIM dimensions');
  }
  const widths = Array(5 + bones * 4).fill(4);
  for (let i = 0; i < dummies; i++) widths.push(1, 4, ...Array(7).fill(4));
  return { frames, stride, widths };
}

export function unpackNativeAnimation(packed) {
  const input = new Uint8Array(packed);
  if (input.length < headerSize + signatureSize ||
    new TextDecoder().decode(input.subarray(0, signatureSize)) !== 'AMB1') throw new Error('Invalid AMB1 signature');
  const buffer = new ArrayBuffer(input.length - signatureSize);
  const output = new Uint8Array(buffer);
  output.set(input.subarray(signatureSize, signatureSize + headerSize));
  const { frames, stride, widths } = animationPackLayout(buffer), view = new DataView(buffer);
  let field = 0, lane = signatureSize + headerSize;
  for (const width of widths) {
    let previous = 0, delta = 0;
    for (let frame = 0; frame < frames; frame++) {
      const at = headerSize + frame * stride + field, index = lane + frame;
      if (width === 1) { output[at] = input[index]; continue; }
      const encoded = (input[index] | input[index + frames] << 8 |
        input[index + 2 * frames] << 16 | input[index + 3 * frames] << 24) >>> 0;
      delta = (delta + ((encoded >>> 1) ^ -(encoded & 1))) | 0;
      previous = (previous + delta) | 0;
      view.setInt32(at, previous, true);
    }
    field += width;
    lane += width * frames;
  }
  return buffer;
}
