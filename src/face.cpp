#include "face.h"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <stdio.h>


namespace {
    cv::CascadeClassifier* face_cascade;
    //cv::CascadeClassifier* eye_cascade;
    cv::VideoCapture* capture;
    
    
    
    cv::CascadeClassifier* init_face_cascade(const std::string& cascade, bool& ok ) {

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
/*
    cv::CascadeClassifier* init_eye_cascade(const std::string& cascade, bool& ok ) {
        
        eye_cascade = new cv::CascadeClassifier();

        if( ! eye_cascade->load( cascade ) ) {
            std::cerr << "--(!)Error loading eye cascade" << std::endl; 
            delete eye_cascade;
            ok = false;
        }
        else {
            ok = true;
        }

        return eye_cascade;
    }
*/
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

bool detectAndDisplay( cv::Point&, int& area );

bool isInitialized() {
    return face_cascade && /*eye_cascade &&*/ capture; 
}

bool init() {
    if ( isInitialized() )
        return true;
    bool ok;
    face_cascade = init_face_cascade("/home/michele/workspace/progettoOpencv/src/cascades/haarcascade_frontalface_default.xml",ok);
    
    if( !ok ) { 
        return false; 
    }   
/*
    //controllare se cascade e' giusto
    eye_cascade = init_eye_cascade("/home/michele/workspace/progettoOpencv/src/cascades/haarcascade_mcs_eyepair_big.xml",ok);
    if( !ok ) { 
        return false; 
    }   
*/
    capture = init_video(ok);
    return ok;
}



void finalize() {
    if ( isInitialized() ) { 
        cv::Mat frame;
        capture->release();
        do {
            capture->read(frame);
        } while( !frame.empty() );
        
        
        delete face_cascade;
        face_cascade = NULL;
        /*delete eye_cascade;
        eye_cascade = NULL;*/
        delete capture;
        capture = NULL;
    }
}

bool getFaceCoord(int* x, int* y, int* z ) {
    if ( !isInitialized() ) {
        std::cerr << "Pointers not initialized" << std::endl;
        return false;
    }

    cv::Point pt;
    int a = 0;

    if ( detectAndDisplay( pt, a ) ) {
        *x = pt.x;
        *y = pt.y;
        *z = a;
        return true;
    } 

    return false;
}


/******* private api *******/


bool detectAndDisplay( cv::Point& center, int& a ) {
    cv::Mat frame;
    assert(capture);
    capture->read(frame);
    if( frame.empty() ) {
        std::cerr << " --(!) No captured frame -- Break!" << std::endl;
        return false;
    }

    std::vector<cv::Rect> faces;
    std::vector<cv::Rect> eyes;

    double scale = 1;
    cv::Mat frame_gray;

    cv::cvtColor( frame, frame_gray, cv::COLOR_BGR2GRAY );
    cv::equalizeHist( frame_gray, frame_gray );

    //-- Detect faces
    assert(face_cascade);
    //assert(eye_cascade);

    //modificare -> usare face_cascade per rilevare grandezza volto (distanza da camera)
    face_cascade->detectMultiScale( frame_gray, faces, 1.1, 3,
                                    0|cv::CASCADE_SCALE_IMAGE, 
                                    cv::Size(90,110) );
    
    if (faces.size() == 1 ) { //PROVA UNO SOLO
            
            std::vector<cv::Rect>::const_iterator r = faces.begin();

            center.x = faces[0].x + faces[0].width*0.5;
            center.y = faces[0].y + faces[0].height*0.1;
            //center.x = cvRound((r->x + r->width* 0.5)*scale);
            //center.y = cvRound((r->y + r->height*0.5)*scale);
            
            //calcolo area volto
            //area = (r->x +r->width) * (r->y + r->height);
            //if ( r->x > 0 && r->y > 0 )
            //     area = r->width * r->height;
            //if ( faces[0].x > 0 && faces[0].height > 0 )
            //    area = faces[0].width * faces[0].height;           
            //else
            //    area = 0;
            a = faces[0].width;
        
    }
    else {
        return false;
    }
    
    return true;
}
