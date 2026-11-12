"""Reproducible, local Blender p0 enhancement. Run with Blender --background.

Authored game SKC/BNC/AMB files are read only. The export stays in native Z-up
coordinates and retains the original 30 bone indices and six attachment dummies.
This is a first-pass enhancement, not an independently sculpted AAA character.
"""
import bpy, bmesh, os, re, json, math, struct, hashlib, argparse, sys
import numpy as np
from mathutils import Vector, Matrix, Quaternion
from mathutils.kdtree import KDTree

ROOT=os.path.abspath(os.path.join(os.path.dirname(__file__),'../..'))
SRC=os.path.join(ROOT,'dist/assets/original/characters/p0')
OUT=os.path.join(ROOT,'work/character-hd/retired-assets')
WORK=os.path.join(ROOT,'work/character-hd')
for p in [OUT,WORK,os.path.join(OUT,'textures')]:os.makedirs(p,exist_ok=True)
args=argparse.ArgumentParser();args.add_argument('--skip-render',action='store_true');options=args.parse_args(sys.argv[sys.argv.index('--')+1:] if '--' in sys.argv else [])
bpy.ops.object.select_all(action='SELECT');bpy.ops.object.delete(use_global=False)

def read_skin():
    text=open(os.path.join(SRC,'p0.skc')).read();p=[];uv=[];ws=[];f=[];mi=[]
    for line in text.splitlines():
        t=line.split()
        if t and t[0]=='v':
            p.append(tuple(map(float,t[1:4])));u=t.index('vt');uv.append(tuple(map(float,t[u+1:u+3])));b=t.index('Bones');n=int(t[b+1]);ws.append([(int(t[b+2+2*i]),float(t[b+3+2*i]))for i in range(n)])
        elif t and t[0]=='f':f.append(tuple(map(int,t[3:6])));mi.append(int(t[2]))
    return p,uv,ws,f,mi
P,UV,W,F,MI=read_skin();K=KDTree(len(P))
for i,p in enumerate(P):K.insert(p,i)
K.balance()
bone_text=open(os.path.join(SRC,'p0.bnc')).read();entries=[]
for m in re.finditer(r'\b(bone|Dummey)\s+(\S+)\s*\{([^}]+)\}',bone_text):
    def get(k):return re.search(k+r'\s+([^\r\n]+)',m[3])[1].strip()
    entries.append(dict(kind='bone' if m[1]=='bone' else 'dummy',name=m[2],parent=get('parent'),position=list(map(float,get('pivot').split())),quaternion=list(map(float,get('quaternion').split()))))
B=[e for e in entries if e['kind']=='bone'];D=[e for e in entries if e['kind']=='dummy'];BY={e['name']:e for e in entries}
def resolve(n):
    if n in BY:return n
    if re.fullmatch(r'b\d+',n):return B[int(n[1:])]['name']
    if re.fullmatch(r'd\d+',n):return D[int(n[1:])]['name']
    return None
def native_world(local=None):
    local=local or {};result={}
    def calc(name):
        if name in result:return result[name]
        e=BY[name];a=local.get(name,e);pos=a['position'];q=Quaternion(a['quaternion']);q.normalize();m=Matrix.Translation(Vector(pos))@q.to_matrix().to_4x4();parent=resolve(a['parent'])
        result[name]=(calc(parent)@m) if parent else m
        return result[name]
    for e in entries:calc(e['name'])
    return result
REST=native_world();C=Matrix.Rotation(-math.pi/2,4,'Z')
def qnative(wxyz):q=Quaternion(wxyz);q.normalize();return q
def animation_frame(path,frame):
    data=open(path,'rb').read();nb,nd,nf,fps=struct.unpack_from('<iiii',data,5);stride=20+nb*16+nd*33;o=21+frame*stride
    root=struct.unpack_from('<fff',data,o+8);local={e['name']:dict(e)for e in entries}
    local[B[0]['name']]['position']=[0,0,root[2]]
    for i,e in enumerate(B):local[e['name']]['quaternion']=struct.unpack_from('<ffff',data,o+20+i*16)
    start=o+20+nb*16
    for i,e in enumerate(D):
        d=start+i*33;local[e['name']]['parent']=data[d:d+5].decode().rstrip('\0');local[e['name']]['position']=struct.unpack_from('<fff',data,d+5);local[e['name']]['quaternion']=struct.unpack_from('<ffff',data,d+17)
        if e['name']=='d_base':local[e['name']]['position']=e['position']
    return native_world(local)

