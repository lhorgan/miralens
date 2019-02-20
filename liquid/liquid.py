import bpy, bmesh, math

def make_prism_frame(angle_x, angle_y, width, height, thickness, spacing, bm):
    rad_angle_x = angle_x * (math.pi / 180)
    rad_angle_y = angle_y * (math.pi / 180)
    
    tri_x_height = width * math.tan(rad_angle_x)
    tri_y_width = height * math.tan(rad_angle_y)
    
    sub_tri_x_height = thickness * math.tan(rad_angle_x)
    sub_tri_y_width = thickness * math.tan(rad_angle_y)
    
    print("%f, %f" % (tri_x_height, tri_y_width))
    
    # bottom face
    a = bm.verts.new((0, 0, 0))
    b = bm.verts.new((width, tri_x_height, 0))
    c = bm.verts.new((width, tri_x_height + tri_y_width + spacing, 0))
    d = bm.verts.new((0, tri_x_height + tri_y_width + spacing, 0))
    
    aa = a
    ab = bm.verts.new((thickness, sub_tri_x_height, 0))
    ac = bm.verts.new((thickness, thickness + sub_tri_x_height, 0))
    ad = bm.verts.new((0, thickness, 0))
    
    ba = bm.verts.new((b.co.x - thickness, b.co.y - sub_tri_x_height, 0))
    bb = b
    bc = bm.verts.new((b.co.x, b.co.y + thickness, 0))
    bd = bm.verts.new((ba.co.x, ba.co.y + thickness, 0))
    
    ca = bm.verts.new((c.co.x - thickness, c.co.y - thickness, 0))
    cb = bm.verts.new((c.co.x, c.co.y - thickness, 0))
    cc = c
    cd = bm.verts.new((c.co.x - thickness, c.co.y, 0))
    
    da = bm.verts.new((d.co.x, d.co.y - thickness, 0))
    db = bm.verts.new((d.co.x + thickness, d.co. y - thickness, 0))
    dc = bm.verts.new((d.co.x + thickness, d.co.y, 0))
    dd = d
    
    
    # top face
    a2 = bm.verts.new((a.co.x, a.co.y, height))
    b2 = bm.verts.new((b.co.x, b.co.y, height))
    c2 = bm.verts.new((c.co.x, c.co.y - tri_y_width, height))
    d2 = bm.verts.new((d.co.x, d.co.y - tri_y_width, height))
    
    a2a = a2#bm.verts.new((aa.co.x, aa.co.y, height))
    a2b = bm.verts.new((ab.co.x, ab.co.y, height))
    a2c = bm.verts.new((ac.co.x, ac.co.y, height))
    a2d = bm.verts.new((ad.co.x, ad.co.y, height))
    
    b2a = bm.verts.new((ba.co.x, ba.co.y, height))
    b2b = b2#bm.verts.new((bb.co.x, bb.co.y, height))
    b2c = bm.verts.new((bc.co.x, bc.co.y, height))
    b2d = bm.verts.new((bd.co.x, bd.co.y, height))
    
    c2a = bm.verts.new((c2.co.x - thickness, c2.co.y - thickness, height))
    c2b = bm.verts.new((c2.co.x, c2.co.y - thickness, height))
    c2c = c2 #bm.verts.new((c2.co.x, c2.co.y, height))
    c2d = bm.verts.new((c2.co.x - thickness, c2.co.y, height))
    
    d2a = bm.verts.new((d2.co.x, d2.co.y - thickness, height))
    d2b = bm.verts.new((d2.co.x + thickness, d2.co.y - thickness, height))
    d2c = bm.verts.new((d2.co.x + thickness, d2.co.y, height))
    d2d = d2
    
    # top of the bottom
    aap = bm.verts.new((aa.co.x, aa.co.y, thickness)) 
    abp = bm.verts.new((ab.co.x, ab.co.y, thickness)) 
    acp = bm.verts.new((ac.co.x, ac.co.y, thickness)) 
    adp = bm.verts.new((ad.co.x, ad.co.y, thickness)) 
    
    bap = bm.verts.new((ba.co.x, ba.co.y, thickness)) 
    bbp = bm.verts.new((bb.co.x, bb.co.y, thickness)) 
    bcp = bm.verts.new((bc.co.x, bc.co.y, thickness)) 
    bdp = bm.verts.new((bd.co.x, bd.co.y, thickness))
    
    cap = bm.verts.new((ca.co.x, ca.co.y - sub_tri_y_width, thickness)) 
    cbp = bm.verts.new((cb.co.x, cb.co.y - sub_tri_y_width, thickness)) 
    ccp = bm.verts.new((cc.co.x, cc.co.y - sub_tri_y_width, thickness)) 
    cdp = bm.verts.new((cd.co.x, cd.co.y - sub_tri_y_width, thickness))
    
    dap = bm.verts.new((da.co.x, da.co.y - sub_tri_y_width, thickness)) 
    dbp = bm.verts.new((db.co.x, db.co.y - sub_tri_y_width, thickness)) 
    dcp = bm.verts.new((dc.co.x, dc.co.y - sub_tri_y_width, thickness)) 
    ddp = bm.verts.new((dd.co.x, dd.co.y - sub_tri_y_width, thickness))
    
    # bottom of the top
    a2ap = bm.verts.new((a2a.co.x, a2a.co.y, a2a.co.z - thickness)) 
    a2bp = bm.verts.new((a2b.co.x, a2b.co.y, a2a.co.z - thickness)) 
    a2cp = bm.verts.new((a2c.co.x, a2c.co.y, a2a.co.z - thickness)) 
    a2dp = bm.verts.new((a2d.co.x, a2d.co.y, a2a.co.z - thickness))
    
    b2ap = bm.verts.new((b2a.co.x, b2a.co.y, b2a.co.z - thickness)) 
    b2bp = bm.verts.new((b2b.co.x, b2b.co.y, b2a.co.z - thickness)) 
    b2cp = bm.verts.new((b2c.co.x, b2c.co.y, b2a.co.z - thickness)) 
    b2dp = bm.verts.new((b2d.co.x, b2d.co.y, b2a.co.z - thickness))
    
    c2ap = bm.verts.new((c2a.co.x, c2a.co.y + sub_tri_y_width, c2a.co.z - thickness)) 
    c2bp = bm.verts.new((c2b.co.x, c2b.co.y + sub_tri_y_width, c2a.co.z - thickness)) 
    c2cp = bm.verts.new((c2c.co.x, c2c.co.y + sub_tri_y_width, c2a.co.z - thickness)) 
    c2dp = bm.verts.new((c2d.co.x, c2d.co.y + sub_tri_y_width, c2a.co.z - thickness))
    
    d2ap = bm.verts.new((d2a.co.x, d2a.co.y + sub_tri_y_width, d2a.co.z - thickness)) 
    d2bp = bm.verts.new((d2b.co.x, d2b.co.y + sub_tri_y_width, d2a.co.z - thickness)) 
    d2cp = bm.verts.new((d2c.co.x, d2c.co.y + sub_tri_y_width, d2a.co.z - thickness)) 
    d2dp = bm.verts.new((d2d.co.x, d2d.co.y + sub_tri_y_width, d2a.co.z - thickness))
    
    ''' bottom '''
    # front bottom left corner
    bm.faces.new((a, ab, ac, ad))
    bm.faces.new((a, ab, abp, aap))
    bm.faces.new((ad, a, aap, adp))
    
    # front bottom right corner
    bm.faces.new((ba, b, bc, bd))
    bm.faces.new((b, bc, bcp, bbp))
    bm.faces.new((ba, b, bbp, bap))
    
    bm.faces.new((cb, c, ccp, cbp))
    bm.faces.new((ca, cb, c, cd))
    bm.faces.new((cd, c, ccp, cdp))
    
    # back bottom left corner
    bm.faces.new((da, db, dc, d))
    bm.faces.new((d, da, dap, ddp))
    bm.faces.new((d, dc, dcp, ddp))
    
    # front bottom left to back bottom left
    bm.faces.new((ad, da, dap, adp))
    bm.faces.new((ad, ac, db, da))
    bm.faces.new((ac, acp, dbp, db))
    bm.faces.new((adp, acp, dbp, dap))
    
    # back bottom left to back bottom right
    bm.faces.new((dc, db, ca, cd))
    bm.faces.new((db, ca, cap, dbp))
    bm.faces.new((dbp, cap, cdp, dcp))
    bm.faces.new((dc, cd, cdp, dcp))
    
    # back bottom right to front bottom right
    bm.faces.new((ca, cb, bc, bd))
    bm.faces.new((ca, cap, bdp, bd))
    bm.faces.new((cap, bdp, bcp, cbp))
    bm.faces.new((bc, cb, cbp, bcp))
    
    # front bottom right to front bottom left
    bm.faces.new((bd, ba, ab, ac))
    bm.faces.new((ab, abp, bap, ba))
    bm.faces.new((acp, abp, bap, bdp))
    bm.faces.new((ac, acp, bdp, bd))
    
    ''' top '''
    # front top left corner
    bm.faces.new((a2, a2b, a2c, a2d))
    bm.faces.new((a2, a2b, a2bp, a2ap))
    bm.faces.new((a2d, a2, a2ap, a2dp))
    
    # front top right corner
    bm.faces.new((b2a, b2, b2c, b2d))
    bm.faces.new((b2, b2c, b2cp, b2bp))
    bm.faces.new((b2a, b2, b2bp, b2ap))
    
    bm.faces.new((c2b, c2, c2cp, c2bp))
    bm.faces.new((c2a, c2b, c2, c2d))
    bm.faces.new((c2d, c2, c2cp, c2dp))
    
    # back top left corner
    bm.faces.new((d2a, d2b, d2c, d2))
    bm.faces.new((d2, d2a, d2ap, d2dp))
    bm.faces.new((d2, d2c, d2cp, d2dp))
    
    # front top left to back bottom left
    bm.faces.new((a2d, d2a, d2ap, a2dp))
    bm.faces.new((a2d, a2c, d2b, d2a))
    bm.faces.new((a2c, a2cp, d2bp, d2b))
    bm.faces.new((a2dp, a2cp, d2bp, d2ap))
    
    # back top left to back bottom right
    bm.faces.new((d2c, d2b, c2a, c2d))
    bm.faces.new((d2b, c2a, c2ap, d2bp))
    bm.faces.new((d2bp, c2ap, c2dp, d2cp))
    bm.faces.new((d2c, c2d, c2dp, d2cp))
    
    # back top right to front bottom right
    bm.faces.new((c2a, c2b, b2c, b2d))
    bm.faces.new((c2a, c2ap, b2dp, b2d))
    bm.faces.new((c2ap, b2dp, b2cp, c2bp))
    bm.faces.new((b2c, c2b, c2bp, b2cp))
    
    # front top right to front bottom left
    bm.faces.new((b2d, b2a, a2b, a2c))
    bm.faces.new((a2b, a2bp, b2ap, b2a))
    bm.faces.new((a2cp, a2bp, b2ap, b2dp))
    bm.faces.new((a2c, a2cp, b2dp, b2d))
    
    ''' vertical bars'''
    # front left
    bm.faces.new((aap, abp, a2bp, a2ap))
    bm.faces.new((abp, acp, a2cp, a2bp))
    bm.faces.new((adp, acp, a2cp, a2dp))
    bm.faces.new((adp, aap, a2ap, a2dp))
    
    # front right
    bm.faces.new((bap, bbp, b2bp, b2ap))
    bm.faces.new((bbp, bcp, b2cp, b2bp))
    bm.faces.new((bdp, bcp, b2cp, b2dp))
    bm.faces.new((bdp, bap, b2ap, b2dp))
    
    bm.faces.new((ccp, cbp, c2bp, c2ap))
    bm.faces.new((cbp, ccp, c2cp, c2bp))
    bm.faces.new((cdp, ccp, c2cp, c2dp))
    bm.faces.new((cdp, cap, c2ap, c2dp))
    
    bm.faces.new((ddp, dbp, d2bp, d2ap))
    bm.faces.new((dbp, dcp, d2cp, d2bp))
    bm.faces.new((ddp, dcp, d2cp, d2dp))
    bm.faces.new((ddp, dap, d2ap, d2dp))
    
def main():
    obj = bpy.context.object
    me = obj.data
    bm = bmesh.from_edit_mesh(me)

    make_prism_frame(30, 30, 1.5, 1.5, 0.0625, 0.25, bm)

    bmesh.update_edit_mesh(obj.data)

    # This is optional, you could also stay in editmode.
    #bpy.ops.object.mode_set(mode='OBJECT')
    
main()
