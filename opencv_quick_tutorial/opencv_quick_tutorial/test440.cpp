#include<opencv2/opencv.hpp>
#include<quickopencv.h>
#include<iostream>

using namespace cv;
using namespace std;

int main(int argc, char**argv) {
	Mat src = imread("F:/images/3.2.png");
	if (src.empty()) {
		printf("could not load image...\n");
		return -1;
	}
	namedWindow("shuruchuangkou", WINDOW_FREERATIO);
		imshow("shuruchuangkou", src);

	QuickDemo qd;
	//qd.colorSpace_Demo(src);
	//qd.mat_creation_demo(src);
	//qd.pixel_visit_demo(src);
	//qd.operators_demo(src);
	qd.tracking_bar_demo(src);
	//qd.key_demo(src);
	//qd.color_style_demo(src);
	//qd.bitwise_demo(src);

	waitKey(0);
	destroyAllWindows();
	return 0;
}