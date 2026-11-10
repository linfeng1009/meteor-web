"""Convert the user-provided standalone weapon PMX as inert, local geometry.
No source files or character meshes are modified. AL1's duplicate triangles are
merged into the corresponding base faces as an alpha-masked emission material.
"""
from pathlib import Path
import argparse, collections, hashlib, json, math, shutil, sys
from PIL import Image, ImageChops
sys.path.insert(0,str(Path(__file__).resolve().parent/'blender'))
from pmx_reader import PMXReader
ROOT=Path(__file__).resolve().parents[1]
DEFAULT=Path('/Users/dulinfeng/Downloads/人物模型/【模之屋】雷电将军_by_原神_535ff740fe45cbd49822311479d93d94')

def main():
 parser=argparse.ArgumentParser();parser.add_argument('--source',type=Path,default=DEFAULT);args=parser.parse_args();source=args.source
 output=ROOT/'dist/assets/enhanced/weapons/raiden-sword';work=ROOT/'work/raiden-sword'
 for directory in [output,output/'textures',work]:directory.mkdir(parents=True,exist_ok=True)
 pmx=PMXReader(source/'武器.pmx').parse();(work/'source-audit.json').write_text(json.dumps(pmx.summary(),ensure_ascii=False,indent=2))
 grip_z=pmx.bones[0]['position'][2];cross_section=[]
 for i in range(0,len(pmx.indices),3):
  face=pmx.indices[i:i+3]
  for a,b in zip(face,face[1:]+face[:1]):
   pa,pb=pmx.vertices[a]['position'],pmx.vertices[b]['position']
   if min(pa[2],pb[2])<=grip_z<=max(pa[2],pb[2]) and abs(pa[2]-pb[2])>1e-8:
    t=(grip_z-pa[2])/(pb[2]-pa[2]);cross_section.append([pa[k]+t*(pb[k]-pa[k]) for k in range(3)])
 if not cross_section:raise ValueError('Grip cross section is missing')
 grip_x=(min(p[0] for p in cross_section)+max(p[0] for p in cross_section))/2
 source_tip=min(v['position'][2] for v in pmx.vertices);scale=20.03/(grip_z-source_tip)
 positions=[];normals=[];uvs=[]
 for vertex in pmx.vertices:
  x,y,z=vertex['position'];nx,ny,nz=vertex['normal']
  positions.extend([round((x-grip_x)*scale,7),round(y*scale,7),round((grip_z-z)*scale,7)])
  normals.extend([nx,ny,-nz]);uvs.extend([vertex['uv'][0],1-vertex['uv'][1]])
 materials=[dict(name='紫金刀装',texture='textures/color.png',metalness=.3,roughness=.42,emissiveIntensity=0),dict(name='紫刃纹饰',texture='textures/color.png',metalness=.28,roughness=.32,emissive='textures/color.png',emissiveIntensity=.12),dict(name='刀身',texture='textures/color.png',metalness=.3,roughness=.3,emissive='textures/color.png',emissiveIntensity=.16),dict(name='刀装发光纹',texture='textures/color.png',metalness=.3,roughness=.4,emissive='textures/emission.png',emissiveIntensity=.35)]
 source_faces=[];cursor=0
 for material in pmx.materials:
  source_faces.append([pmx.indices[i:i+3] for i in range(cursor,cursor+material['indexCount'],3)]);cursor+=material['indexCount']
 def signature(face):return tuple(sorted(tuple(round(value,5) for value in (*pmx.vertices[i]['position'],*pmx.vertices[i]['uv'])) for i in face))
 overlay={signature(face) for face in source_faces[1]};base={signature(face) for face in source_faces[0]}
 if not overlay<=base:raise ValueError('AL1 contains independent geometry and cannot be merged')
 faces=[]
 for mi,source_group in enumerate(source_faces):
  if mi==1:continue
  for a,b,c in source_group:
   # Native target reflects PMX z; reverse winding along with that reflection.
   material=(3 if signature([a,b,c]) in overlay else 0) if mi==0 else mi-1
   faces.append(dict(material=material,indices=[a,c,b]))
 mesh=dict(schema=1,coordinateSystem='weapon-local-Z-forward',positions=positions,normals=normals,uvs=uvs,faces=faces,materials=materials,vertexCount=len(pmx.vertices),triangleCount=len(faces))
 (output/'mesh.json').write_text(json.dumps(mesh,ensure_ascii=False,separators=(',',':'))+'\n')
 shutil.copyfile(source/'tex/刀.png',output/'textures/color.png')
 overlay_image=Image.open(source/'tex/刀AL.png').convert('RGBA');r,g,b,a=overlay_image.split()
 Image.merge('RGB',[ImageChops.multiply(channel,a) for channel in [r,g,b]]).save(output/'textures/emission.png')
 readme=source/'readme【一定要看】.txt';shutil.copyfile(readme,work/'原包使用说明.txt')
 files=[source/'武器.pmx',source/'tex/刀.png',source/'tex/刀AL.png',source/'sph/katana.bmp',readme]
 provenance=[dict(file=str(p.relative_to(source)),bytes=p.stat().st_size,sha256=hashlib.sha256(p.read_bytes()).hexdigest()) for p in files]
 manifest=dict(schema=1,id='raiden',label='雷电影佩刀',sourceName=pmx.name,mesh='mesh.json',sourceFiles=provenance,credits=dict(modelProvidedBy='miHoYo',modelAdaptedBy='观海（观海子）',instructions='Original readme retained in work/raiden-sword/原包使用说明.txt; local conversion only.'),stats=dict(sourceVertices=len(pmx.vertices),sourceTriangles=len(pmx.indices)//3,triangles=len(faces),mergedOverlayTriangles=len(source_faces[1]),textureSizes=[[2048,2048],[2048,2048]]),attachment=dict(localAxis='positive Z blade; rotate X=PI/2 when attached to d_wpnR',sourceGrip=[grip_x,0,grip_z],scale=scale,tip=20.03,tail=(grip_z-max(v['position'][2] for v in pmx.vertices))*scale),presentation=dict(originalColorTexture=True,originalUVs=True,mergedAL1='Alpha-premultiplied emission on the same 42 base faces; no coplanar overlay mesh.',sphereMap='MMD additive sphere pass is represented by restrained PBR reflection; not reused as a normal map.',combat='Display only; original W0_0 keeps native damage, reach and effect sockets.'))
 (output/'manifest.json').write_text(json.dumps(manifest,ensure_ascii=False,indent=2)+'\n');(work/'build-evidence.json').write_text(json.dumps(manifest,ensure_ascii=False,indent=2)+'\n')
 print(json.dumps(dict(vertices=mesh['vertexCount'],triangles=mesh['triangleCount'],sourceTriangles=len(pmx.indices)//3,mergedOverlay=42,grip=manifest['attachment']),ensure_ascii=False))
if __name__=='__main__':main()
