"""Build the editable Qiyun battlefield and its batched browser geometry.

Run with Blender --background --python this_file.py. All authoring coordinates
below are game Y-up metres; conversion to Blender Z-up happens at the boundary.
No original level or game asset is modified.
"""
import bpy, bmesh, math, random, json, struct, array
from pathlib import Path
from mathutils import Vector

ROOT = Path(__file__).resolve().parents[2]
OUT = ROOT / 'dist/assets/enhanced/maps/qiyun'
WORK = ROOT / 'work/qiyun-courtyard'
OUT.mkdir(parents=True, exist_ok=True)
WORK.mkdir(parents=True, exist_ok=True)
random.seed(71024)
R = random.random
TAU = math.tau
bpy.ops.object.select_all(action='SELECT')
bpy.ops.object.delete(use_global=False)

def linear(v):
    return v / 12.92 if v <= .04045 else ((v + .055) / 1.055) ** 2.4

def rgb(h):
    return tuple(linear(((h >> s) & 255) / 255) for s in (16, 8, 0))

def blendpos(p):
    return (p[0], -p[2], p[1])

materials = {}
specs = {}
def material(name, color, roughness=.85, metalness=0, texture=False, special=None):
    m = bpy.data.materials.new(name)
    m.diffuse_color = (*rgb(color), 1)
    m.use_nodes = True
    n = m.node_tree.nodes
    bsdf = n.get('Principled BSDF')
    bsdf.inputs['Base Color'].default_value = (*rgb(color), 1)
    bsdf.inputs['Roughness'].default_value = roughness
    bsdf.inputs['Metallic'].default_value = metalness
    vc = n.new('ShaderNodeVertexColor')
    vc.layer_name = 'Tint'
    mul = n.new('ShaderNodeMixRGB'); mul.blend_type = 'MULTIPLY'; mul.inputs[0].default_value = 1
    mul.inputs[1].default_value = (*rgb(color), 1)
    m.node_tree.links.new(vc.outputs['Color'], mul.inputs[2])
    if texture:
        image = bpy.data.images.get('limestone.png') or bpy.data.images.load(str(OUT / 'limestone.png'))
        tex = n.new('ShaderNodeTexImage'); tex.image = image
        mult = n.new('ShaderNodeMixRGB'); mult.blend_type = 'MULTIPLY'; mult.inputs[0].default_value = 1
        m.node_tree.links.new(mul.outputs[0], mult.inputs[1]); m.node_tree.links.new(tex.outputs['Color'], mult.inputs[2])
        m.node_tree.links.new(mult.outputs[0], bsdf.inputs['Base Color'])
        bump = n.new('ShaderNodeBump'); bump.inputs['Strength'].default_value = .2; bump.inputs['Distance'].default_value = .09
        m.node_tree.links.new(tex.outputs['Color'], bump.inputs['Height']); m.node_tree.links.new(bump.outputs['Normal'], bsdf.inputs['Normal'])
    else:
        m.node_tree.links.new(mul.outputs[0], bsdf.inputs['Base Color'])
    if special == 'water':
        bsdf.inputs['Roughness'].default_value = .22
        bsdf.inputs['Metallic'].default_value = .2
    if special == 'lantern':
        bsdf.inputs['Emission Color'].default_value = (*rgb(0xffc57d), 1)
        bsdf.inputs['Emission Strength'].default_value = 1.1
    if special == 'distant':
        emission=n.new('ShaderNodeEmission'); emission.inputs['Strength'].default_value=.8
        m.node_tree.links.new(mul.outputs[0],emission.inputs['Color'])
        m.node_tree.links.new(emission.outputs[0],n.get('Material Output').inputs['Surface'])
    materials[name] = m
    specs[name] = dict(name=name, color=color, roughness=roughness, metalness=metalness,
                       texture='limestone.png' if texture else None, special=special)
    return name

