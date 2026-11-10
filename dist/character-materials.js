import * as THREE from './vendor/three.module.js';

export function configureSourceMaterial(material,spec){
  if(spec.hairSurface){material.anisotropy=spec.anisotropy??.35;material.specularIntensity=.4;}
  else if(spec.skinSurface&&material.isMeshPhysicalMaterial){material.specularIntensity=.35;material.roughness=spec.roughnessMap?1:(spec.roughness??.6);}
  if(spec.normalEncoding!=='unity-rg-or-ag'&&spec.roughnessChannel!=='r')return;
  material.customProgramCacheKey=()=>`source-material:${spec.normalEncoding||'rgb'}:${spec.roughnessChannel||'g'}`;
  material.onBeforeCompile=shader=>{
    if(spec.normalEncoding==='unity-rg-or-ag'){
      const chunk=THREE.ShaderChunk.normal_fragment_maps.replace(
        'vec3 mapN = texture2D( normalMap, vNormalMapUv ).xyz * 2.0 - 1.0;',
        'vec4 sourcePackedNormal = texture2D( normalMap, vNormalMapUv );\n vec2 sourceNormalXY = vec2( sourcePackedNormal.r * sourcePackedNormal.a, sourcePackedNormal.g ) * 2.0 - 1.0;\n vec3 mapN = vec3( sourceNormalXY, sqrt( max( 1.0 - dot( sourceNormalXY, sourceNormalXY ), 0.0 ) ) );'
      );
      shader.fragmentShader=shader.fragmentShader.replace('#include <normal_fragment_maps>',chunk);
    }
    if(spec.roughnessChannel==='r')shader.fragmentShader=shader.fragmentShader.replace('#include <roughnessmap_fragment>',THREE.ShaderChunk.roughnessmap_fragment.replace('texelRoughness.g','texelRoughness.r'));
  };
}