def write_image(name,array,color_space='sRGB'):
    h,w=array.shape[:2];image=bpy.data.images.new(name,width=w,height=h,alpha=True,float_buffer=False);image.colorspace_settings.name=color_space
    if array.shape[2]==3:array=np.concatenate([array,np.ones((h,w,1),dtype=np.float32)],axis=2)
    image.pixels.foreach_set(np.clip(array,0,1).astype(np.float32).reshape(-1));image.filepath_raw=os.path.join(OUT,'textures',name+'.png');image.file_format='PNG';image.save();return image
def textures():
    src=bpy.data.images.load(os.path.join(SRC,'textures/nm001b01.png'),check_existing=True);src.scale(2048,2048);a=np.array(src.pixels[:],dtype=np.float32).reshape(2048,2048,4)
    y,x=np.indices((2048,2048));u=x/2048;v=y/2048
    # Small physical weave; existing painted lighting remains in the base color.
    weave=(np.sin(x*math.pi)*.0+np.cos(x*math.pi/2)*np.cos(y*math.pi/2))
    broad=.5+.5*np.sin(x*.022+y*.013)
    cloth=(a[:,:,1]>a[:,:,0]*1.12)&(a[:,:,1]>a[:,:,2]*1.05)&(a[:,:,0]<.35)
    skin=(a[:,:,0]>a[:,:,1]*1.2)&(a[:,:,1]>a[:,:,2]*1.03)&(v>.46)
    grain=np.random.default_rng(7349).normal(0,1,(2048,2048))
    color=a.copy();color[:,:,:3]*=1+(weave*.013+grain*.004)[:,:,None]*cloth[:,:,None]
    # Keep transparency hard-edged, matching the original card cutouts.
    color[:,:,3]=(a[:,:,3]>.5).astype(np.float32)
    body=write_image('body-color',color)
    rough=np.where(cloth,.82+weave*.035,np.where(skin,.67,.60))+grain*.012
    roughness=write_image('body-roughness',np.repeat(rough[:,:,None],3,axis=2),'Non-Color')
    height=(weave*.0012+grain*.0002)*cloth
    gy,gx=np.gradient(height);normal=np.stack([-gx*18,-gy*18,np.ones_like(gx)],axis=2);normal/=np.linalg.norm(normal,axis=2)[:,:,None];normal=normal*.5+.5
    normal=write_image('body-normal',normal,'Non-Color')
    facepath=os.path.join(OUT,'face-hd-v1.png')
    face=bpy.data.images.load(facepath if os.path.exists(facepath) else os.path.join(SRC,'textures/nm001f01.jpg'),check_existing=True)
    if face.size[0]>1024:face.scale(1024,1024)
    face.filepath_raw=os.path.join(OUT,'textures/face-color.png');face.file_format='PNG';face.save()
    return body,roughness,normal,face
BODY,ROUGH,NORMAL,FACE=textures()

MATERIAL_SPECS=[]
def material(name,color=None,texture=None,roughness=.75,metalness=0,alpha=False,twoSide=False,detail=False):
    m=bpy.data.materials.new(name);m.use_nodes=True;nodes=m.node_tree.nodes;p=nodes.get('Principled BSDF');p.inputs['Roughness'].default_value=roughness;p.inputs['Metallic'].default_value=metalness
    if color:p.inputs['Base Color'].default_value=(*color,1)
    if texture:
        t=nodes.new('ShaderNodeTexImage');t.image=texture;t.extension='EXTEND';m.node_tree.links.new(t.outputs['Color'],p.inputs['Base Color'])
        if alpha:m.node_tree.links.new(t.outputs['Alpha'],p.inputs['Alpha']);m.surface_render_method='DITHERED'
    if detail:
        n=nodes.new('ShaderNodeTexImage');n.image=NORMAL;n.extension='EXTEND';n.image.colorspace_settings.name='Non-Color';b=nodes.new('ShaderNodeNormalMap');b.inputs['Strength'].default_value=.35;m.node_tree.links.new(n.outputs['Color'],b.inputs['Color']);m.node_tree.links.new(b.outputs['Normal'],p.inputs['Normal'])
        r=nodes.new('ShaderNodeTexImage');r.image=ROUGH;r.extension='EXTEND';r.image.colorspace_settings.name='Non-Color';m.node_tree.links.new(r.outputs['Color'],p.inputs['Roughness'])
    spec=dict(name=name,texture=('textures/'+texture.name.replace('.png','')+'.png') if texture else None,twoSide=twoSide,alpha=alpha,opacity=1,roughness=roughness,metalness=metalness)
    if texture==FACE:spec['texture']='textures/face-color.png'
    if texture==BODY:spec['texture']='textures/body-color.png'
    if color:spec['color']='#'+''.join(f'{round(c*255):02x}' for c in color)
    if detail:spec.update(normal='textures/body-normal.png',roughnessMap='textures/body-roughness.png',normalScale=.35)
    MATERIAL_SPECS.append(spec);return m
