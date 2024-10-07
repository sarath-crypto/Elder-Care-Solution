#include <iostream>
#include <lccv.hpp>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

enum type{PI_CAMERA = 1,USB_CAMERA = 0,NO_CAMERA = 255};

class syscam{
	private:
		lccv::PiCamera pi;
		VideoCapture usb;
		unsigned char type;
	public:
		syscam();
		syscam(unsigned char);
		~syscam();
		bool get_frame(Mat &);
};
