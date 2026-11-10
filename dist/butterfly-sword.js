import * as THREE from './vendor/three.module.js';

// 月蝶剑 · 精修版
// 坐标约定沿用原版 W0_0：握把 z=-3.35..0，剑身 z=0..20.1，剑身宽度沿 x，厚度沿 y。
// 外观只影响显示，战斗判定仍由原版武器模型承担（见 engine.js _equip）。
export const SWORD_AXIS = Object.freeze({ grip: -3.35, bladeStart: .35, tip: 20.15 });

export const BUTTERFLY_PALETTE = Object.freeze({
  steel: 0xf2fbff, ice: 0x8fe3ff, deep: 0x1f7fa8, core: 0xbff2ff,
  gold: 0xe6c583, goldLight: 0xffe3ab, silver: 0xd5e4ee,
  red: 0xb71230, ribbon: 0x8ad9f0, grip: 0x18242f, membrane: 0xdff6ff
});

// 单张图片看不出金属反射，缺环境贴图时高光只能靠灯，金属会发灰发闷。
// 这里用程序生成一张等距柱状环境图（冷调天光 + 两个高光窗），给剑身提供可读的反射。
export function createSwordEnvironment(renderer) {
  if (!renderer || typeof document === 'undefined' || typeof THREE.PMREMGenerator !== 'function') return null;
  const canvas = document.createElement('canvas'); canvas.width = 512; canvas.height = 256;
  const ctx = canvas.getContext('2d'); if (!ctx) return null;
  const sky = ctx.createLinearGradient(0, 0, 0, 256);
  sky.addColorStop(0, '#f7fcff'); sky.addColorStop(.42, '#9dbfd2');
  sky.addColorStop(.62, '#2b3f4e'); sky.addColorStop(1, '#080e14');
  ctx.fillStyle = sky; ctx.fillRect(0, 0, 512, 256);
  const blob = (x, y, r, color) => {
    const g = ctx.createRadialGradient(x, y, 0, x, y, r);
    g.addColorStop(0, color); g.addColorStop(1, 'rgba(0,0,0,0)');
    ctx.fillStyle = g; ctx.beginPath(); ctx.arc(x, y, r, 0, Math.PI * 2); ctx.fill();
  };
  blob(148, 66, 96, 'rgba(255,247,226,.96)');   // 暖亮点：剑脊上的一条暖高光
  blob(392, 88, 74, 'rgba(188,232,255,.88)');   // 冷亮点：刃口青高光
  blob(258, 176, 132, 'rgba(96,168,220,.34)');  // 地面反光，避免下半截死黑
  const texture = new THREE.CanvasTexture(canvas);
  texture.mapping = THREE.EquirectangularReflectionMapping;
  texture.colorSpace = THREE.SRGBColorSpace;
  const pmrem = new THREE.PMREMGenerator(renderer);
  let target = null;
  try { target = pmrem.fromEquirectangular(texture); } catch (error) { console.warn('环境贴图生成失败，回落为纯灯光材质：', error); }
  texture.dispose(); pmrem.dispose();
  return target ? target.texture : null;
}

// 固定种子的冰晶与拉丝纹理：无需加载外部图片，每次创建都保持一致。
function createBladeTexture() {
  const width = 256, height = 1024;
  const pixels = new Uint8Array(width * height * 4);
  for (let y = 0; y < height; y++) {
    for (let x = 0; x < width; x++) {
      const u = x / width, v = y / height;
      const grain = Math.sin(x * .61 + Math.sin(y * .025) * 2) * 4 + Math.sin(x * .17 + y * .004) * 6;
      const facets = Math.sin(u * 25 + v * 30) * Math.sin(u * 13 - v * 48) * 9;
      const frost = Math.sin(u * 34 + Math.sin(v * 23) * 1.8) * Math.sin(v * 47 + u * 9) * 5;
      const ridge = Math.max(0, 1 - Math.abs(u - .5) * 6) * 13;
      const scratch = Math.pow(Math.max(0, Math.sin(u * 110 + v * 21)), 30) * 8;
      const light = grain + facets + frost + ridge + scratch;
      const i = (y * width + x) * 4;
      pixels[i] = Math.max(0, Math.min(255, 163 + light));
      pixels[i + 1] = Math.max(0, Math.min(255, 202 + light));
      pixels[i + 2] = Math.max(0, Math.min(255, 218 + light));
      pixels[i + 3] = 255;
    }
  }
  const texture = new THREE.DataTexture(pixels, width, height, THREE.RGBAFormat);
  texture.colorSpace = THREE.SRGBColorSpace;
  texture.magFilter = THREE.LinearFilter;
  texture.minFilter = THREE.LinearMipmapLinearFilter;
  texture.generateMipmaps = true;
  texture.needsUpdate = true;
  texture.userData.butterflyOwned = true;
  return texture;
}

