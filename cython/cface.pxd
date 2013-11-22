from libcpp cimport bool

cdef extern from "face.h":
	bool getFaceCoord(int* x, int* y)
	bool init()
	void finalize()
