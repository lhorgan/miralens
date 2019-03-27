import bpy, bmesh

obj = bpy.context.object
me = obj.data
bm = bmesh.from_edit_mesh(me)

def make_box(xs, ys, zs, x, y, z):
    vb1 = bm.verts.new((x, y, z))
    vb2 = bm.verts.new((x + xs, y, z))
    vb3 = bm.verts.new((x + xs, y + ys, z))
    vb4 = bm.verts.new((x, y + ys, z))
    
    vt1 = bm.verts.new((x, y, z + zs))
    vt2 = bm.verts.new((x + xs, y, z + zs))
    vt3 = bm.verts.new((x + xs, y + ys, z + zs))
    vt4 = bm.verts.new((x, y + ys, z + zs))
    
    bm.faces.new((vb1, vb2, vb3, vb4))
    bm.faces.new((vt1, vt2, vt3, vt4))
    
    bm.faces.new((vb1, vb2, vt2, vt1))
    bm.faces.new((vb3, vb4, vt4, vt3))
    
    bm.faces.new((vb1, vb4, vt4, vt1))
    bm.faces.new((vb2, vb3, vt3, vt2))

#bm.faces.new((v1, v2, v3))

def make_boxes(rows, cols, xs, ys, zs, space):
    x = 0
    y = 0
    z = 0
    for row in range(rows):
        for col in range(cols):
            make_box(xs, ys, zs, x, y, z)
            x += xs + space
        z += zs + space
        x = 0
        
    make_box(xs * cols + space * (cols + 1), ys, zs * rows + space * (rows + 1), -space, 0, -space)
        
make_boxes(4, 5, 43.6, 35, 43.6, 1.575)

bmesh.update_edit_mesh(obj.data)
