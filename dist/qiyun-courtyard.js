import * as THREE from './vendor/three.module.js';

// A complete Blender-authored battlefield. Geometry is batched by material;
// separate, continuous collision surfaces avoid catching feet in slab seams.
export const QIYUN_MAP = Object.freeze({ id: 'qiyun', name: '栖云古庭', english: 'THE CLOUDREST COURT', poem: '山风入古庭，云深一剑鸣。' });
const assetRoot = new URL('./assets/enhanced/maps/qiyun/', import.meta.url);

async function checkedFetch(url) {
  const response = await fetch(url);
  if (!response.ok) throw new Error(`栖云古庭资源读取失败：${url.pathname}`);
  return response;
}

export function decodeCourtyardGeometry(record, buffer) {
  const geometry = new THREE.BufferGeometry();
  const read = (item, Type, size) => {
    if (!item || !Number.isInteger(item.offset) || !Number.isInteger(item.count) || item.offset < 0 || item.count < 0 ||
        item.count % size || item.offset % Type.BYTES_PER_ELEMENT || item.offset + item.count * Type.BYTES_PER_ELEMENT > buffer.byteLength) {
      throw new Error('栖云古庭几何数据不完整');
    }
    return new Type(buffer, item.offset, item.count);
  };
  geometry.setAttribute('position', new THREE.BufferAttribute(read(record.positions, Float32Array, 3), 3));
  geometry.setAttribute('normal', new THREE.BufferAttribute(read(record.normals, Float32Array, 3), 3));
  geometry.setAttribute('uv', new THREE.BufferAttribute(read(record.uvs, Float32Array, 2), 2));
  geometry.setAttribute('color', new THREE.BufferAttribute(read(record.colors, Uint8Array, 4), 4, true));
  geometry.setIndex(new THREE.BufferAttribute(read(record.indices, Uint32Array, 3), 1));
  const count = geometry.attributes.position.count;
  if (geometry.attributes.normal.count !== count || geometry.attributes.uv.count !== count || geometry.attributes.color.count !== count ||
      geometry.index.array.some(index => index >= count)) throw new Error('栖云古庭顶点数据不匹配');
  geometry.computeBoundingSphere(); geometry.computeBoundingBox();
  return geometry;
}

const noiseGLSL = `
float hash21(vec2 p) { return fract(sin(dot(p,vec2(127.1,311.7)))*43758.5453); }
float noise21(vec2 p) {
  vec2 i=floor(p), f=fract(p); f=f*f*(3.0-2.0*f);
  return mix(mix(hash21(i),hash21(i+vec2(1,0)),f.x),mix(hash21(i+vec2(0,1)),hash21(i+vec2(1,1)),f.x),f.y);
}
float cloudNoise(vec2 p) { return noise21(p)*.57+noise21(p*2.03)*.28+noise21(p*4.07)*.15; }
`;

function createSky(clock) {
  const sky = new THREE.Mesh(new THREE.SphereGeometry(850, 40, 20), new THREE.ShaderMaterial({
    side: THREE.BackSide, depthWrite: false, fog: false,
    uniforms: { time: clock },
    vertexShader: 'varying vec3 skyDirection; void main(){skyDirection=position;gl_Position=projectionMatrix*modelViewMatrix*vec4(position,1.0);}',
    fragmentShader: `${noiseGLSL}
      uniform float time; varying vec3 skyDirection;
      void main(){
        vec3 d=normalize(skyDirection);
        vec3 horizon=vec3(.70,.78,.73), zenith=vec3(.24,.48,.57);
        vec3 c=mix(horizon,zenith,pow(max(0.,d.y),.65));
        vec3 sunDir=normalize(vec3(-.50,.72,.35));
        float sun=max(0.,dot(d,sunDir));
        c+=vec3(1.,.76,.43)*(pow(sun,28.)*.16+smoothstep(.9992,.99965,sun)*2.3);
        vec2 uv=d.xz/(max(.13,d.y)+.16)*2.3+vec2(time*.004,0.);
        float clouds=smoothstep(.48,.76,cloudNoise(uv));
        clouds*=smoothstep(.03,.25,d.y)*(1.-smoothstep(.7,1.,d.y));
        c=mix(c,vec3(.91,.90,.80),clouds*.64);
        gl_FragColor=vec4(c,1.);
        #include <tonemapping_fragment>
        #include <colorspace_fragment>
      }`,
  }));
  sky.name = '栖云古庭 · 天光与云层'; sky.renderOrder = -100;
  return sky;
}

