#include <iosfwd>

namespace cv {
	class CascadeClassifier;
}

cv::CascadeClassifier* init_cascade(const std::string& cascade, bool& ok);
//VideoCapture init_video();

int getFaceCoord( int* x, int* y );