stone = material('Carved limestone', 0xd1d0bb, .9, texture=True)
edge = material('Weathered cornices', 0x8a9d94, .93, texture=True)
rockmat = material('Stratified cliff', 0x718780, .98, texture=True)
earth = material('Moss and loam', 0x4c6347, 1, texture=True)
wood = material('Aged cedar', 0x554139, .94)
redwood = material('Oxide lacquer', 0x794c42, .82)
roofmat = material('Celadon roof', 0x345d60, .63)
roofline = material('Ceramic tile ribs', 0x5d9290, .63)
gold = material('Old bronze inlay', 0xa18a55, .58, .42)
leaves = material('Leaf canopy', 0xffffff, .94)
grassmat = material('Grass and ferns', 0xffffff, .98)
flower = material('Wild flowers', 0xffffff, .9)
water = material('Still jade water', 0x346d70, .22, .15, special='water')
falls = material('Waterfall veil', 0xb6dfdb, .35, special='waterfall')
lantern = material('Warm lantern paper', 0xf5c790, .8, special='lantern')
mountain = material('Distant mountain', 0x779c9d, 1, special='distant')

class Batch:
    def __init__(self, name, mat, collision=False, cast=True):
        self.name, self.mat, self.collision, self.cast = name, mat, collision, cast
        self.vertices, self.faces, self.colors = [], [], []
    def add(self, vertices, faces, tint=(1, 1, 1), gradient=0):
        start = len(self.vertices)
        low = min(v[1] for v in vertices); high = max(v[1] for v in vertices)
        self.vertices.extend(vertices)
        for v in vertices:
            shade = 1 - gradient + gradient * (v[1] - low) / max(.01, high - low)
            self.colors.append(tuple(max(0, min(1, c * shade)) for c in tint))
        self.faces.extend(tuple(start + i for i in f) for f in faces)

batches = {}
def batch(mat, section='near', collision=False, cast=True):
    key = (mat, section, collision)
    if key not in batches:
        batches[key] = Batch(f'{section} / {mat}', mat, collision, cast)
    return batches[key]

# Bevelled slab geometry is reused hundreds of times before material batching.
bm = bmesh.new(); bmesh.ops.create_cube(bm, size=1)
bmesh.ops.bevel(bm, geom=list(bm.edges), offset=.035, segments=1, affect='EDGES')
bm.verts.ensure_lookup_table(); bm.verts.index_update()
BOX_V = [tuple(v.co) for v in bm.verts]; BOX_F = [tuple(v.index for v in f.verts) for f in bm.faces]; bm.free()
bm = bmesh.new(); bmesh.ops.create_icosphere(bm, subdivisions=3, radius=1)
bm.verts.ensure_lookup_table(); bm.verts.index_update()
ROCK_V = [tuple(v.co) for v in bm.verts]; ROCK_F = [tuple(v.index for v in f.verts) for f in bm.faces]; bm.free()

def box(mat, p, size, angle=0, tint=(1,1,1), section='near', collision=False):
    c, s = math.cos(angle), math.sin(angle)
    verts = []
    for x, y, z in BOX_V:
        x, y, z = x * size[0], y * size[1], z * size[2]
        verts.append((p[0] + x*c + z*s, p[1]+y, p[2] - x*s + z*c))
    batch(mat, section, collision).add(verts, BOX_F, tint)

def cylinder(mat, p, radius, height, segments=24, top=None, section='near', collision=False, tint=(1,1,1)):
    top = radius if top is None else top
    vs = [(p[0]+math.sin(i*TAU/segments)*r, p[1]+y, p[2]+math.cos(i*TAU/segments)*r)
          for y, r in ((-height/2,radius),(height/2,top)) for i in range(segments)]
    fs = [(i,(i+1)%segments,(i+1)%segments+segments,i+segments) for i in range(segments)]
    fs += [tuple(range(segments-1,-1,-1)), tuple(range(segments,segments*2))]
    batch(mat, section, collision).add(vs, fs, tint)

