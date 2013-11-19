#include "face.h"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

namespace {

    String window_name = "Capture - face detection";
    String face_cascade_name = "haarcascade_frontalface_alt.xml";
    CascadeClassifier face_cascade;

}

Point detectAndDisplay( Mat frame );

int getFaceCoord(int* x, int* y ) {

   

    
    

    VideoCapture capture;
    Mat frame;

    //-- 1. Load the cascades
    if( !face_cascade.load( face_cascade_name ) ){ printf("--(!)Error loading face cascade\n"); return -1; };	
    printf("CIAO\n");

    //-- 2. Read the video stream
    capture.open( -1 );
    if ( !capture.isOpened() ) { printf("--(!)Error opening video capture\n"); return -1; }

    while ( capture.read(frame) )
    {
        if( frame.empty() )
        {
            printf(" --(!) No captured frame -- Break!");
            break;
        }

        //-- 3. Apply the classifier to the frame
        Point pt = detectAndDisplay( frame );
        *x = pt.x;
        *y = pt.y;
        return 1;
        
    }
    return 0;

}

Point detectAndDisplay( Mat frame )
{
    std::vector<Rect> faces;
    
    double scale = 1;
    Mat frame_gray;

    cvtColor( frame, frame_gray, COLOR_BGR2GRAY );
    equalizeHist( frame_gray, frame_gray );

    //-- Detect faces
    face_cascade.detectMultiScale( frame_gray, faces, 1.1, 1, 0|CASCADE_SCALE_IMAGE, Size(frame.cols*0.4,frame.rows*0.4) );
    
    
    Point center;
  if (faces.size() == 1 ) { //PROVA UNO SOLO
    
     int i = 0;
     
     vector<Rect>::const_iterator r = faces.begin();

     Mat smallImgROI;
     vector<Rect> nestedObjects;
     
	    //Scalar color = colors[i%8];
     int radius;
     center.x = cvRound((r->x + r->width*0.5)*scale);
     center.y = cvRound((r->y + r->height*0.5)*scale);

     radius = cvRound((r->width + r->height)*0.25*scale);
     circle( frame, center, radius, Scalar( 255, 0, 255 ), 3, 8, 0 );
     
     
		//-- Show what you got
     
     
 }

 imshow( window_name, frame );
 return Point(center);

}
