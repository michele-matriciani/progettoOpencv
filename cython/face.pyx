cimport cface

def init():
    return cface.init()

def finalize():
    cface.finalize()

def get_face_coord():
    cdef int x=0, y=0, retval 
    retval = cface.getFaceCoord(&x , &y)
    return (retval,x,y)