MATS=[material('Jade cloth and skin',texture=BODY,alpha=True,detail=True),material('Sleeve brocade',texture=BODY,alpha=True,detail=True),material('AI assisted face',texture=FACE,roughness=.7),material('Original hair cards',texture=FACE,roughness=.72,twoSide=True),material('Robe panels',texture=BODY,alpha=True,twoSide=True,detail=True),material('Antique gold piping',color=(.48,.30,.095),roughness=.45,metalness=.65),material('Dark leather',color=(.035,.028,.021),roughness=.78),material('Carved jade hair',color=(.012,.14,.115),roughness=.64),material('Hair highlights',color=(.018,.20,.158),roughness=.68),material('Stitch thread',color=(.27,.23,.14),roughness=.92)]

def weights(ob,values=None,fixed=None):
    for b in B:ob.vertex_groups.new(name=b['name'])
    for v in ob.data.vertices:
        ws=values[v.index] if values is not None else ([(fixed,1)] if fixed is not None else W[K.find(v.co)[1]])
        total=sum(w for b,w in ws)or 1
        for b,w in ws:ob.vertex_groups[b].add([v.index],w/total,'REPLACE')
def mesh_object(name,p,f,uv=None,mi=None,ws=None,fixed=None):
    mesh=bpy.data.meshes.new(name);mesh.from_pydata(p,[],f);mesh.update();ob=bpy.data.objects.new(name,mesh);bpy.context.collection.objects.link(ob)
    for m in MATS:mesh.materials.append(m)
    if uv is not None:
        layer=mesh.uv_layers.new(name='Original UV')
        for polygon in mesh.polygons:
            for i in polygon.loop_indices:layer.data[i].uv=uv[mesh.loops[i].vertex_index]
    for poly in mesh.polygons:poly.material_index=mi[poly.index] if mi is not None else 0;poly.use_smooth=True
    weights(ob,ws,fixed);return ob
original=mesh_object('ORIGINAL • SKC 1482 triangles',P,F,UV,MI,W)
# Original comparison uses the exact unmodified source images and material values.
for i in range(5):
    m=bpy.data.materials.new('Source material '+str(i));m.use_nodes=True;p=m.node_tree.nodes.get('Principled BSDF');p.inputs['Roughness'].default_value=.85;t=m.node_tree.nodes.new('ShaderNodeTexImage');t.image=bpy.data.images.load(os.path.join(SRC,'textures/nm001f01.jpg'if i in[2,3]else'textures/nm001b01.png'),check_existing=True);t.extension='EXTEND';m.node_tree.links.new(t.outputs['Color'],p.inputs['Base Color'])
    if i in[0,1,4]:m.node_tree.links.new(t.outputs['Alpha'],p.inputs['Alpha']);m.surface_render_method='DITHERED'
    original.data.materials[i]=m
