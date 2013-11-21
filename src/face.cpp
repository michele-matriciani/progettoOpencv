#include "face.h"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <stdio.h>


namespace {
    cv::CascadeClassifier* face_cascade;
    cv::VideoCapture* capture;
    
    cv::CascadeClassifier* init_cascade(const std::string& cascade, bool& ok ) {

        face_cascade = new cv::CascadeClassifier();

        if( ! face_cascade->load( cascade ) ) {
             std::cerr << "--(!)Error loading face cascade" << std::endl; 
             delete face_cascade;
             ok = false;    
        }
        else {
            ok = true;
        }

        return face_cascade;
    }

    cv::VideoCapture* init_video(bool& ok) {

        capture = new cv::VideoCapture();

        capture->open( -1 );

        if ( !capture->isOpened() ) { 
            std::cerr << "--(!)Error opening video capture" << std::endl; 
            delete capture;
            ok = false; 
        }
        else {
            ok = true;
        }

        return capture;
    }
}


cv::Point detectAndDisplay( cv::Mat, cv::CascadeClassifier* );


bool init() {
    bool ok;
    face_cascade = init_cascade("haarcascade_frontalface_alt.xml",ok);
    if( !ok ) { 
        return false; 
    }   

    capture = init_video(ok);
    return ok;
}


int getFaceCoord(int* x, int* y ) {

    cv::Mat frame;

    //-- 2. Read the video stream
    while ( capture->read(frame) ) {
        if( frame.empty() )
        {
            printf(" --(!) No captured frame -- Break!");
            break;
        }

        //-- 3. Apply the classifier to the frame
        cv::Point pt = detectAndDisplay( frame , face_cascade);
        *x = pt.x;
        *y = pt.y;
        break;
    }

    capture->release();
    delete face_cascade;
    delete capture;
    
    return 1;
}


cv::Point detectAndDisplay( cv::Mat frame , cv::CascadeClassifier* face_cascade) //usa frame e face_cascade
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
     
    std::vector<cv::Rect>::const_iterator r = faces.begin();

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
