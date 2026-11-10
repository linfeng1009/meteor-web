#!/usr/bin/env python3
"""Read-only quantitative audit of original p0 SKC for HD comparison work."""
from pathlib import Path
from collections import defaultdict,Counter
import re,json,math
from PIL import Image
root=Path(__file__).resolve().parents[2]
src=root/'dist/assets/original/characters/p0/p0.skc'
s=src.read_text()
materials=[]
for block in re.findall(r'^\s*Material\s*\n([\s\S]*?)(?=^\s*Material\s*$|^\s*Vertices:)',s,re.M):
 materials.append({'texture':re.search(r'Texture\s+(\S+)',block)[1].lower(),'twoSided':bool(re.search(r'TwoSide\s+TRUE',block)),'alphaTest':bool(re.search(r'Option\s+ALPHA',block))})
vertices=[]
for line in re.findall(r'^\s*v\s+([^\r\n]+)',s,re.M):
 t=line.split();bi=t.index('Bones');uv=t.index('vt');n=int(t[bi+1]);w={int(t[bi+2+i*2]):float(t[bi+3+i*2]) for i in range(n)}
 vertices.append({'pos':tuple(map(float,t[:3])),'uv':tuple(map(float,t[uv+1:uv+3])),'weights':w})
faces=[]
for line in re.findall(r'^\s*f\s+([^\r\n]+)',s,re.M):
 t=list(map(int,line.split()));faces.append({'material':t[1],'indices':t[2:5]})
def edges(fs):
 c=Counter()
 for f in fs:
  a,b,c0=f['indices']
  for i,j in [(a,b),(b,c0),(c0,a)]:c[tuple(sorted([i,j]))]+=1
 return c
posgroups=defaultdict(list)
for i,v in enumerate(vertices):posgroups[v['pos']].append(i)
repeat=[g for g in posgroups.values() if len(g)>1]
weight_mismatch=[];uv_mismatch=[]
for g in repeat:
 if len({tuple(sorted(vertices[i]['weights'].items())) for i in g})>1:weight_mismatch.append(g)
 if len({vertices[i]['uv'] for i in g})>1:uv_mismatch.append(g)
ed=edges(faces)
# Exact position weld used solely for diagnosis, never mutate source or adopt as mesh algorithm.
key_to_id={p:i for i,p in enumerate(posgroups)}
vert_to_weld={i:key_to_id[v['pos']] for i,v in enumerate(vertices)}
wfaces=[dict(material=f['material'],indices=[vert_to_weld[i] for i in f['indices']]) for f in faces]
wed=edges(wfaces)
def components(fs):
 adj=defaultdict(set)
 for f in fs:
  for i in f['indices']:
   adj[i].update(f['indices'])
 groups=[];seen=set()
 for v in adj:
  if v in seen:continue
  stack=[v];seen.add(v);group=[]
  while stack:
   i=stack.pop();group.append(i)
   for j in adj[i]:
    if j not in seen:seen.add(j);stack.append(j)
  groups.append(group)
 return sorted([len(x) for x in groups],reverse=True)
def area(p,q,r):
 a=[q[i]-p[i] for i in range(3)];b=[r[i]-p[i] for i in range(3)];c=[a[1]*b[2]-a[2]*b[1],a[2]*b[0]-a[0]*b[2],a[0]*b[1]-a[1]*b[0]]
 return math.sqrt(sum(x*x for x in c))/2
for mi,m in enumerate(materials):
 fs=[f for f in faces if f['material']==mi];ids={i for f in fs for i in f['indices']}
 m['triangles']=len(fs);m['verticesUsed']=len(ids);m['boundaryEdges']=sum(n==1 for n in edges(fs).values());m['components']=components(fs)
 m['uvBounds']=[[min(vertices[i]['uv'][a] for i in ids),max(vertices[i]['uv'][a] for i in ids)] for a in range(2)]
 m['uvAreaSum']=sum(abs((vertices[b]['uv'][0]-vertices[a]['uv'][0])*(vertices[c]['uv'][1]-vertices[a]['uv'][1])-(vertices[b]['uv'][1]-vertices[a]['uv'][1])*(vertices[c]['uv'][0]-vertices[a]['uv'][0]))/2 for a,b,c in (f['indices'] for f in fs))
 m['surfaceArea']=sum(area(*(vertices[i]['pos'] for i in f['indices'])) for f in fs)
 m['degenerateTriangles']=sum(area(*(vertices[i]['pos'] for i in f['indices']))<1e-8 for f in fs)
textures=[]
for p in (src.parent/'textures').iterdir():
 im=Image.open(p);t={'file':p.name,'size':list(im.size),'mode':im.mode}
 if 'A' in im.getbands():
  hist=im.getchannel('A').histogram();t['alphaZero']=hist[0];t['alphaBelowNativeCutoff035']=sum(hist[:90]);t['alphaIntermediate']=sum(hist[1:255])
 textures.append(t)
report={'source':str(src.relative_to(root)),'vertices':len(vertices),'triangles':len(faces),'uniqueExactPositions':len(posgroups),'coincidentPositionGroups':len(repeat),'verticesInCoincidentGroups':sum(map(len,repeat)),'coincidentGroupsWithDifferentUV':len(uv_mismatch),'coincidentGroupsWithDifferentWeights':len(weight_mismatch),'coincidentWeightMismatchGroups':weight_mismatch,'originalIndexedBoundaryEdges':sum(n==1 for n in ed.values()),'exactPositionWeldBoundaryEdges':sum(n==1 for n in wed.values()),'exactPositionWeldNonmanifoldEdges':sum(n>2 for n in wed.values()),'originalConnectedComponents':components(faces),'exactPositionWeldComponents':components(wfaces),'influenceCounts':dict(Counter(len(v['weights']) for v in vertices)),'unnormalizedWeightVertices':sum(abs(sum(v['weights'].values())-1)>1e-4 for v in vertices),'boneIndexRange':[min(i for v in vertices for i in v['weights']),max(i for v in vertices for i in v['weights'])],'positionBounds':[[min(v['pos'][a] for v in vertices),max(v['pos'][a] for v in vertices)] for a in range(3)],'materials':materials,'textures':textures}
print(json.dumps(report,ensure_ascii=False,indent=2))
