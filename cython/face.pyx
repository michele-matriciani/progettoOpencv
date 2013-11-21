cimport cface

def init():
    return cface.init()

def get_face_coord():
    cdef int x, y, retval 
    retval = cface.getFaceCoord(&x , &y)
    return (retval,x,y)

