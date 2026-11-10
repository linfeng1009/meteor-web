import * as THREE from './vendor/three.module.js';

// 按原版 W7_0 的握持点与长度制作。局部 +z 为枪尖，装入原骨骼时旋转 x=π/2。
export const PHOENIX_SPEAR_AXIS = Object.freeze({ tip: 31.9, tail: -22.9 });

function surfaceTexture(kind) {
  const width = 128, height = 512, data = new Uint8Array(width * height * 4);
  for (let y = 0; y < height; y++) for (let x = 0; x < width; x++) {
    const u = x / width, v = y / height;
    const grain = Math.sin(x * 1.81 + Math.sin(y * .05)) * 3;
    const crystal = Math.sin(u * 29 + v * 36) * Math.sin(u * 17 - v * 28) * 13;
    const vein = Math.pow(Math.max(0, Math.sin(u * 40 + Math.sin(v * 22) * 2)), 18) * 16;
    const k = (y * width + x) * 4;
    const base = kind === 'ice' ? [141, 193, 216] : kind === 'silk' ? [225, 228, 235] : [198, 210, 218];
    const detail = kind === 'ice' ? crystal + vein + grain : kind === 'silk' ? Math.sin(x * 3) * 4 + Math.sin(y * 3) * 3 : grain + Math.sin(x * .7) * 8;
    for (let c = 0; c < 3; c++) data[k + c] = THREE.MathUtils.clamp(base[c] + detail, 0, 255);
    data[k + 3] = 255;
  }
  const texture = new THREE.DataTexture(data, width, height, THREE.RGBAFormat);
  texture.colorSpace = THREE.SRGBColorSpace;
  texture.magFilter = THREE.LinearFilter; texture.minFilter = THREE.LinearMipmapLinearFilter;
  texture.generateMipmaps = true; texture.needsUpdate = true;
  texture.userData.phoenixOwned = true;
  return texture;
}

