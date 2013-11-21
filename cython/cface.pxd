from libcpp cimport bool

cdef extern from "face.h":
	int getFaceCoord(int* x, int* y)
	bool init()