def tube(mat, points, radii, sides=7, tint=(1,1,1), section='near'):
    vs = []
    for i,p in enumerate(points):
        axis = Vector(points[min(i+1,len(points)-1)]) - Vector(points[max(i-1,0)])
        axis.normalize(); a = axis.cross(Vector((0,0,1)))
        if a.length < .01: a = axis.cross(Vector((1,0,0)))
        a.normalize(); b = a.cross(axis).normalized()
        for j in range(sides):
            v = Vector(p)+(a*math.sin(j*TAU/sides)+b*math.cos(j*TAU/sides))*radii[i]
            vs.append(tuple(v))
    fs = [(i*sides+j,i*sides+(j+1)%sides,(i+1)*sides+(j+1)%sides,(i+1)*sides+j)
          for i in range(len(points)-1) for j in range(sides)]
    batch(mat, section).add(vs,fs,tint, .18)

def rock(p, size, section='near', mat=rockmat, tint=None):
    phase=R()*20
    vertices=[]
    for x,y,z in ROCK_V:
        noise = 1+.1*math.sin(x*7+phase)*math.sin(y*5-phase)+.06*math.cos(z*9+phase)
        # Horizontal shelves give the cliff a geological silhouette.
        y = round(y*6)/6*.55 + y*.45
        vertices.append((p[0]+x*size[0]*noise, p[1]+y*size[1]*noise, p[2]+z*size[2]*noise))
    tint = tint or (1-R()*.18,1-R()*.12,1-R()*.14)
    batch(mat, section, cast=section=='near').add(vertices,ROCK_F,tint,.25)

def ring(mat, radius, y, thickness=.035, x=0,z=0, start=0,end=TAU):
    count=max(5,int((end-start)*radius*5))
    pts=[(x+math.sin(start+(end-start)*i/count)*radius,y,z+math.cos(start+(end-start)*i/count)*radius) for i in range(count+1)]
    tube(mat,pts,[thickness]*len(pts),5)

# The fight surface is deliberately continuous, with a separate low-poly floor.
cylinder(edge,(0,-.06,0),18.3,1.5,96)
cylinder(stone,(0,.6,0),17.9,.24,96)
cylinder(stone,(0,.54,0),18,.45,64,section='collision',collision=True)
for row in range(-10,11):
    for col in range(-10,11):
        x=col*1.57 + (row%2)*.78; z=row*1.57
        if math.hypot(x,z)>16.8: continue
        shade=.83+R()*.17
        box(stone,(x,.742+R()*.008,z),(1.53,.075,1.53),tint=(shade,shade,shade*.98))
for r,y in ((17.1,.77),(17.48,.77),(6.15,.802),(5.95,.802),(4.3,.802)):
    ring(gold,r,y,.018 if r<10 else .028)
for i in range(12):
    a=i*TAU/12
    tube(gold,[(math.sin(a)*4.3,.804,math.cos(a)*4.3),(math.sin(a+.10)*5.15,.804,math.cos(a+.10)*5.15),(math.sin(a)*5.9,.804,math.cos(a)*5.9)], [.023]*3,4)
    box(gold,(math.sin(a)*6.6,.8,math.cos(a)*6.6),(.16,.014,.5),angle=a)
cylinder(gold,(0,.802,0),.23,.015,12)

# Apron terraces and the north approach to the ceremonial gate.
box(edge,(0,.1,-20),(10,.65,11))
box(stone,(0,.45,-20),(9.7,.18,10.8))
box(stone,(0,.1,-20),(10,.88,11),section='collision',collision=True)
for i in range(4):
    y=.45+i*.18; z=-24-i*.6
    box(stone,(0,y,z),(8,.2,.65))
    box(stone,(0,y-.02,z),(8,.24,.65),section='collision',collision=True)
box(stone,(0,.93,-27.25),(7,.3,3.8))
box(stone,(0,.91,-27.25),(7,.34,3.8),section='collision',collision=True)
for i in range(4):
    z=-26.6-i*.45; y=1.18+i*.2
    box(stone,(0,y,z),(7,.23,.52))
    box(stone,(0,y-.015,z),(7,.26,.52),section='collision',collision=True)