enhanced=mesh_object('HD • tailored base surface',P,F,UV,MI,W)
bpy.context.view_layer.objects.active=enhanced;enhanced.select_set(True);original.select_set(False)
bm=bmesh.new();bm.from_mesh(enhanced.data);bmesh.ops.remove_doubles(bm,verts=list(bm.verts),dist=.00005)
# The UVs are face-corner data and survive welding. Weight-equivalent seams only.
bmesh.ops.join_triangles(bm,faces=list(bm.faces),cmp_seam=True,cmp_sharp=True,cmp_uvs=True,cmp_materials=True,angle_face_threshold=math.radians(35),angle_shape_threshold=math.radians(45))
crease=bm.edges.layers.float.get('crease_edge')or bm.edges.layers.float.new('crease_edge')
for edge in bm.edges:
    if len(edge.link_faces)!=2:edge[crease]=1
    elif edge.calc_face_angle(0)>math.radians(65):edge[crease]=.8
    elif edge.link_faces[0].material_index!=edge.link_faces[1].material_index:edge[crease]=.72
    else:edge[crease]=.12 if edge.calc_face_angle(0)>math.radians(35)else 0
bm.to_mesh(enhanced.data);bm.free()
sub=enhanced.modifiers.new('Surface refinement • authored creases preserved','SUBSURF');sub.subdivision_type='CATMULL_CLARK';sub.levels=2;sub.render_levels=2;sub.uv_smooth='PRESERVE_BOUNDARIES'
bpy.ops.object.modifier_apply(modifier=sub.name)
# Corrective sculpt pass: preserve the nose ridge and jaw, soften T-pose knuckles.
for v in enhanced.data.vertices:
    x,y,z=v.co
    if 33.1<z<35.7 and y<-1.15 and abs(x)<1.3:
        ridge=math.exp(-(x/.24)**2-((z-34.18)/.6)**2);v.co.y-=.045*ridge
        jaw=math.exp(-((z-33.25)/.42)**2)*max(0,1-abs(x)/1.4);v.co.z-=.025*jaw
enhanced.data.update();DETAILS=[]

def tube(name,points,radius,mat=5,cyclic=False,fixed=None):
    curve=bpy.data.curves.new(name,'CURVE');curve.dimensions='3D';curve.resolution_u=3;curve.bevel_depth=radius;curve.bevel_resolution=1
    spl=curve.splines.new('POLY' if cyclic else 'BEZIER')
    if cyclic:
        spl.points.add(len(points)-1)
        for b,p in zip(spl.points,points):b.co=(*p,1)
    else:
        spl.bezier_points.add(len(points)-1)
        for b,p in zip(spl.bezier_points,points):b.co=p;b.handle_left_type='AUTO';b.handle_right_type='AUTO'
    spl.use_cyclic_u=cyclic;ob=bpy.data.objects.new(name,curve);bpy.context.collection.objects.link(ob);bpy.ops.object.select_all(action='DESELECT');ob.select_set(True);bpy.context.view_layer.objects.active=ob;bpy.ops.object.convert(target='MESH')
    for m in MATS:ob.data.materials.append(m)
    for p in ob.data.polygons:p.material_index=mat;p.use_smooth=True
    weights(ob,fixed=fixed);DETAILS.append(ob);return ob
def ring(name,center,radii,axis='Z',radius=.045,mat=5):
    pts=[]
    for i in range(32):
        a=2*math.pi*i/32
        if axis=='Z':p=(center[0]+radii[0]*math.cos(a),center[1]+radii[1]*math.sin(a),center[2])
        else:p=(center[0],center[1]+radii[0]*math.cos(a),center[2]+radii[1]*math.sin(a))
        pts.append(p)
    return tube(name,pts,radius,mat,True)
# New continuous rolled collar and stitched edging, fitted to original coat vertices.
for side in[-1,1]:
    inner=[(side*1.54,-1.61,31.83),(side*1.44,-2.78,29.55),(side*1.52,-3.055,27.86),(side*1.47,-3.055,26.05)]
    tube(('L'if side<0 else'R')+' rolled gold lapel',inner,.052)
    tube(('L'if side<0 else'R')+' inset lapel stitch',[(x+side*.15,y-.005,z)for x,y,z in inner],.020,9)
    for i in range(2):ring('Raised sleeve cuff '+str(side)+' '+str(i),(side*(7.75+i*.15),0,30.6),(1.28,1.42),'X',.045,5)
    for i in range(2):ring('Leather glove seam '+str(side)+' '+str(i),(side*(13.65+i*.16),0,30.5),(.67,.79),'X',.025,9)
