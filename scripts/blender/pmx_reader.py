"""Read the geometry/material/bone prefix of PMX 2.0/2.1 as inert data."""
import struct, pathlib, json, collections, math
class PMXReader:
 def __init__(self,path):
  self.path=pathlib.Path(path);self.data=self.path.read_bytes();self.offset=0
 def read(self,n):
  if n<0 or self.offset+n>len(self.data):raise ValueError(f'PMX truncated at {self.offset} + {n}')
  v=self.data[self.offset:self.offset+n];self.offset+=n;return v
 def unpack(self,fmt):return struct.unpack('<'+fmt,self.read(struct.calcsize('<'+fmt)))
 def one(self,fmt):return self.unpack(fmt)[0]
 def text(self):
  n=self.one('i');return self.read(n).decode(self.encoding,errors='strict')
 def index(self,kind):
  size=self.sizes[kind];return self.one({1:'B' if kind=='vertex' else 'b',2:'H' if kind=='vertex' else 'h',4:'I' if kind=='vertex' else 'i'}[size])
 def count(self):
  n=self.one('i');assert 0<=n<=10000000;return n
 def parse(self):
  assert self.read(4)==b'PMX ';self.version=self.one('f');n=self.one('B');config=self.read(n);assert n>=8
  self.encoding='utf-16-le' if config[0]==0 else 'utf-8';extra=config[1];self.sizes=dict(zip(['vertex','texture','material','bone','morph','rigid'],config[2:8]));assert all(x in(1,2,4)for x in self.sizes.values())
  self.name=self.text();self.name_en=self.text();self.comment=self.text();self.comment_en=self.text();self.vertices=[]
  for i in range(self.count()):
   p=self.unpack('3f');n=self.unpack('3f');uv=self.unpack('2f');self.read(extra*16);deform=self.one('B')
   if deform==0:j=[self.index('bone')];w=[1.]
   elif deform in(1,3):
    j=[self.index('bone'),self.index('bone')];a=self.one('f');w=[a,1-a]
    if deform==3:self.read(36)
   elif deform in(2,4):j=[self.index('bone')for _ in range(4)];w=list(self.unpack('4f'))
   else:raise ValueError(f'unsupported deform {deform}')
   edge=self.one('f');self.vertices.append(dict(position=p,normal=n,uv=uv,joints=j,weights=w,deform=deform,edge=edge))
  self.indices=[self.index('vertex')for _ in range(self.count())];assert len(self.indices)%3==0;assert all(i<len(self.vertices)for i in self.indices)
  self.textures=[self.text()for _ in range(self.count())];self.materials=[]
  for _ in range(self.count()):
   m=dict(name=self.text(),name_en=self.text(),diffuse=self.unpack('4f'),specular=self.unpack('3f'),shininess=self.one('f'),ambient=self.unpack('3f'),flags=self.one('B'),edgeColor=self.unpack('4f'),edgeSize=self.one('f'),texture=self.index('texture'),sphereTexture=self.index('texture'),sphereMode=self.one('B'));shared=self.one('B');m['toonShared']=shared;m['toonIndex']=self.one('B')if shared else self.index('texture');m['comment']=self.text();m['indexCount']=self.count();self.materials.append(m)
  assert sum(m['indexCount']for m in self.materials)==len(self.indices)
  self.bones=[]
  for i in range(self.count()):
   b=dict(index=i,name=self.text(),name_en=self.text(),position=self.unpack('3f'),parent=self.index('bone'),layer=self.one('i'),flags=self.one('H'));f=b['flags']
   if f&1:b['tailBone']=self.index('bone')
   else:b['tailOffset']=self.unpack('3f')
   if f&0x300:b['inheritBone']=self.index('bone');b['inheritWeight']=self.one('f')
   if f&0x400:b['fixedAxis']=self.unpack('3f')
   if f&0x800:b['localX']=self.unpack('3f');b['localZ']=self.unpack('3f')
   if f&0x2000:b['externalParent']=self.one('i')
   if f&0x20:
    b['ikTarget']=self.index('bone');b['ikIterations']=self.one('i');b['ikLimit']=self.one('f');b['ikLinks']=[]
    for _ in range(self.count()):
     link=dict(index=self.index('bone'),limited=self.one('B'))
     if link['limited']:link['min']=self.unpack('3f');link['max']=self.unpack('3f')
     b['ikLinks'].append(link)
   self.bones.append(b)
  return self
 def summary(self):
  used=collections.Counter()
  for v in self.vertices:
   for j,w in zip(v['joints'],v['weights']):
    if w>.001:used[j]+=1
  return dict(source=str(self.path),version=self.version,name=self.name,name_en=self.name_en,comment=self.comment,comment_en=self.comment_en,vertices=len(self.vertices),triangles=len(self.indices)//3,weights=dict(collections.Counter(v['deform']for v in self.vertices)),textures=self.textures,materials=self.materials,bones=[dict(b,weightedVertices=used[b['index']])for b in self.bones],bounds=[[min(v['position'][a]for v in self.vertices),max(v['position'][a]for v in self.vertices)]for a in range(3)],parsedOffset=self.offset,totalBytes=len(self.data))
if __name__=='__main__':
 import sys
 p=PMXReader(sys.argv[1]).parse();out=p.summary();print(json.dumps(out,ensure_ascii=False,indent=2))