for i in range(64):
    a=i*TAU/64
    # Deliberate openings line up with solid approaches, rather than leaving
    # body-width cracks between the decorative balustrade panels.
    if abs(a-math.pi)<.29 or 1.90<a<2.17: continue
    x,z=math.sin(a)*17.65,math.cos(a)*17.65
    box(edge,(x,1.28,z),(1.8,1.05,.4),angle=a)
    box(stone,(x,1.85,z),(1.84,.16,.58),angle=a)
    box(edge,(x,1.28,z),(1.84,1.05,.48),angle=a,section='collision',collision=True)
    if i%4==0:
        cylinder(stone,(x,1.47,z),.3,1.45,8)
        cylinder(gold,(x,2.24,z),.2,.11,8)

# Grass-covered limestone outcrops, a pool and layered cliffs around the arena.
for i in range(42):
    a=i*TAU/42; rr=23+R()*3
    rock((math.sin(a)*rr,-2.2-R()*2,math.cos(a)*rr),(5+R()*3,3+R()*3,5+R()*2))
    if i%2==0:
        rock((math.sin(a)*rr,-.4,math.cos(a)*rr),(4,1.1,4),mat=earth)
for i in range(22):
    a=3.7 + i*.092; rr=39+R()*5
    rock((math.sin(a)*rr,4+R()*9,math.cos(a)*rr),(5+R()*5,11+R()*9,5+R()*4))
    rock((math.sin(a)*rr,11+R()*8,math.cos(a)*rr),(5+R()*3,1.8+R()*2,5),mat=earth)
for i in range(14):
    x=20+R()*11; z=-27+R()*49
    rock((x,-2,z),(4+R()*3,2.5+R()*3,4+R()*3))
cylinder(water,(-21,-.4,-3),9,.03,72,section='water')
for x,z in ((-27,-13),(-28,-8),(-26,-3),(-25,4)):
    rock((x,-.9,z),(4,2.3,3))
# Vertical ribbons are animated independently from the rigid environment.
for x,z,h,width in ((-27,-19,12,2.1),(-24.4,-18.3,8,1.3),(-30,-20,15,.8)):
    verts=[(x-width/2,-.35,z),(x+width/2,-.35,z),(x+width*.32,h,z-.8),(x-width*.32,h,z-.8)]
    batch(falls,'waterfall',cast=False).add(verts,[(0,1,2,3)])
    rock((x-2,h*.55,z-2),(3,h*.7,4))

def roof(x,y,z,w,d):
    nx,nz=32,16
    def point(i,j):
        xx=(i/nx*2-1)*w; zz=(j/nz*2-1)*d
        t=abs(zz)/d
        yy=y+2.1*(1-t)**1.4 + .58*t**7 + .6*(abs(xx)/w)**9
        return (x+xx,yy,z+zz)
    vs=[point(i,j) for i in range(nx+1) for j in range(nz+1)]
    fs=[(i*(nz+1)+j,i*(nz+1)+j+1,(i+1)*(nz+1)+j+1,(i+1)*(nz+1)+j) for i in range(nx) for j in range(nz)]
    batch(roofmat).add(vs,fs)
    batch(roofmat,'collision',True).add(vs,fs)
    for i in range(0,nx+1):
        pts=[point(i,j) for j in range(nz+1)]
        tube(roofline,pts,[.045]*len(pts),5)
    for j in (0,nz):
        pts=[point(i,j) for i in range(nx+1)]
        tube(gold,pts,[.07]*len(pts),6)
    tube(gold,[(x-w,y+2.25,z),(x,y+2.18,z),(x+w,y+2.25,z)],[.13,.1,.13],8)
    for side in (-1,1):
        tube(gold,[(x+side*w,y+2.25,z),(x+side*(w+.5),y+2.5,z),(x+side*(w+.8),y+3.05,z)], [.15,.10,.02],7)

# North gate, its masonry, carved capitals and brackets. The opening is walkable.
for x in (-5.5,5.5):
    for y,w,d in ((1.2,2.1,2.1),(1.5,1.8,1.8),(1.75,1.35,1.35),(8.4,1.8,1.8),(8.68,2.1,2.1)):
        box(stone,(x,y,-21.3),(w,.28,d))
    box(stone,(x,4.95,-21.3),(1.2,6.3,1.2))
    box(stone,(x,4.5,-21.3),(1.2,7,1.2),section='collision',collision=True)
    for z in (-21.93,-20.67):
        box(gold,(x,4.7,z),(.12,4.7,.035))
        for y in (2.7,6.7):
            box(gold,(x,y,z),(.48,.48,.04),angle=.78)
    for z in (-22,-20.6):
        box(redwood,(x,7.6,z),(2.8,.35,.4))