function waterMaterial(clock, waterfall) {
  return new THREE.ShaderMaterial({
    side: THREE.DoubleSide, transparent: waterfall, depthWrite: !waterfall, fog: true,
    uniforms: THREE.UniformsUtils.merge([THREE.UniformsLib.fog, { time: clock }]),
    vertexShader: `varying vec3 waterPosition; varying vec2 waterUv;
      #include <fog_pars_vertex>
      void main(){waterPosition=position;waterUv=uv;vec4 mvPosition=modelViewMatrix*vec4(position,1.);gl_Position=projectionMatrix*mvPosition;
      #include <fog_vertex>
      }`,
    fragmentShader: `${noiseGLSL}
      uniform float time; varying vec3 waterPosition; varying vec2 waterUv;
      #include <fog_pars_fragment>
      void main(){
        ${waterfall ? `
        float stream=noise21(vec2(waterUv.x*18.,waterUv.y*2.+time*2.8));
        float streak=pow(noise21(vec2(waterUv.x*45.,waterUv.y*1.5+time*4.)),3.);
        float rim=smoothstep(.18,.40,stream);
        vec3 c=mix(vec3(.31,.61,.64),vec3(.80,.91,.83),rim*.8+streak*.2);
        float alpha=.26+rim*.36;
        ` : `
        vec2 p=waterPosition.xz;
        float wave=sin(p.x*2.4+time*.9)*sin(p.y*2.0-time*.7);
        vec3 n=normalize(vec3(cos(p.x*2.4+time*.9)*.07,1.,sin(p.y*2.-time*.7)*.07));
        vec3 view=normalize(cameraPosition-waterPosition);
        float fresnel=pow(1.-max(0.,dot(view,n)),3.);
        float glint=pow(max(0.,dot(reflect(-normalize(vec3(-.5,.72,.35)),n),view)),100.);
        float caustic=pow(.5+.5*sin(p.x*2.3+sin(p.y*1.8+time*.7)),13.);
        vec3 c=mix(vec3(.045,.23,.24),vec3(.44,.66,.64),fresnel*.75);
        c+=vec3(.20,.34,.22)*caustic*.25+vec3(1.,.84,.55)*glint*.7+wave*.012;
        float alpha=1.;
        `}
        gl_FragColor=vec4(c,alpha);
        #include <tonemapping_fragment>
        #include <colorspace_fragment>
        #include <fog_fragment>
      }`,
  });
}

function addWind(material, clock, canopy) {
  material.onBeforeCompile = shader => {
    shader.uniforms.courtyardTime = clock;
    shader.vertexShader = 'uniform float courtyardTime;\n' + shader.vertexShader;
    shader.vertexShader = shader.vertexShader.replace('#include <begin_vertex>', `
      vec3 transformed=vec3(position);
      float wind=sin(position.x*.61+position.z*.32+courtyardTime*.83)+sin(position.z*1.3-courtyardTime*1.2)*.35;
      transformed.x+=wind*${canopy ? '.075*smoothstep(3.,7.,position.y)' : '.025'};
      transformed.z+=sin(position.x*.8+courtyardTime*.7)*${canopy ? '.035' : '.012'};
    `);
  };
  material.customProgramCacheKey = () => `qiyun-wind-${canopy}`;
}

function createDriftingLeaves() {
  const geometry = new THREE.BufferGeometry();
  geometry.setAttribute('position', new THREE.Float32BufferAttribute([-.04,0,0, 0,.08,.02, .04,0,0, 0,-.08,-.02], 3));
  geometry.setIndex([0,1,2,0,2,3]);
  geometry.computeVertexNormals();
  const mesh = new THREE.InstancedMesh(geometry, new THREE.MeshStandardMaterial({ color: 0xc59c64, roughness: .85, side: THREE.DoubleSide }), 64);
  mesh.name = '山风落叶'; mesh.frustumCulled = false;
  const matrix = new THREE.Matrix4(), position = new THREE.Vector3(), quaternion = new THREE.Quaternion(), euler = new THREE.Euler(), scale = new THREE.Vector3(1,1,1);
  mesh.instanceMatrix.setUsage(THREE.DynamicDrawUsage);
  return { mesh, update(time) {
    for (let i=0;i<64;i++) {
      const phase = i*2.39996, t = time*.12+i*.173;
      position.set(Math.sin(phase)*24+Math.sin(time*.3+phase)*1.4, 1+((14-t%14)%14), Math.cos(phase*1.2)*23);
      quaternion.setFromEuler(euler.set(phase+time*.5,phase+time*.3,Math.sin(time+phase)));
      matrix.compose(position,quaternion,scale); mesh.setMatrixAt(i,matrix);
    }
    mesh.instanceMatrix.needsUpdate = true;
  }};
}

