cimport cface

cdef int get_face_coord(int *x, int *y):
    return cface.getFaceCoord(x , y)
	