box(redwood,(0,8.1,-21.3),(13.3,.9,1.1))
box(gold,(0,7.7,-20.73),(10.7,.08,.06))
box(wood,(0,8.05,-20.68),(3.6,.93,.12))
# A relief roundel and repeated ornamental lattice replace illegible text.
ring(gold,.28,8.06,.035,x=0,z=-20.59)
for x in (-3.9,-2.8,2.8,3.9):
    box(gold,(x,8.05,-20.69),(.38,.38,.05),angle=.78)
roof(0,9,-21.3,8.8,3.3)
for side in (-1,1):
    for i in range(5):
        x=side*(7.5+i*1.7)
        if side==1 and i>2: continue
        box(edge,(x,2.0,-21.6),(1.65,2.6,.85))
        box(stone,(x,3.4,-21.6),(1.78,.2,1))
        box(edge,(x,1.8,-21.6),(1.65,2.8,.85),section='collision',collision=True)
# A distant shrine visible through the gate, with an enclosed back.
box(stone,(0,1.45,-31),(10,1.1,6))
box(stone,(0,1.45,-31),(10,1.1,6),section='collision',collision=True)
box(redwood,(0,4.2,-32),(7.5,4.5,1))
box(redwood,(0,4.2,-31),(7.5,4.5,1),section='collision',collision=True)
roof(0,6.1,-31.8,5.7,3.5)
for x in (-3.2,3.2):
    cylinder(redwood,(x,3.6,-29.4),.24,4.2,10)

# An open-sided pavilion on the east bank.
box(edge,(22,1.0,-8),(7,1,7))
box(stone,(22,1.6,-8),(7.6,.2,7.6))
box(stone,(22,1.05,-8),(7.6,1.3,7.6),section='collision',collision=True)
for i in range(6):
    x=16+i*.48; y=.72+i*.17
    box(stone,(x,y,-8),(.55,.2,3.6))
    box(stone,(x,y-.01,-8),(.55,.22,3.6),section='collision',collision=True)
for x in (19.3,24.7):
    for z in (-10.7,-5.3):
        cylinder(stone,(x,1.85,z),.48,.4,8)
        cylinder(redwood,(x,4.05,z),.2,4.2,10)
        cylinder(redwood,(x,4.05,z),.23,4.2,8,section='collision',collision=True)
        cylinder(gold,(x,5.9,z),.25,.15,10)
roof(22,6,-8,4.7,4.0)

def lamp(x,z,y=.8):
    cylinder(stone,(x,y+.2,z),.65,.4,8)
    cylinder(edge,(x,y+1.0,z),.24,1.3,8)
    box(stone,(x,y+1.65,z),(1.1,.22,1.1))
    box(lantern,(x,y+2.05,z),(.7,.65,.7))
    for a in range(4):
        aa=a*TAU/4+math.pi/4
        box(wood,(x+math.sin(aa)*.48,y+2.05,z+math.cos(aa)*.48),(.09,.82,.09))
    cylinder(roofmat,(x,y+2.5,z),.86,.35,4,top=.35)
    cylinder(gold,(x,y+2.78,z),.09,.3,8)
for x,z in ((-11,-13),(11,-13),(-14,11),(14,11),(-4.2,-26),(4.2,-26)):
    lamp(x,z)
    cylinder(edge,(x,1.55,z),.5,1.7,8,section='collision',collision=True)