# Waist trim and a three-part buckle are new geometry, rather than painted highlights.
for z in[23.25,23.52]:ring('Waist rolled edge '+str(z),(0,0,z),(2.75,2.25),'Z',.045,5)
tube('Angular belt buckle',[(-.46,-2.31,23.18),(-.46,-2.35,23.6),(.46,-2.35,23.6),(.46,-2.31,23.18)],.065,5,True)
tube('Buckle tongue',[(0,-2.42,23.24),(0,-2.42,23.55)],.045,5)
# Sculpted tapered hair locks: each is a real closed, curved six-sided strip.
# The head keeps its original silhouette and 100% bone13 binding.
rng=np.random.default_rng(3081)
def lock(name,points,width,mat):
    points=[Vector(p)for p in points];p=[];f=[];steps=9;sides=6
    for i in range(steps):
        t=i/(steps-1);s=1-t;c=s*s*s*points[0]+3*s*s*t*points[1]+3*s*t*t*points[2]+t*t*t*points[3]
        tangent=(-3*s*s*points[0]+(3*s*s-6*s*t)*points[1]+(6*s*t-3*t*t)*points[2]+3*t*t*points[3]).normalized();a=tangent.cross(Vector((0,0,1)))
        if a.length<.01:a=tangent.cross(Vector((0,1,0)))
        a.normalize();b=tangent.cross(a).normalized();w=width*(.4+.75*math.sin(t*math.pi*.9))*(1-t)**.55+.008
        for j in range(sides):
            ang=j*math.tau/sides;p.append(tuple(c+a*(math.cos(ang)*w)+b*(math.sin(ang)*w*.30)))
    for i in range(steps-1):
        for j in range(sides):f.append((i*sides+j,i*sides+(j+1)%sides,(i+1)*sides+(j+1)%sides,(i+1)*sides+j))
    f.append(tuple(range(sides-1,-1,-1)));f.append(tuple((steps-1)*sides+j for j in range(sides)))
    ob=mesh_object(name,p,f,fixed=13)
    for poly in ob.data.polygons:poly.material_index=mat
    DETAILS.append(ob)
for i in range(22):
    angle=math.tau*i/22;rx=1.75*math.cos(angle);ry=2.25*math.sin(angle);back=ry>0
    z=33.3 if back else 34.8;z+=float(rng.uniform(-.32,.25));end=(rx,ry,z)
    lock('Sculpted crown lock '+str(i),[(rx*.15,ry*.13,37.15),(rx*.65,ry*.45,37.45),(rx*1.05,ry*.95,35.9),end],float(rng.uniform(.08,.15)),7+i%2)
for side in[-1,1]:
    for i in range(5):
        x=side*(.30+i*.30);y=-1.5+i*.08;endx=side*(.40+i*.28)
        lock('Layered face fringe '+str(side)+' '+str(i),[(x*.65,-.60,37.1),(x,-1.75,37.0),(endx,-2.11,35.9),(endx+side*.1,-1.96+i*.09,34.9-i*.23)],.08+i*.009,7+i%2)

def rig(name,objects,x=0):
    data=bpy.data.armatures.new(name);arm=bpy.data.objects.new(name,data);bpy.context.collection.objects.link(arm);bpy.context.view_layer.objects.active=arm;arm.select_set(True);bpy.ops.object.mode_set(mode='EDIT')
    for e in B:
        data.edit_bones.new(e['name'])
    for e in B:
        parent=resolve(e['parent'])
        if parent in data.edit_bones:data.edit_bones[e['name']].parent=data.edit_bones[parent]
    # Set orientation after the hierarchy. Blender's matrix setter followed by
    # length/parent edits did not preserve the native rest axes in Blender 5.4.
    for e in B:
        b=data.edit_bones[e['name']];m=REST[e['name']]@C
        b.head=m.translation;b.tail=b.head+m.to_3x3().col[1]*.8
        b.align_roll(m.to_3x3().col[2])
    bpy.ops.object.mode_set(mode='OBJECT');arm.show_in_front=True;arm.location.x=x
    rest_error=max(abs(arm.data.bones[e['name']].matrix_local[i][j]-(REST[e['name']]@C)[i][j])for e in B for i in range(4)for j in range(4))
    if rest_error>1e-4:raise ValueError(f'Native bind axes changed in Blender: {rest_error}')
    arm['native_rest_max_error']=rest_error
    for ob in objects:
        mod=ob.modifiers.new('Original 30 bone rig','ARMATURE');mod.object=arm;ob.parent=arm
    for e in D:
        ob=bpy.data.objects.new(e['name'],None);bpy.context.collection.objects.link(ob);ob.empty_display_type='ARROWS';ob.empty_display_size=.6;ob.matrix_world=REST[e['name']];ob.parent=arm;ob['native_parent']=e['parent'];ob['native_quaternion_wxyz']=e['quaternion'];ob['attachment_dummy']=True;ob.hide_render=True
    arm['source_skeleton']='p0.bnc';arm['bone_count']=30;arm['dummy_count']=6;arm['native_rest_entries']=json.dumps(entries)
    return arm