function createMaterials(environment) {
  const env = { envMap: environment || null };
  const M = (options, envIntensity) => new THREE.MeshPhysicalMaterial({ ...env, envMapIntensity: envIntensity, ...options });
  return {
    // 剑身：冰蓝半透明晶体，内部自发光让它在暗背景里始终可读。
    ice: M({ color: BUTTERFLY_PALETTE.ice, metalness: .28, roughness: .3, emissive: 0x186f9a, emissiveIntensity: .08,
      clearcoat: .65, clearcoatRoughness: .2, side: THREE.DoubleSide }, 1.05),
    // 剑脊：抛光钢，roughness 压到 .06 才出镜面反射。
    steel: M({ color: BUTTERFLY_PALETTE.steel, metalness: .75, roughness: .27, clearcoat: .7, clearcoatRoughness: .15, side: THREE.DoubleSide }, 1.15),
    // 刃口高光条：不是真发光体，只是给轮廓一条亮边。
    edge: M({ color: 0xffffff, metalness: .8, roughness: .23, emissive: 0x9fe8ff, emissiveIntensity: .12, toneMapped: true }, 1.1),
    silver: M({ color: BUTTERFLY_PALETTE.silver, metalness: 1, roughness: .16, clearcoat: .8, clearcoatRoughness: .1, side: THREE.DoubleSide }, 2.2),
    gold: M({ color: BUTTERFLY_PALETTE.gold, metalness: 1, roughness: .19, emissive: 0x4a3208, emissiveIntensity: .35, side: THREE.DoubleSide }, 2.4),
    goldGlow: M({ color: BUTTERFLY_PALETTE.goldLight, metalness: .7, roughness: .22, emissive: 0xffc76a, emissiveIntensity: .12, side: THREE.DoubleSide }, 1.2),
    // 蝶翼膜：极薄、微透，靠 clearcoat 出虹彩感。
    membrane: M({ color: BUTTERFLY_PALETTE.membrane, metalness: .05, roughness: .12, clearcoat: 1, clearcoatRoughness: .03,
      transparent: true, opacity: .76, emissive: 0x2a7fa8, emissiveIntensity: .08, side: THREE.DoubleSide, depthWrite: false }, 2.6),
    grip: M({ color: BUTTERFLY_PALETTE.grip, metalness: .45, roughness: .52, clearcoat: .35, clearcoatRoughness: .4 }, 1.2),
    red: M({ color: BUTTERFLY_PALETTE.red, metalness: .18, roughness: .34, emissive: 0x5c0014, emissiveIntensity: .55, sheen: 1, sheenColor: new THREE.Color(0xff7a94), side: THREE.DoubleSide }, 1.1),
    ribbon: M({ color: BUTTERFLY_PALETTE.ribbon, metalness: .06, roughness: .3, emissive: 0x1b6d8a, emissiveIntensity: .5,
      transparent: true, opacity: .8, side: THREE.DoubleSide }, 1.8)
  };
}