# Geometry leaves, not solid low-poly blobs. Each canopy is a branched cluster
# of bent, five-point leaves with shaded roots and different sunlit tips.
def leaf(center,size,angle,tint,mat=leaves):
    c,s=math.cos(angle),math.sin(angle)
    shape=[(0,0),(-.45,.18),(-.20,.38),(-.55,.62),(-.17,.55),(0,1),(.17,.55),(.55,.62),(.20,.38),(.45,.18)]
    verts=[center]
    for xx,zz in shape:
        xx,zz=xx*size,(zz-.35)*size
        verts.append((center[0]+xx*c+zz*s,center[1]+abs(xx)*.22+zz*.16,center[2]-xx*s+zz*c))
    fs=[(0,i+1,(i+1)%len(shape)+1) for i in range(len(shape))]
    batch(mat,cast=mat==leaves).add(verts,fs,tint,.3)

def tree(x,z,height,spread,autumn=False):
    lean=R()*1.5-.75
    trunk=[(x,.0,z),(x+.25,height*.28,z+.15),(x+lean,height*.52,z-.5),(x+lean*1.8,height*.78,z-.6)]
    tube(wood,trunk,[height*.095,height*.063,height*.04,.11],10)
    for i in range(7):
        a=i*TAU/7+R()*.3
        tube(wood,[(x+math.sin(a)*2.5,.1,z+math.cos(a)*2.5),(x+math.sin(a),.4,z+math.cos(a)),(x,height*.18,z)], [.06,.19,height*.07],6)
    for b in range(11):
        a=b*2.4+R()*.7; reach=spread*(.55+R()*.42); yy=height*(.67+R()*.28)
        end=(x+math.sin(a)*reach,yy,z+math.cos(a)*reach)
        tube(wood,[(x+lean,height*.48,z-.2),(x+math.sin(a)*reach*.5,yy-.7,z+math.cos(a)*reach*.5),end],[.2,.13,.035],7)
        for k in range(230):
            az=R()*TAU; rr=math.sqrt(R())*spread*.38
            px=end[0]+math.sin(az)*rr; pz=end[2]+math.cos(az)*rr
            py=yy+math.cos(rr/(spread*.4)*1.3)*1.0+(R()-.35)*spread*.5
            if autumn:
                tint=rgb(random.choice([0xb87046,0xcf8150,0xdca35f,0x9b5e3d,0xe1b66b,0x92734a]))
            else:
                tint=rgb(random.choice([0x5c794c,0x7d9959,0x96ac6b,0x45694e,0xabc380,0x6b8c53]))
            leaf((px,py,pz),.25+R()*.31,R()*TAU,tint)

tree(-19,-7,11,5.8,True)
tree(18,12,9.5,4.7)
tree(-23,16,10,4.5)
tree(29,-19,13,5.3)
tree(-12,-30,12,4.4)

def fern(x,y,z,size):
    for b in range(7):
        a=b*TAU/7+R()*.2
        pts=[(x,y,z),(x+math.sin(a)*size*.5,y+size*.5,z+math.cos(a)*size*.5),(x+math.sin(a)*size,y+size*.25,z+math.cos(a)*size)]
        tube(grassmat,pts,[.022,.013,.002],3,tint=rgb(0x7a9a52))
        for k in range(1,6):
            t=k/6; px=x+math.sin(a)*size*t; pz=z+math.cos(a)*size*t; py=y+math.sin(t*math.pi)*size*.5
            for side in (-1,1):
                leaf((px+math.cos(a)*side*size*.13,py,pz-math.sin(a)*side*size*.13),size*.33*(1-t*.6),a+side*1.2,rgb(0x668e4e),grassmat)

for i in range(820):
    a=R()*TAU; radius=17.6+R()*6
    x,z=math.sin(a)*radius,math.cos(a)*radius
    if z < -17 and abs(x)<6: continue
    y=.0 if radius>18.5 else .77
    tint=rgb(random.choice([0x708553,0x94a664,0x5c764e,0xa6ad78]))
    for b in range(4):
        aa=R()*TAU; h=.2+R()*.6
        vs=[(x-.05,y,z),(x+.05,y,z),(x+math.sin(aa)*.22,y+h,z+math.cos(aa)*.22)]
        batch(grassmat,cast=False).add(vs,[(0,1,2)],tint,.45)
    if i%19==0: fern(x,y,z,.65+R()*.4)
    if i%8==0:
        for f in range(3):
            xx=x+R()*.5; zz=z+R()*.5; yy=y+.3+R()*.3
            tube(grassmat,[(xx,y,zz),(xx,yy,zz)],[.012,.009],3,tint=rgb(0x66814c))
            for j in range(5):
                aa=j*TAU/5
                leaf((xx+math.sin(aa)*.08,yy,zz+math.cos(aa)*.08),.16,aa,rgb(0xded4b2 if i%3 else 0xb1a4c4),flower)