export async function loadQiyunCourtyard({ collisionMaterial } = {}) {
  const manifest = await (await checkedFetch(new URL('manifest.json', assetRoot))).json();
  if (manifest.format !== 'qiyun-battlefield-v1') throw new Error('栖云古庭资源版本不匹配');
  const [buffer, stoneTexture] = await Promise.all([
    checkedFetch(new URL(manifest.geometry, assetRoot)).then(response => response.arrayBuffer()),
    new THREE.TextureLoader().loadAsync(new URL('limestone.webp', assetRoot).href),
  ]);
  stoneTexture.colorSpace = THREE.SRGBColorSpace; stoneTexture.wrapS = stoneTexture.wrapT = THREE.RepeatWrapping; stoneTexture.anisotropy = 8;
  const clock = { value: 0 }, model = new THREE.Group(), geometries = [], materials = new Map(), colliders = [];
  model.name = '栖云古庭 · 山间遗迹战场';
  try {
    for (const spec of manifest.materials) {
      let material;
      if (spec.special === 'water' || spec.special === 'waterfall') material = waterMaterial(clock, spec.special === 'waterfall');
      else {
        const doubleSide = ['Leaf canopy', 'Grass and ferns', 'Wild flowers'].includes(spec.name);
        const Material = spec.special === 'distant' ? THREE.MeshBasicMaterial : THREE.MeshStandardMaterial;
        material = new Material({ color: spec.color, vertexColors: true, side: doubleSide ? THREE.DoubleSide : THREE.FrontSide,
          ...(spec.special === 'distant' ? {} : { roughness: spec.roughness, metalness: spec.metalness }),
          ...(spec.texture ? { map: stoneTexture, bumpMap: stoneTexture, bumpScale: .08 } : {}),
          ...(spec.special === 'lantern' ? { emissive: 0xffc57d, emissiveIntensity: .45 } : {}),
        });
        if (spec.name === 'Leaf canopy' || spec.name === 'Grass and ferns') addWind(material, clock, spec.name === 'Leaf canopy');
      }
      material.name = spec.name; materials.set(spec.name, material);
    }
    for (const record of manifest.meshes) {
      const geometry = decodeCourtyardGeometry(record, buffer); geometries.push(geometry);
      const mesh = new THREE.Mesh(geometry, record.collision ? collisionMaterial : materials.get(record.material)); mesh.name = record.name;
      if (record.collision) {
        // Keep these in the resource tree for disposal, with their own visibility
        // disabled. Raycaster intentionally reads them directly, like native maps.
        mesh.visible = false; mesh.userData.collisionOnly = true; colliders.push(mesh);
      } else {
        mesh.castShadow = record.castShadow && !['Still jade water', 'Waterfall veil', 'Distant mountain', 'Grass and ferns'].includes(record.material);
        mesh.receiveShadow = !['Waterfall veil', 'Distant mountain'].includes(record.material);
      }
      model.add(mesh);
    }
    const sun = new THREE.DirectionalLight(0xffe4bc, 3.0); sun.name = '栖云古庭 · 夕照'; sun.position.set(-35, 60, 25);
    sun.castShadow = true; sun.shadow.mapSize.set(2048, 2048);
    Object.assign(sun.shadow.camera, { left: -43, right: 43, top: 43, bottom: -43, near: 1, far: 130 });
    sun.shadow.bias = -.00015; sun.shadow.normalBias = .035; sun.shadow.radius = 2;
    model.add(sun, new THREE.HemisphereLight(0xc8e4e5, 0x68725a, 1.7));
    const fill = new THREE.DirectionalLight(0xb4d9e3, .45); fill.position.set(20, 16, -28); model.add(fill);
    const drifting = createDriftingLeaves(); drifting.update(0);
    model.add(createSky(clock), drifting.mesh); model.updateMatrixWorld(true);
    const bounds = new THREE.Box3(new THREE.Vector3(...manifest.bounds[0]), new THREE.Vector3(...manifest.bounds[1]));
    return {
      id: 'qiyun', enhanced: true, entry: { ...QIYUN_MAP, available: true }, metadata: { level: { integers: { PlayerHP: 1000 } } },
      model, colliders, bounds, sceneObjects: new Map(), points: [], skippedSpawns: [],
      spawns: manifest.spawns.map((p, i) => ({ name: `courtyard-${i}`, position: new THREE.Vector3(...p) })),
      fog: new THREE.FogExp2(0xa9c4be, .011), background: 0xa9c4be, sun,
      cameraPitch: .17, cameraDistance: 10,
      menuCamera: { position: [24, 17, 32], target: [0, 2.7, -5] },
      update(dt) {
        clock.value += dt;
        drifting.update(clock.value);
        // UniformsUtils clones plain uniform records; share the live clock again.
        for (const material of materials.values()) if (material.isShaderMaterial && material.uniforms.time) material.uniforms.time.value = clock.value;
      },
      onDispose() { sun.shadow.dispose(); },
    };
  } catch (error) {
    geometries.forEach(g => g.dispose()); materials.forEach(m => m.dispose()); stoneTexture.dispose();
    throw error;
  }
}