export function createPhoenixSpear({ environment = null } = {}) {
  const root = new THREE.Group(); root.name = '霜翎凤鸣枪';
  const iceTexture = surfaceTexture('ice'), steelTexture = surfaceTexture('steel'), silkTexture = surfaceTexture('silk');
  const physical = options => new THREE.MeshPhysicalMaterial({ envMap: environment, envMapIntensity: .85, side: THREE.DoubleSide, ...options });
  const mat = {
    steel: physical({ color: 0xffffff, map: steelTexture, metalness: .68, roughness: .3, clearcoat: .5, clearcoatRoughness: .2 }),
    feather: physical({ color: 0xe3eff9, map: steelTexture, metalness: .45, roughness: .34, clearcoat: .4 }),
    blue: physical({ color: 0x80b9da, map: steelTexture, metalness: .48, roughness: .35 }),
    ice: physical({ color: 0xffffff, map: iceTexture, metalness: .25, roughness: .24, clearcoat: .8, clearcoatRoughness: .15, emissive: 0x16445c, emissiveIntensity: .08 }),
    core: physical({ color: 0xca426e, map: iceTexture, metalness: .25, roughness: .23, clearcoat: 1, emissive: 0x5c0a2d, emissiveIntensity: .12 }),
    gold: physical({ color: 0xd3b276, metalness: .78, roughness: .3, clearcoat: .4 }),
    jade: physical({ color: 0xafdace, metalness: .12, roughness: .24, clearcoat: .8 }),
    eye: physical({ color: 0x123a60, metalness: .5, roughness: .2 }),
    silk: physical({ color: 0xf3f0f2, map: silkTexture, roughness: .72, metalness: .02, sheen: .65, sheenColor: new THREE.Color(0xb3cde9), transparent: true, opacity: .86 }),
    pinkSilk: physical({ color: 0xc66a8e, map: silkTexture, roughness: .65, sheen: .6, transparent: true, opacity: .9 })
  };
  const add = (geometry, material, name = '') => {
    const mesh = new THREE.Mesh(geometry, material); mesh.name = name; root.add(mesh); return mesh;
  };
  const shape = (points, material, depth = .12, y = 0, name = '') => {
    const outline = new THREE.Shape(); outline.moveTo(...points[0]);
    for (const p of points.slice(1)) outline.lineTo(...p); outline.closePath();
    const geometry = new THREE.ExtrudeGeometry(outline, { depth, bevelEnabled: true, bevelSize: .025, bevelThickness: .025, bevelSegments: 2 });
    const position = geometry.attributes.position, uv = geometry.attributes.uv;
    geometry.computeBoundingBox();
    const box = geometry.boundingBox, width = Math.max(.001, box.max.x - box.min.x), length = Math.max(.001, box.max.y - box.min.y);
    for (let i = 0; i < position.count; i++) uv.setXY(i, (position.getX(i) - box.min.x) / width, (position.getY(i) - box.min.y) / length);
    const mesh = add(geometry, material, name); mesh.rotation.x = Math.PI / 2; mesh.position.y = y; return mesh;
  };
  const tube = (points, radius, material, segments = 24, name = '') => add(new THREE.TubeGeometry(new THREE.CatmullRomCurve3(points.map(p => new THREE.Vector3(...p))), segments, radius, 6, false), material, name);
  const rod = (radius, length, z, material) => {
    const mesh = add(new THREE.CylinderGeometry(radius, radius, length, 12), material); mesh.rotation.x = Math.PI / 2; mesh.position.z = z; return mesh;
  };
  const gem = (x, y, z, radius, material, elongation = 1) => {
    const mesh = add(new THREE.IcosahedronGeometry(radius, 1), material); mesh.position.set(x, y, z); mesh.scale.z = elongation; return mesh;
  };
  const ring = (x, y, z, radius, thickness, material) => {
    const mesh = add(new THREE.TorusGeometry(radius, thickness, 8, 32), material); mesh.rotation.x = Math.PI / 2; mesh.position.set(x, y, z); return mesh;
  };
  const blade = (low, high, width, material, name) => {
    // 每面三角切面在中心形成真实棱线，避免平面自发光遮住晶体纹理。
    const shoulder = low + (high - low) * .38, middle = low + (high - low) * .46;
    const vertices = [[0,0,low],[-width,0,shoulder],[0,0,high],[width,0,shoulder],[0,-.26,middle],[0,.26,middle]];
    const faces = [[0,4,1],[1,4,2],[2,4,3],[3,4,0],[0,1,5],[1,2,5],[2,3,5],[3,0,5]];
    const p = [], uv = [];
    for (const face of faces) for (const i of face) { p.push(...vertices[i]); uv.push((vertices[i][0] / width + 1) / 2, (vertices[i][2] - low) / (high - low)); }
    const geometry = new THREE.BufferGeometry(); geometry.setAttribute('position', new THREE.Float32BufferAttribute(p, 3)); geometry.setAttribute('uv', new THREE.Float32BufferAttribute(uv, 2)); geometry.computeVertexNormals();
    return add(geometry, material, name);
  };

  // 银白枪杆，绕杆的金藤是真实几何，转动时可读。
  rod(.235, 31.7, .9, mat.steel);
  for (const z of [-14.9,-13.8,14.8,16.4]) rod(.32, .18, z, mat.gold);
  const spiral = [];
  for (let i = 0; i <= 150; i++) { const s = i / 150, angle = s * Math.PI * 12; spiral.push([Math.cos(angle) * .25, Math.sin(angle) * .25, -14 + s * 30]); }
  tube(spiral, .035, mat.gold, 150, 'gold-shaft-inlay');
  for (const z of [-12,-5,2,9]) {
    rod(.25,.5,z,mat.blue);
    for (const offset of [-.28,.28]) rod(.27,.07,z+offset,mat.gold);
  }

  // 冰晶双尖与绯红内芯。
  blade(20.1, PHOENIX_SPEAR_AXIS.tip, 1.13, mat.ice, 'phoenix-head-blade');
  for (const side of [-1,1]) {
    const y = side * .285;
    shape([[0,21.15],[-.42,24.1],[-.3,26.1],[0,29.5],[.3,26.1],[.42,24.1]],mat.core,.045,y,'phoenix-crimson-core');
    tube([[0,y,21.1],[-.44,y,24.1],[-.31,y,26.1],[0,y,29.5]],.027,mat.gold,24);
    tube([[0,y,21.1],[.44,y,24.1],[.31,y,26.1],[0,y,29.5]],.027,mat.gold,24);
    for (let i = 0; i < 5; i++) {
      const z = 22.1 + i * 1.12;
      tube([[-.58+i*.06,y,z],[0,y,z+.65],[.46-i*.06,y,z+1.3]],.012,mat.feather,12);
    }
  }

  // 凤翼分层羽片：每片有银白羽面、浅蓝背羽与金色羽轴。
  const feather = (base, tip, width, material, y, name) => {
    const dx = tip[0]-base[0], dz = tip[1]-base[1], length = Math.hypot(dx,dz), nx = -dz/length, nz=dx/length;
    const point = (s,w=0) => { const bend = Math.sin(Math.PI*s)*width*1.4; return [base[0]+dx*s+nx*(w+bend),base[1]+dz*s+nz*(w+bend)]; };
    const contour = [];
    for(let i=0;i<=12;i++){const t=i/12;contour.push(point(t,Math.pow(Math.sin(Math.PI*t),.8)*width*.9));}
    for(let i=11;i>=0;i--){const t=i/12;contour.push(point(t,-Math.pow(Math.sin(Math.PI*t),.8)*width*.64));}
    const mesh = shape(contour,material,.07,y,name);
    tube([0,.25,.5,.75,1].map(t=>{const p=point(t);return[p[0],y-.09,p[1]];}),.016,mat.gold,18);
    return mesh;
  };
  for (const side of [-1,1]) {
    // 向上扬起的主翼与向外下垂的尾翎，轮廓呼应参考图。
    for (let i = 0; i < 7; i++) {
      const t=i/6;
      feather([side*(.28+t*.66),20.9+t*.45],[side*(1.3+t*2.2),26.65-t*2.45],.34+t*.11,i%2?mat.feather:mat.blue,-.2-i*.018,'phoenix-upper-feather');
    }
    for (let i = 0; i < 5; i++) {
      const t=i/4;
      feather([side*.6,20.5],[side*(2.1+t*2.3),22.4-t*3.1],.37,mat.feather,-.31-i*.018,'phoenix-lower-feather');
    }
    tube([[side*.45,-.5,20.2],[side*1.4,-.48,21.75],[side*2.9,-.4,21.9],[side*4.35,-.3,19.35]],.055,mat.gold,32);
    // 根部覆羽隐藏羽片的交汇。
    for(let i=0;i<4;i++) feather([side*.13,19.5+i*.25],[side*(.85+i*.22),21.25+i*.43],.22,mat.feather,-.6-i*.025,'phoenix-cover-feather');
  }
  // 飞凤颈、头与喙，压在晶芯前方。
  tube([[0,-.7,19.45],[-.58,-.75,20.4],[-.63,-.78,21.35],[.15,-.8,22.25],[.54,-.8,22.52]],.19,mat.blue,32,'phoenix-neck');
  tube([[-.05,-.91,19.65],[-.49,-.96,20.45],[-.35,-.98,21.45],[.3,-.98,22.3]],.075,mat.feather,26);
  gem(.52,-.81,22.55,.24,mat.feather,.85);
  shape([[.58,22.6],[1.16,22.35],[.61,22.33]],mat.gold,.09,-.85,'phoenix-beak');
  gem(.59,-1.03,22.61,.055,mat.eye);
  for(let i=0;i<3;i++) feather([.29,22.55],[-.12-i*.2,23.4+i*.14],.09,mat.feather,-.85,'phoenix-crown');

  // 青玉环、项圈和细链坠饰。
  ring(0,0,17.9,.75,.15,mat.jade);
  // 环的两端与枪杆、凤身相接，避免悬空的装饰部件。
  rod(.17,.65,16.85,mat.steel);rod(.2,.8,19.1,mat.gold);
  for(const z of [16.8,18.9]) { rod(.38,.18,z,mat.gold); gem(0,0,z,.29,mat.jade); }
  for(const side of [-1,1]) {
    tube([[side*.6,0,18.3],[side*1.4,-.05,18.7],[side*1.65,-.08,17.5]],.035,mat.gold,18);
    for(let i=0;i<8;i++) { const link=ring(side*(1.6+.08*Math.sin(i)),0,17.3-i*.31,.075,.018,mat.gold); if(i%2)link.rotation.y=Math.PI/2; }
    gem(side*1.65,0,14.6,.16,mat.ice,2.2);
  }
  // 红绳结与小白花。
  for(let i=0;i<5;i++) {const a=i*Math.PI*2/5;ring(-1.4+Math.cos(a)*.22,-.23,16.1+Math.sin(a)*.22,.16,.035,mat.core);gem(-1.45+Math.cos(a)*.16,-.36,15.45+Math.sin(a)*.16,.12,mat.feather);}
  gem(-1.45,-.48,15.45,.1,mat.gold);

  // 枪尾与枪头呼应，用小型凤翼护住第二枚绯红冰晶。
  rod(.16,1.5,-15.55,mat.steel);
  gem(0,0,-15.7,.42,mat.jade); ring(0,0,-15.7,.43,.045,mat.gold);
  blade(PHOENIX_SPEAR_AXIS.tail,-17.4,.62,mat.ice,'phoenix-tail-blade');
  for(const y of [-.3,.32])shape([[0,-18.2],[-.25,-19.1],[0,-21.8],[.25,-19.1]],mat.core,.035,y);
  for(const side of [-1,1]) {
    tube([[0,0,-16.2],[side*.75,0,-17.3],[side*.45,0,-18.9],[0,0,-20.1]],.06,mat.gold,26);
    gem(side*.72,0,-17.65,.36,mat.jade,1.5);
    for(let i=0;i<4;i++) feather([side*.35,-19.4+i*.15],[side*(1.7-i*.22),-17.4-i*.48],.2,mat.feather,-.25,'phoenix-tail-feather');
  }

  // 两条白绡夹一条绯红绸带；固定根部、尾部摆动，长度控制在枪杆上半段。
  const ribbons = [];
  const ribbon = (points, width, material, phase) => {
    const segments=36, curve=new THREE.CatmullRomCurve3(points.map(p=>new THREE.Vector3(...p))), samples=curve.getPoints(segments);
    const geometry=new THREE.BufferGeometry(), positions=new Float32Array((segments+1)*6), uv=[], indices=[];
    geometry.setAttribute('position',new THREE.BufferAttribute(positions,3));
    for(let i=0;i<=segments;i++){uv.push(0,i/segments,1,i/segments);if(i<segments){const a=i*2;indices.push(a,a+2,a+1,a+1,a+2,a+3);}}
    geometry.setAttribute('uv',new THREE.Float32BufferAttribute(uv,2));geometry.setIndex(indices);
    const mesh=add(geometry,material,'phoenix-ribbon');mesh.frustumCulled=false;
    const update=time=>{
      for(let i=0;i<=segments;i++){
        const t=i/segments,p=samples[i],w=width*Math.sin(Math.PI*(t*.88+.08))*(1-t*.75),sway=t*t;
        const x=p.x+Math.sin(time*1.8+t*5+phase)*sway*.4,y=p.y+Math.sin(time*2.1+t*6+phase)*sway*.35;
        positions.set([x-w,y,p.z,x+w,y+.035,p.z],i*6);
      }
      geometry.attributes.position.needsUpdate=true;geometry.computeVertexNormals();geometry.computeBoundingSphere();
    };
    update(0);ribbons.push(update);
  };
  ribbon([[-1.2,-.15,16],[-2.8,-.12,14.2],[-4.9,0,10.7],[-4.2,.15,7.2],[-2.7,.2,4.8]],.65,mat.silk,0);
  ribbon([[-1.25,-.27,16],[-2.6,-.3,13.6],[-4,-.18,10],[-3.8,0,6.8],[-2.2,.1,4.5]],.48,mat.pinkSilk,1.7);
  ribbon([[-1.3,-.38,15.9],[-3.5,-.38,14.5],[-5.6,-.2,11.8],[-5.2,-.1,9.6],[-3.6,.05,8]],.48,mat.silk,3.2);
  root.userData={version:'phoenix-spear-1',features:['faceted-ice','crimson-core','layered-phoenix-feathers','gold-inlay','jade-charms','dynamic-ribbons'],update(time=0){for(const animate of ribbons)animate(time);}};
  return root;
}

export function disposePhoenixSpear(root) {
  if(!root)return;
  const geometries=new Set(),materials=new Set(),textures=new Set();
  root.traverse(mesh=>{
    if(mesh.geometry)geometries.add(mesh.geometry);
    for(const material of mesh.material?(Array.isArray(mesh.material)?mesh.material:[mesh.material]):[]){materials.add(material);for(const value of Object.values(material))if(value?.isTexture&&value.userData.phoenixOwned)textures.add(value);}
  });
  for(const geometry of geometries)geometry.dispose();for(const material of materials)material.dispose();for(const texture of textures)texture.dispose();
  root.removeFromParent();
}