# Ivy on wall faces and stone seams.
for i in range(44):
    a=R()*TAU; x=math.sin(a)*17.72; z=math.cos(a)*17.72
    for k in range(6):
        leaf((x+math.sin(k)*.19,1.65-k*.22,z+math.cos(k)*.16),.24,R()*TAU,rgb(0x5d7955),grassmat)

# Continuous ridgelines form a mountain range; all layers have real depth and
# broad slopes rather than giant isolated faceted rocks in the skyline.
for layer in range(3):
    angular,radial=192,9
    vs=[]; fs=[]
    for j in range(radial+1):
        t=j/radial
        for i in range(angular+1):
            a=i*TAU/angular
            rr=75+layer*72+t*85+math.sin(a*5+layer)*5
            ridge=max(0,math.sin(t*math.pi))**1.35
            peaks=45+math.sin(a*3+layer*1.7)*12+math.sin(a*7-layer)*9+math.sin(a*13+layer)*3
            h=-20+ridge*peaks+math.sin(a*17+t*5)*ridge*1.8
            vs.append((math.sin(a)*rr,h,math.cos(a)*rr))
    for j in range(radial):
        for i in range(angular):
            a=j*(angular+1)+i; b=a+angular+1
            fs.append((a,b,b+1,a+1))
    batch(mountain,'vista',cast=False).add(vs,fs,(.86+layer*.03,.92+layer*.02,.94+layer*.02),.13)

objects=[]
for b in batches.values():
    if not b.faces: continue
    mesh=bpy.data.meshes.new(b.name)
    mesh.from_pydata([blendpos(p) for p in b.vertices],[],b.faces); mesh.update()
    obj=bpy.data.objects.new(b.name,mesh); bpy.context.collection.objects.link(obj); obj.data.materials.append(materials[b.mat])
    obj['collision']=b.collision; obj['castShadow']=b.cast
    obj['special']=specs[b.mat]['special'] or ''
    colors=mesh.color_attributes.new(name='Tint',type='FLOAT_COLOR',domain='POINT')
    for i,c in enumerate(b.colors): colors.data[i].color=(*c,1)
    uv=mesh.uv_layers.new(name='UVMap')
    for poly in mesh.polygons:
        poly.use_smooth = b.mat in (wood, leaves, grassmat, flower)
        norm=poly.normal
        for li in poly.loop_indices:
            p=b.vertices[mesh.loops[li].vertex_index]
            if b.mat==falls:
                coords=(p[0]*.45,p[1]*.13)
            elif abs(norm.z)>.6: coords=(p[0]/3,p[2]/3)
            elif abs(norm.x)>.6: coords=(p[2]/3,p[1]/3)
            else: coords=(p[0]/3,p[1]/3)
            uv.data[li].uv=coords
    if b.collision:
        obj.hide_render=True; obj.display_type='WIRE'
    objects.append(obj)

# Native browser format: material-batched meshes, little-endian typed arrays.
# Exporting polygon corners preserves bevel normals, UV seams and vertex tint.
blob=bytearray(); records=[]
def put(values,code):
    while len(blob)%4: blob.append(0)
    offset=len(blob); a=array.array(code,values); blob.extend(a.tobytes())
    return dict(offset=offset,count=len(values))

