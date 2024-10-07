#include <iostream>
#include <lccv.hpp>
#include <opencv2/opencv.hpp>
#include "syscam.h"

using namespace std;
using namespace cv;

syscam::syscam(){
	pi.options->video_width = 1024;
	pi.options->video_height = 768;
	pi.options->framerate = 2;
	pi.options->verbose = false;
	pi.startVideo();
	type = PI_CAMERA;
}

syscam::syscam(unsigned char n){
	if(n == NO_CAMERA){
		type = NO_CAMERA;
	}else{
		usb = VideoCapture(n);
		if(!usb.isOpened())return;
		usb.set(CAP_PROP_FRAME_WIDTH,1920);
		usb.set(CAP_PROP_FRAME_HEIGHT,1080);
		type = USB_CAMERA;
	}
}

syscam::~syscam(){
	switch(type){
		case(USB_CAMERA):{
			usb.release();
			break;
		}
		case(PI_CAMERA):{
			pi.stopVideo();
			break;
		}
	}
}

bool syscam::get_frame(Mat & frame){
	switch(type){
		case(USB_CAMERA):{
                	usb >> frame;
                	if(frame.empty())return false;
			break;
		}
		case(PI_CAMERA):{
   			if(!pi.getVideoFrame(frame,1000))return false;
			break;
		}
		default:{
        		frame = Mat(768,1024,CV_8UC3, Scalar(100,0,0));
			Point p1(random()%100,random()%100);
    			Point p2(random()%1024,random()%1024);
    			int thickness = -1;
			rectangle(frame, p1, p2,Scalar(random()%255,random()%255,random()%255),thickness,LINE_8);
		 	putText(frame,"DEVICE CAMERA",Point(380,320),FONT_HERSHEY_COMPLEX,1.48,Scalar(255,255,255),1);
		}
	}
	return true;
}
