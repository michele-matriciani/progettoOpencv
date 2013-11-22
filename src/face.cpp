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

bool detectAndDisplay( cv::Point& );

bool init() {
    bool ok;
    face_cascade = init_cascade("haarcascade_frontalface_alt.xml",ok);
    if( !ok ) { 
        return false; 
    }   

    capture = init_video(ok);
    return ok;
}

bool isInitialized() {
    return face_cascade && capture; 
}

void finalize() {
    if ( isInitialized() ) { 
        capture->release();
        delete face_cascade;
        face_cascade = NULL;
        delete capture;
        capture = NULL;
    }
}

bool getFaceCoord(int* x, int* y ) {
    if ( !isInitialized() ) {
        std::cerr << "Pointers not initialized" << std::endl;
        return false;
    }

    cv::Point pt;

    if ( detectAndDisplay( pt ) ) {
        *x = pt.x;
        *y = pt.y;
        return true;
    } 

    return false;
}


/******* private api *******/


bool detectAndDisplay( cv::Point& center ) {
    cv::Mat frame;
    assert(capture);
    capture->read(frame);
    if( frame.empty() ) {
        std::cerr << " --(!) No captured frame -- Break!" << std::endl;
        return false;
    }

    std::vector<cv::Rect> faces;
    
    double scale = 1;
    cv::Mat frame_gray;

    cv::cvtColor( frame, frame_gray, cv::COLOR_BGR2GRAY );
    cv::equalizeHist( frame_gray, frame_gray );

    //-- Detect faces
    assert(face_cascade);
    face_cascade->detectMultiScale( frame_gray, faces, 1.1, 1, 0|cv::CASCADE_SCALE_IMAGE, 
                                    cv::Size(frame.cols*0.4,frame.rows*0.4) );
    
    if (faces.size() == 1 ) { //PROVA UNO SOLO
    
        int i = 0;
         
        std::vector<cv::Rect>::const_iterator r = faces.begin();

        cv::Mat smallImgROI;
        std::vector<cv::Rect> nestedObjects;
         
        center.x = cvRound((r->x + r->width*0.5)*scale);
        center.y = cvRound((r->y + r->height*0.5)*scale);
    }

    return true;
}