for obj in objects:
    mesh=obj.data; mesh.calc_loop_triangles()
    positions=[]; normals=[]; uvs=[]; colors=[]; indices=[]; unique={}
    for tri in mesh.loop_triangles:
        for li in tri.loops:
            loop=mesh.loops[li]; vertex=mesh.vertices[loop.vertex_index]; p=vertex.co
            poly=mesh.polygons[tri.polygon_index]; norm=vertex.normal if poly.use_smooth else poly.normal
            uv=mesh.uv_layers.active.data[li].uv; color=mesh.color_attributes['Tint'].data[loop.vertex_index].color
            key=(loop.vertex_index,*(round(v,5) for v in norm),round(uv[0],5),round(uv[1],5))
            if key not in unique:
                unique[key]=len(positions)//3
                positions.extend((p.x,p.z,-p.y)); normals.extend((norm.x,norm.z,-norm.y)); uvs.extend(uv)
                colors.extend(round(max(0,min(1,c))*255) for c in color[:3])
                colors.append(255)
            indices.append(unique[key])
    records.append(dict(name=obj.name,material=obj.data.materials[0].name,collision=bool(obj['collision']),castShadow=bool(obj['castShadow']),
                        positions=put(positions,'f'),normals=put(normals,'f'),uvs=put(uvs,'f'),colors=put(colors,'B'),indices=put(indices,'I')))
(OUT/'geometry.bin').write_bytes(blob)
meta=dict(format='qiyun-battlefield-v1',id='qiyun',name='栖云古庭',units='metres-y-up',seed=71024,geometry='geometry.bin',
          materials=list(specs.values()),meshes=records,bounds=[[-27,-6,-35],[27,17,26]],
          spawns=[[0,.8,9],[-6,.8,-2],[6,.8,-4],[0,.8,-8],[9,.8,5],[-9,.8,4]],
          stats=dict(bytes=len(blob),triangles=sum(o.data.loop_triangles.__len__() for o in objects),drawBatches=sum(not o['collision'] for o in objects)))
(OUT/'manifest.json').write_text(json.dumps(meta,ensure_ascii=False,separators=(',',':')))

# A packaged, editable .blend shares the exact same geometry as the browser.
world=bpy.context.scene.world or bpy.data.worlds.new('Mountain air'); bpy.context.scene.world=world; world.use_nodes=True
world.node_tree.nodes['Background'].inputs[0].default_value=(.36,.49,.52,1)
world.node_tree.nodes['Background'].inputs[1].default_value=.65
def light(name,kind,p,energy,color):
    data=bpy.data.lights.new(name,kind); data.energy=energy; data.color=rgb(color)
    obj=bpy.data.objects.new(name,data); bpy.context.collection.objects.link(obj); obj.location=blendpos(p); return obj
sun=light('Afternoon sun','SUN',(-35,60,25),3.0,0xffe5b7)
sun.rotation_euler=(Vector(blendpos((0,0,0)))-sun.location).to_track_quat('-Z','Y').to_euler(); sun.data.angle=.10
fill=light('Sky fill','AREA',(0,25,-3),1800,0xcbe9eb); fill.data.shape='DISK'; fill.data.size=45
fill.rotation_euler=(Vector((0,0,0))-fill.location).to_track_quat('-Z','Y').to_euler()
camera_data=bpy.data.cameras.new('Battlefield overview'); camera=bpy.data.objects.new('Battlefield overview',camera_data); bpy.context.collection.objects.link(camera)
camera.location=blendpos((34,27,42)); target=Vector(blendpos((0,2,-7)))
camera.rotation_euler=(target-camera.location).to_track_quat('-Z','Y').to_euler(); camera.data.lens=40; camera.data.clip_end=1500
scene=bpy.context.scene; scene.camera=camera; scene.render.engine='CYCLES'; scene.cycles.samples=24
scene.render.resolution_x=1400; scene.render.resolution_y=900; scene.render.resolution_percentage=100
scene.view_settings.view_transform='AgX'
for image in bpy.data.images:
    if image.source=='FILE': image.pack()
bpy.ops.wm.save_as_mainfile(filepath=str(WORK/'栖云古庭.blend'))
# A portable interchange copy, in addition to the tightly batched runtime export.
bpy.ops.object.select_all(action='DESELECT')
for obj in objects:
    if not obj['collision']: obj.select_set(True)
bpy.ops.export_scene.gltf(filepath=str(WORK/'栖云古庭.glb'),use_selection=True,export_format='GLB',export_yup=True,export_extras=True)
print('QIYUN_EXPORT',json.dumps(meta['stats']))