export function createButterflySword({ environment = null } = {}) {
  const root = new THREE.Group(); root.name = '月蝶剑 · 精修';
  const mat = createMaterials(environment);
  const bladeTexture = createBladeTexture();
  const bladeMaterial = mat.ice.clone();
  bladeMaterial.color.set(0xffffff);
  bladeMaterial.map = bladeTexture;
  const glowMaterials = [];
  const ribbons = [];
  const glowMeshes = [];

  // —— 基础构件 ——
  const shape = (points, material, depth = .12, y = 0) => {
    const s = new THREE.Shape(); s.moveTo(...points[0]);
    for (const p of points.slice(1)) s.lineTo(...p);
    s.closePath();
    const g = new THREE.ExtrudeGeometry(s, { depth, bevelEnabled: true, bevelSize: .028, bevelThickness: .028, bevelSegments: 2 });
    const m = new THREE.Mesh(g, material); m.rotation.x = Math.PI / 2; m.position.y = y;
    root.add(m); return m;
  };
  const rod = (radius, length, z, material, segments = 14) => {
    const m = new THREE.Mesh(new THREE.CylinderGeometry(radius, radius, length, segments), material);
    m.rotation.x = Math.PI / 2; m.position.z = z; root.add(m); return m;
  };
  const bead = (x, y, z, r, material) => {
    const m = new THREE.Mesh(new THREE.IcosahedronGeometry(r, 2), material);
    m.position.set(x, y, z); root.add(m); return m;
  };
  const tube = (points, radius, material, segments = 28) => {
    const curve = new THREE.CatmullRomCurve3(points.map(p => new THREE.Vector3(...p)));
    const m = new THREE.Mesh(new THREE.TubeGeometry(curve, segments, radius, 7, false), material);
    root.add(m); return m;
  };

  // 软边发光条：中间亮、两侧压成黑（加法混合下黑色即透明），
  // 不需要贴图就能做出ray状的光晕，斜看也有体积。
  const glowStrip = (points, halfWidthAt, color, { plane = 'xz', segments = 30, intensity = 1 } = {}) => {
    const curve = new THREE.CatmullRomCurve3(points.map(p => new THREE.Vector3(...p)));
    const ref = plane === 'yz' ? new THREE.Vector3(1, 0, 0) : new THREE.Vector3(0, 1, 0);
    const positions = new Float32Array((segments + 1) * 3 * 3), colors = new Float32Array((segments + 1) * 3 * 3);
    const geometry = new THREE.BufferGeometry();
    geometry.setAttribute('position', new THREE.BufferAttribute(positions, 3));
    geometry.setAttribute('color', new THREE.BufferAttribute(colors, 3));
    const index = [];
    for (let i = 0; i < segments; i++) { const a = i * 3, b = (i + 1) * 3; index.push(a, b, a + 1, a + 1, b, b + 1, a + 1, b + 1, a + 2, a + 2, b + 1, b + 2); }
    geometry.setIndex(index);
    const base = new THREE.Color(color);
    for (let i = 0; i <= segments; i++) {
      const s = i / segments, p = curve.getPoint(s), tangent = curve.getTangent(s).normalize();
      const side = tangent.clone().cross(ref).normalize().multiplyScalar(halfWidthAt(s));
      const k = i * 9, fade = intensity * (1 - .55 * s);
      positions.set([p.x + side.x, p.y + side.y, p.z + side.z, p.x, p.y, p.z, p.x - side.x, p.y - side.y, p.z - side.z], k);
      // 中列最亮，左右列收到 ~22% 作为柔和过渡而不是硬边。
      colors.set([base.r * .22 * fade, base.g * .22 * fade, base.b * .22 * fade, base.r * fade, base.g * fade, base.b * fade, base.r * .22 * fade, base.g * .22 * fade, base.b * .22 * fade], k);
    }
    const material = new THREE.MeshBasicMaterial({ vertexColors: true, transparent: true, blending: THREE.AdditiveBlending, depthWrite: false, side: THREE.DoubleSide, toneMapped: false });
    material.userData.baseOpacity = .1;
    material.opacity = material.userData.baseOpacity;
    const mesh = new THREE.Mesh(geometry, material);
    mesh.renderOrder = 4; mesh.frustumCulled = false;
    root.add(mesh); glowMeshes.push(mesh); glowMaterials.push(material);
    return mesh;
  };

  // —— 剑身 ——
  // 叶形：护手处最宽，向剑尖收出内凹的刃线。
  const bladeOutline = [[-.56, .35], [-.89, 1.5], [-.94, 4.2], [-.88, 8.4], [-.79, 12.9], [-.63, 16.7], [-.36, 18.95], [0, 20.15],
    [.36, 18.95], [.63, 16.7], [.79, 12.9], [.88, 8.4], [.94, 4.2], [.89, 1.5], [.56, .35]];
  // 将挤出轮廓的二维坐标映射到整张纹理，正反面都能看见冰晶。
  const textureBlade = mesh => {
    const position = mesh.geometry.attributes.position, uv = mesh.geometry.attributes.uv;
    for (let i = 0; i < position.count; i++) {
      uv.setXY(i, (position.getX(i) + 1) / 2, (position.getY(i) - .35) / 19.8);
    }
    uv.needsUpdate = true;
    mesh.name = 'blade-textured';
    return mesh;
  };
  textureBlade(shape(bladeOutline, bladeMaterial, .15));
  // 内层剑脊：略窄略短，形成一道真实的棱线阴影。
  shape([[-.5, 1.35], [-.58, 5.6], [-.5, 12.4], [-.34, 16.6], [0, 19.55], [.34, 16.6], [.5, 12.4], [.58, 5.6], [.5, 1.35]], mat.steel, .055, -.085);
  textureBlade(shape([[-.3, 1.6], [-.34, 6.4], [-.3, 12.6], [-.2, 16.2], [0, 18.7], [.2, 16.2], [.3, 12.6], [.34, 6.4], [.3, 1.6]], bladeMaterial, .04, -.12));
  // 纤细的金色藤纹沿剑脊盘绕，正反面各一组。
  for (const y of [-.205, .055]) {
    tube([[0,y,1.8], [.18,y,2.8], [-.13,y,4.2], [.16,y,5.6], [-.12,y,7.0], [.11,y,8.6], [-.08,y,10.4], [.06,y,12.2], [0,y,15.5]], .035, mat.gold, 72);
    tube([[.02,y,3.2], [-.22,y,3.8], [-.12,y,4.5]], .017, mat.gold, 18);
    tube([[-.01,y,6.3], [.23,y,6.9], [.13,y,7.8]], .017, mat.gold, 18);
  }
  // 刃口亮边：沿轮廓走两条细管，暗处也能看出剑的长短。
  for (const side of [-1, 1]) {
    tube([[side * .56, 0, .4], [side * .9, 0, 4.2], [side * .87, 0, 9.2], [side * .76, 0, 14.2], [side * .5, 0, 17.9], [0, 0, 20.1]], .026, mat.edge, 34);
  }
  // 双侧内发光：一个平面在 xz，另一个在 yz，任意角度都能看到光晕。
  glowStrip([[0, 0, .8], [0, 0, 5], [0, 0, 10], [0, 0, 15], [0, 0, 19.4]], s => .16 * (1 - .62 * s), BUTTERFLY_PALETTE.core, { plane: 'xz', segments: 34, intensity: .9 });
  glowStrip([[0, 0, .8], [0, 0, 5], [0, 0, 10], [0, 0, 15], [0, 0, 19.4]], s => .08 * (1 - .5 * s), BUTTERFLY_PALETTE.core, { plane: 'yz', segments: 30, intensity: .55 });

  // —— 护手 · 蝶翼 ——
  // 每侧四片：上大翼、上小翼、下翼、下小翼；金边 + 薄膜双层，翅脉用细管。
  const wings = {
    upper: { rim: [[.06, .1], [.5, -.18], [1.3, .02], [2.1, .66], [2.78, 1.62], [3.36, 2.86], [2.3, 2.4], [1.12, 1.92], [.24, .92], [.06, .1]], depth: .16 },
    upperInner: { rim: [[.12, .14], [.5, .02], [1.22, .22], [1.94, .82], [2.92, 2.6], [2.04, 2.22], [1.08, 1.74], [.22, .82], [.12, .14]], depth: .1 },
    lower: { rim: [[.08, .16], [.32, .1], [1.02, -.16], [1.5, -.74], [1.27, -1.06], [.72, -.96], [.2, -.56], [.08, .16]], depth: .15 },
    lowerInner: { rim: [[.14, .14], [.38, .04], [1.0, -.22], [1.3, -.7], [1.15, -.85], [.7, -.78], [.22, -.48], [.14, .14]], depth: .1 }
  };
  for (const side of [-1, 1]) {
    const mirror = points => points.map(([x, z]) => [x * side, z]);
    const upper = shape(mirror(wings.upper.rim.slice(0, -1)), mat.gold, wings.upper.depth);
    shape(mirror(wings.upperInner.rim.slice(0, -1)), mat.membrane, wings.upperInner.depth, -.13);
    shape(mirror(wings.lower.rim.slice(0, -1)), mat.gold, wings.lower.depth);
    shape(mirror(wings.lowerInner.rim.slice(0, -1)), mat.membrane, wings.lowerInner.depth, -.14);
    // 金边：沿蝶翼外轮廓一圈亮金，让翼形在白墙前也不糊。
    tube(mirror(wings.upper.rim).map(([x, z]) => [x, 0, z]), .022, mat.goldGlow, 40);
    tube(mirror(wings.lower.rim).map(([x, z]) => [x, 0, z]), .02, mat.goldGlow, 28);
    // 翅脉：从翼根放射到翼尖，末端缀一颗小金珠。
    for (const [tipX, tipZ] of [[1.0, .42], [1.78, .92], [2.56, 2.08]]) {
      tube([[.14 * side, 0, .32], [tipX * .5 * side, .02, tipZ * .66], [tipX * side, .03, tipZ]], .019, mat.gold, 18);
      bead(tipX * side, .03, tipZ, .045, mat.goldGlow);
    }
    // 翼膜的极细高光，贴在靠近翼缘的位置。
    tube(mirror([[.5, -.05], [1.35, .3], [2.2, 1.1], [2.9, 2.3]]).map(([x, z]) => [x, -.16, z]), .012, mat.membrane, 20);
    upper.userData.wing = true;
  }
  // 护手中心：一颗主珠 + 两侧小珠，压住四片翼的根部。
  bead(0, -.3, .32, .44, mat.ice); bead(0, -.33, 1.1, .27, mat.ice);
  bead(0, -.34, 1.52, .16, mat.goldGlow);
  glowStrip([[0, -.32, .34], [0, -.33, .9], [0, -.33, 1.5]], s => .16 * (1 - .4 * s), BUTTERFLY_PALETTE.core, { plane: 'xz', segments: 10, intensity: .7 });

  // —— 握把 ——
  rod(.3, 3.3, -1.6, mat.grip);
  for (const z of [-3.12, -2.86, -.3, 0]) rod(.355, .12, z, mat.silver);
  for (let i = 0; i < 7; i++) {
    const z = -2.62 + i * .38;
    const diamond = new THREE.Mesh(new THREE.BoxGeometry(.34, .07, .17), mat.gold);
    diamond.position.set(0, -.28, z); diamond.rotation.z = Math.PI / 4; root.add(diamond);
    const back = diamond.clone(); back.position.y = .28; back.rotation.z = -Math.PI / 4; root.add(back);
  }
  // 配重球 + 红穗
  shape([[-.46, -3.28], [-.38, -3.82], [0, -4.4], [.38, -3.82], [.46, -3.28]], mat.silver, .2);
  bead(0, 0, -4.42, .17, mat.gold);
  for (const side of [-1, 1]) {
    tube([[.2 * side, 0, -3.86], [.62 * side, -.06, -4.16], [1.02 * side, -.04, -4.7], [1.42 * side, .05, -5.15]], .038, mat.red, 20);
    bead(1.46 * side, .06, -5.2, .11, mat.red);
  }
  bead(0, 0, -4.05, .2, mat.red);

  // —— 飘带 ——
  // 两块布片，逐帧顶点动画（正弦行进波 + 尾端摆动），替代上一版的静态几何。
  const buildRibbon = (basePoints, widthAt, material, { segments = 26, phase = 0, sway = .34, speed = 1 } = {}) => {
    const curve = new THREE.CatmullRomCurve3(basePoints.map(p => new THREE.Vector3(...p)));
    const count = (segments + 1) * 2;
    const positions = new Float32Array(count * 3);
    const geometry = new THREE.BufferGeometry();
    geometry.setAttribute('position', new THREE.BufferAttribute(positions, 3));
    const index = [];
    for (let i = 0; i < segments; i++) { const a = i * 2, b = a + 1, c = a + 2, d = a + 3; index.push(a, c, b, b, c, d); }
    geometry.setIndex(index);
    const mesh = new THREE.Mesh(geometry, material); mesh.frustumCulled = false; mesh.name = 'ribbon'; root.add(mesh);
    const samples = curve.getPoints(segments);
    const tmp = new THREE.Vector3(), tangent = new THREE.Vector3(), side = new THREE.Vector3(), up = new THREE.Vector3(0, 1, 0);
    const update = time => {
      for (let i = 0; i <= segments; i++) {
        const s = i / segments, p = samples[i];
        const wave = sway * Math.pow(s, 1.5);
        const x = p.x + Math.cos(time * 1.7 * speed + s * 3.1 + phase) * wave * .42;
        const y = p.y + Math.sin(time * 2.4 * speed + s * 4.4 + phase) * wave;
        const z = p.z + Math.sin(time * 1.3 * speed + s * 2.2 + phase) * wave * .38;
        tmp.set(x, y, z);
        const next = samples[Math.min(segments, i + 1)], prev = samples[Math.max(0, i - 1)];
        tangent.set(next.x - prev.x, next.y - prev.y, next.z - prev.z);
        if (tangent.lengthSq() < 1e-8) tangent.set(0, 0, 1);
        side.copy(tangent).cross(up);
        if (side.lengthSq() < 1e-6) side.set(1, 0, 0);
        side.normalize().multiplyScalar(widthAt(s));
        const k = i * 6;
        positions[k] = tmp.x - side.x; positions[k + 1] = tmp.y - side.y; positions[k + 2] = tmp.z - side.z;
        positions[k + 3] = tmp.x + side.x; positions[k + 4] = tmp.y + side.y; positions[k + 5] = tmp.z + side.z;
      }
      geometry.attributes.position.needsUpdate = true;
      geometry.computeVertexNormals();
      geometry.computeBoundingSphere();
    };
    update(0); ribbons.push(update);
    return mesh;
  };
  buildRibbon([[.26, -.02, -3.7], [.98, -.06, -3.34], [1.9, -.1, -2.86], [2.96, -.12, -2.52], [4.02, -.08, -2.66], [4.66, -.02, -2.94]],
    s => .13 * (1 - .62 * s), mat.ribbon, { phase: 0, sway: .36, segments: 28 });
  buildRibbon([[-.24, .04, -3.76], [-.92, .08, -3.44], [-1.78, .12, -3.02], [-2.7, .16, -2.7], [-3.6, .2, -2.88]],
    s => .1 * (1 - .6 * s), mat.ribbon, { phase: 2.1, sway: .3, segments: 24, speed: 1.12 });

  root.userData = {
    version: 'butterfly-sword-2',
    features: ['pbr-environment', 'emissive-glow', 'edge-highlight', 'dynamic-ribbon', 'vein-beads', 'membrane-wings', 'crystalline-blade', 'gold-inlay'],
    glowMaterials: glowMaterials.slice(),
    glowMeshes: glowMeshes.slice(),
    /** 每帧驱动飘带与呼吸光。time 为秒。 */
    update(time = 0) {
      for (const fn of ribbons) fn(time);
      const pulse = .82 + .18 * Math.sin(time * 2.6);
      for (const material of glowMaterials) material.opacity = material.userData.baseOpacity * pulse;
    }
  };
  return root;
}

export function disposeButterflySword(root) {
  if (!root) return;
  const textures = new Set();
  root.traverse(object => {
    if (object.geometry) object.geometry.dispose();
    for (const material of object.material ? (Array.isArray(object.material) ? object.material : [object.material]) : []) {
      if (material.map?.userData.butterflyOwned) textures.add(material.map);
      material.dispose();
    }
  });
  for (const texture of textures) texture.dispose();
  root.removeFromParent();
}