def export():
    p=[];uv=[];si=[];sw=[];faces=[];normals=[]
    for ob in[enhanced]+DETAILS:
        mesh=ob.data;mesh.calc_loop_triangles();layer=mesh.uv_layers.active;remap={};normal_list=mesh.corner_normals
        for tri in mesh.loop_triangles:
            inds=[]
            for li in tri.loops:
                loop=mesh.loops[li];v=mesh.vertices[loop.vertex_index];vt=tuple(layer.data[li].uv)if layer else(0,0);n=tuple(normal_list[li].vector);groups=sorted([(g.group,g.weight)for g in v.groups if g.weight>0],key=lambda x:-x[1])[:4];total=sum(w for b,w in groups)or 1
                key=(loop.vertex_index,round(vt[0],7),round(vt[1],7),*(round(k,6)for k in n))
                if key not in remap:
                    remap[key]=len(p)//3;p.extend(round(k,6)for k in v.co);uv.extend(round(k,7)for k in vt);normals.extend(round(k,6)for k in n)
                    si.extend([g[0]for g in groups]+[0]*(4-len(groups)));sw.extend([round(g[1]/total,7)for g in groups]+[0]*(4-len(groups)))
                inds.append(remap[key])
            faces.append(dict(material=tri.material_index,indices=inds))
    skin=dict(schema=1,coordinateSystem='original-native-Z-up',materials=MATERIAL_SPECS,positions=p,uvs=uv,skinIndices=si,skinWeights=sw,faces=faces,normals=normals,vertexCount=len(p)//3,triangleCount=len(faces))
    with open(os.path.join(OUT,'mesh.json'),'w')as f:json.dump(skin,f,separators=(',',':'))
    manifest=dict(schema=1,characterId=0,label='孟星魂 · 高清试制',mesh='mesh.json',source='Blender 5.4 / original p0.skc + p0.bnc',stats=dict(originalVertices=1290,originalTriangles=1482,vertices=skin['vertexCount'],triangles=skin['triangleCount'],bones=30,dummies=6,modeledHairLocks=32),provenance=dict(geometry='Local Blender crease-aware surface refinement plus modeled tapered hair, rolled lapels, sleeve/glove/waist seams and buckle. Original skeleton and animations unchanged.',body='Original 256px color interpolated in Blender to 2048px, small procedural cloth weave, roughness and normal detail. Not hand-painted or recovered detail.',face='AI-assisted face texture redraw constrained to original UV layout; reviewed on original mapped geometry.',limits='First-pass enhancement. Original body proportions, generic hands and old animation deformation remain. Not a full manual retopology or high-end sculpt.'))
    with open(os.path.join(OUT,'manifest.json'),'w')as f:json.dump(manifest,f,ensure_ascii=False,indent=2)
    print('EXPORTED',manifest['stats'],flush=True);return manifest
manifest=export()
orig_rig=rig('ORIGINAL RIG • 30 bones + 6 attachments',[original],-12)
hd_rig=rig('HD RIG • same original bind',[enhanced]+DETAILS,12)

def set_pose(arm,world,keyframe=False):
    # Native matrices are local to the armature, so comparison placement is separate.
    for e in B:
        b=arm.pose.bones[e['name']];b.rotation_mode='QUATERNION';rest=b.bone.matrix_local;target=world[e['name']]@C
        if b.parent:
            parent_rest=b.parent.bone.matrix_local;parent_target=world[b.parent.name]@C
            b.matrix_basis=rest.inverted()@parent_rest@parent_target.inverted()@target
        else:b.matrix_basis=rest.inverted()@target
    bpy.context.view_layer.update()
    if keyframe:
        for b in arm.pose.bones:b.rotation_mode='QUATERNION';b.keyframe_insert('location');b.keyframe_insert('rotation_quaternion');b.keyframe_insert('scale')
idle=animation_frame(os.path.join(SRC,'p0.amb'),1)
for arm in[orig_rig,hd_rig]:set_pose(arm,idle)
scene=bpy.context.scene;scene.render.engine='CYCLES';scene.cycles.samples=40;scene.cycles.use_denoising=True
scene.world.color=(.16,.18,.20);scene.render.resolution_x=1600;scene.render.resolution_y=1200;scene.render.resolution_percentage=100
scene.view_settings.view_transform='AgX'
def track(o,target):o.rotation_euler=(Vector(target)-o.location).to_track_quat('-Z','Y').to_euler()
for name,loc,power,size,col in [('Key softbox',(20,-45,70),25000,42,(1,.91,.80)),('Fill softbox',(-45,-15,40),15000,38,(.72,.84,1)),('Rim softbox',(15,30,55),26000,32,(.72,1,.91))]:
    bpy.ops.object.light_add(type='AREA',location=loc);l=bpy.context.object;l.name=name;l.data.energy=power;l.data.shape='DISK';l.data.size=size;l.data.color=col;track(l,(0,0,20))
floor_mat=bpy.data.materials.new('Studio floor');floor_mat.diffuse_color=(.075,.085,.095,1)
bpy.ops.mesh.primitive_plane_add(size=220,location=(0,0,-.05));floor=bpy.context.object;floor.name='Comparison studio floor';floor.data.materials.append(floor_mat)
bpy.ops.object.camera_add(location=(46,-110,47));camera=bpy.context.object;camera.name='Identical comparison camera';track(camera,(0,0,20));camera.data.type='ORTHO';camera.data.ortho_scale=57;scene.camera=camera
scene.render.image_settings.file_format='PNG'
def render(name,loc,target,scale,size):
    camera.location=loc;track(camera,target);camera.data.ortho_scale=scale;scene.render.resolution_x=size[0];scene.render.resolution_y=size[1];scene.render.filepath=os.path.join(WORK,name+'.png');bpy.ops.render.render(write_still=True)
# Both characters are rigged and render in exactly the same authored idle frame.
if not options.skip_render:
    render('p0-comparison-full',(46,-110,47),(0,0,20),57,(1600,1200))
    # Dedicated original / enhanced closeups share camera relative to their rig.
    enhanced.hide_render=False
    for label,arm,other in[('original',orig_rig,hd_rig),('enhanced',hd_rig,orig_rig)]:
        for child in other.children:child.hide_render=True
        for child in arm.children:
            if child.type=='MESH':child.hide_render=False
        render('p0-'+label+'-face',(arm.location.x+9,-36,37),(arm.location.x,0,34),10,(1000,1000))
        for child in other.children:
            if child.type=='MESH':child.hide_render=False
    render('p0-comparison-full',(46,-110,47),(0,0,20),57,(1600,1200))
# Pack textures, retain import/editable mesh + rig + camera for manual refinement.
for image in bpy.data.images:
    if image.source=='FILE':
        try:image.pack()
        except:pass
scene['README']='LEFT original 1482 tris; RIGHT enhanced Blender prototype. Same source p0 idle frame, skeleton, camera/light. Runtime exports live in work/character-hd/retired-assets. Edit this file or rerun scripts/blender/build_p0_hd.py.'
bpy.ops.wm.save_as_mainfile(filepath=os.path.join(WORK,'孟星魂-高清对照.blend'))
with open(os.path.join(WORK,'build-evidence.json'),'w')as f:json.dump(dict(blender=bpy.app.version_string,manifest=manifest,originalHashes={n:hashlib.sha256(open(os.path.join(SRC,n),'rb').read()).hexdigest()for n in['p0.skc','p0.bnc','p0.amb']},renderPose=dict(source=1,frame=1)),f,ensure_ascii=False,indent=2)
print('DONE',flush=True)
