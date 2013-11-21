cimport cface

def get_face_coord():
    cdef int x, y 
    retval = cface.getFaceCoord(&x , &y)
    return (retval,x,y)

