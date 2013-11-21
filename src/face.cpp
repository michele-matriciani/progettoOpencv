#include "face.h"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <stdio.h>

using namespace std;


namespace {

    //String window_name = "Capture - face detection";
    cv::String face_cascade_name = "haarcascade_frontalface_alt.xml";
    cv::CascadeClassifier* face_cascade;

}

cv::CascadeClassifier* init_cascade(const string& cascade, bool& ok ) {

    cv::CascadeClassifier* face_cascade = new cv::CascadeClassifier();

    if( ! (*face_cascade).load( cascade ) ) {
         std::cerr << "--(!)Error loading face cascade" << std::endl; 
         ok = false;    
    }
    else {
        ok = true;
    }

    return face_cascade;
}

cv::Point detectAndDisplay( cv::Mat frame );

int getFaceCoord(int* x, int* y ) {

   

    cv::Mat frame;
    

    cv::VideoCapture capture;

    //-- 1. Load the cascades
    bool ok;
    face_cascade = init_cascade("haarcascade_frontalface_alt.xml",ok);    
    
    if( !ok ) { 
        return -1; 
    }	


    printf("CIAO\n");

    //-- 2. Read the video stream
    capture.open( -1 );

    if ( !capture.isOpened() ) { 
        printf("--(!)Error opening video capture\n"); 
        return -2; 
    }

    while ( capture.read(frame) ) {

        if( frame.empty() )
        {
            printf(" --(!) No captured frame -- Break!");
            break;
        }

        //-- 3. Apply the classifier to the frame
        cv::Point pt = detectAndDisplay( frame );
        *x = pt.x;
        *y = pt.y;
        
       
        break;
    }

    capture.release();
    delete face_cascade;
    
    return 1;
}

cv::Point detectAndDisplay( cv::Mat frame ) //usa frame e face_cascade
{
    std::vector<cv::Rect> faces;
    
    double scale = 1;
    cv::Mat frame_gray;

    cv::cvtColor( frame, frame_gray, cv::COLOR_BGR2GRAY );
    cv::equalizeHist( frame_gray, frame_gray );

    //-- Detect faces
    face_cascade->detectMultiScale( frame_gray, faces, 1.1, 1, 0|cv::CASCADE_SCALE_IMAGE, 
                                    cv::Size(frame.cols*0.4,frame.rows*0.4) );
    
    
    cv::Point center;
    if (faces.size() == 1 ) { //PROVA UNO SOLO
    
    int i = 0;
     
    vector<cv::Rect>::const_iterator r = faces.begin();

    cv::Mat smallImgROI;
    std::vector<cv::Rect> nestedObjects;
     
	    //Scalar color = colors[i%8];
    int radius;
    center.x = cvRound((r->x + r->width*0.5)*scale);
    center.y = cvRound((r->y + r->height*0.5)*scale);

    radius = cvRound((r->width + r->height)*0.25*scale);
    cv::circle( frame, center, radius, cv::Scalar( 255, 0, 255 ), 3, 8, 0 );
         
    }

    //imshow( window_name, frame );
    return cv::Point(center);

}
