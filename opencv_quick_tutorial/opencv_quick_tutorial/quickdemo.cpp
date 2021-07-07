#include<quickopencv.h>

//图像读写，转变为灰度图像或HSV图像
void QuickDemo::colorSpace_Demo(Mat &image) {
	Mat gray, hsv;
	cvtColor(image, hsv, COLOR_BGR2HSV);//H:0-180,S(决定图像饱和度),V(决定图像亮度)
	cvtColor(image, gray, COLOR_BGR2GRAY);
	imshow("HSV", hsv);
	imshow("GRAY",gray);
	imwrite("F:/images/hsv.png", hsv);
	imwrite("F:/images/gray.png", gray);
}

//创建空白图像并对其赋值，图像拷贝
void QuickDemo::mat_creation_demo(Mat &image) {
	//Mat m1, m2;
	//m1 = image.clone();//克隆图像，生成新的矩阵，矩阵的head是一样的，包括有多少行列，通道数等，复制的是datablock（里面的数据）
	//image.copyTo(m2);//拷贝图像，与克隆效果一样，生成新的矩阵，矩阵的head是一样的，包括有多少行列，通道数等，复制的是datablock

	//创建空白图像
	Mat m3 = Mat::zeros(Size(8, 8), CV_8UC3);//CV_8UC1中，1代表通道数为1。Mat::zeros()函数中两个参数分别为图像的尺寸以及图像类型，zeros表示矩阵数值全是0，换成ones可生成全是1的矩阵，但仅限单通道，多通道只有第一个通道是1，后面通道为0。
	m3 = Scalar(0, 0, 255);//给创建的矩阵赋值
	std::cout << "width:" << m3.cols << " height:" << m3.rows << " channels:" << m3.channels() << std::endl;//输出宽度，高度，通道数
	//std::cout << m3 << std::endl;//输出创建的空白矩阵

	imshow("tuxiang", m3);//输出矩阵代表的图像

	Mat m4 = m3;//这种赋值属于浅拷贝，只是让m4指向m3，并没有生成新的矩阵，m4改变m3跟着变。前两种都是生成新的矩阵，矩阵的head是一样的，包括有多少行列，通道数等，复制的是datablock
	m4 = Scalar(0, 255, 0);
	imshow("tuxiang2", m3);
}

//图像遍历访问及修改像素点数据
void QuickDemo::pixel_visit_demo(Mat &image) {
	int w = image.cols;
	int h = image.rows;
	int dims = image.channels();
	
	/*for (int row = 0; row < h; row++) {
		for (int col = 0; col < w; col++) {
			if (dims == 1) {//灰度图像
				int pv = image.at<uchar>(row, col);
				image.at<uchar>(row, col) = 255 - pv;
			}
			if (dims == 3) {//彩色图像
				Vec3b bgr = image.at<Vec3b>(row, col);//可以把这个看作一个数组，数据就存储在这个里面
				image.at<Vec3b>(row, col)[0] = 255 - bgr[0];
				image.at<Vec3b>(row, col)[1] = 255 - bgr[1];
				image.at<Vec3b>(row, col)[2] = 255 - bgr[2];
		}
		}
	}*/

	//指针方法
	for (int row = 0; row < h; row++) {
		uchar*current_row = image.ptr<uchar>(row);
		for (int col = 0; col < w; col++) {
			if (dims == 1) {//灰度图像
				int pv = *current_row;
				*current_row++ = 255 - pv;
			}
			if (dims == 3) {//彩色图像
				*current_row++ = 255 - *current_row;
				*current_row++ = 255 - *current_row;
				*current_row++ = 255 - *current_row;
			}
		}
	}

	imshow("xiangsuduxiexianshi", image);
}

//图像加减乘除操作
void QuickDemo::operators_demo(Mat &image) {
	Mat dst = Mat::zeros(image.size(), image.type());;

	//dst = image + Scalar(50, 50, 50);//加了一个白色上去，相当于变亮了，减同理
	//dst = image / Scalar(2, 2, 2);//除2倍，变暗；乘可能会报错，用专门的函数

	Mat m = Mat::zeros(image.size(), image.type());
	m = Scalar(2, 2, 2);

	//加法的另一种实现方式
	/*int w = image.cols;
	int h = image.rows;
	int dims = image.channels();
	for (int row = 0; row < h; row++) {
		for (int col = 0; col < w; col++) {
			Vec3b p1 = image.at<Vec3b>(row, col);//可以把这个看作一个数组，数据就存储在这个里面
			Vec3b p2 = m.at<Vec3b>(row, col);
			dst.at<Vec3b>(row, col)[0] = saturate_cast<uchar>(p1[0] + p2[0]);//saturate_cast<uchar>()函数可以对括号中数据进行判定，若小于0，则将数据变为0；若大于255，则将数据变为255.
			dst.at<Vec3b>(row, col)[1] = saturate_cast<uchar>(p1[1] + p2[1]);
			dst.at<Vec3b>(row, col)[2] = saturate_cast<uchar>(p1[2] + p2[2]);
		}
	}
	*/
	add(image, m, dst);//add函数三个参数分别为原图像、加的图像、结果
	//subtract(image, m, dst);//减
	//multiply(image, m, dst);//乘
	//divide(image, m, dst);//除
	imshow("jiafacaozhuo", dst);
}


//亮度调整
/*
Mat src, dst, m;
int lightness = 50;

static void on_track(int, void*) {
	m = Scalar(lightness, lightness, lightness);
	add(src, m, dst);//设置调亮（add）还是暗（substract）
	imshow("lightness control", dst);
}

void QuickDemo::track_bar_demo(Mat &image) {
	namedWindow("lightness control", WINDOW_AUTOSIZE);
	dst = Mat::zeros(image.size(), image.type());
	m = Mat::zeros(image.size(), image.type());
	src = image;
	int max_value = 100;
	createTrackbar("Value bar:","lightness control", &lightness, max_value, on_track);
	on_track(50, 0);
}
*/


//亮度和对比度调整
static void on_lightness(int b, void*userdata) {
	Mat image = *((Mat*)userdata);
	Mat dst = Mat::zeros(image.size(), image.type());
	Mat m = Mat::zeros(image.size(), image.type());
	addWeighted(image, 1.0, m, 0, b, dst);
	imshow("liangduduibidutiaozheng", dst);
}

static void on_contrast(int b, void*userdata) {
	Mat image = *((Mat*)userdata);
	Mat dst = Mat::zeros(image.size(), image.type());
	Mat m = Mat::zeros(image.size(), image.type());
	double contrast = b / 100.0;
	addWeighted(image, contrast, m, 0.0, 0, dst);
	imshow("liangduduibidutiaozheng", dst);
}

void QuickDemo::tracking_bar_demo(Mat &image) {
	namedWindow("liangduduibidutiaozheng", WINDOW_AUTOSIZE);
	int lightness = 50;
	int max_value = 100;
	int contrast_value = 100;
	createTrackbar("Value bar:", "liangduduibidutiaozheng", &lightness, max_value, on_lightness, (void*)(&image));//创建滚轮操作（图片名称；滚轮名称；初始值；最大值；引用上方函数；不知道）
	createTrackbar("Contrast bar:", "liangduduibidutiaozheng", &contrast_value,  200, on_contrast, (void*)(&image));
	on_lightness(50, &image);
}

//键盘输入操作
void	QuickDemo::key_demo(Mat &image) {
	Mat dst= Mat::zeros(image.size(),image.type());
	while (true) {
		int c = waitKey(100);
		if (c == 27) {//退出
			break;
		}
		if (c == 49) {//KEY #1
			std::cout << "you enter key #1" << std::endl;
			cvtColor(image, dst, COLOR_BGR2GRAY);
		}
		if (c == 50) {//KEY #2
			std::cout << "you enter key #2" << std::endl;
			cvtColor(image, dst, COLOR_BGR2HSV);
		}if (c == 51) {//KEY #3
			std::cout << "you enter key #3" << std::endl;
			dst = Scalar(50, 50, 50);
			add(image, dst, dst);
		}
		imshow("jianpanxiangying", dst);
	}
}

//图像不同风格切换
void QuickDemo::color_style_demo(Mat &image){
	int colormap[]={//风格库，19种
		COLORMAP_AUTUMN,
		COLORMAP_BONE,
		COLORMAP_JET,
		COLORMAP_WINTER,
		COLORMAP_RAINBOW,
		COLORMAP_OCEAN,
		COLORMAP_SUMMER,
		COLORMAP_SPRING,
		COLORMAP_COOL,
		COLORMAP_PINK,
		COLORMAP_HOT,
		COLORMAP_PARULA,
		COLORMAP_MAGMA,
		COLORMAP_INFERNO,
		COLORMAP_PLASMA,
		COLORMAP_VIRIDIS,
		COLORMAP_CIVIDIS,
		COLORMAP_TWILIGHT,
		COLORMAP_TWILIGHT_SHIFTED
	};

	Mat dst;
	int index = 0;
	while (true) {
		int c = waitKey(1000);//每张照片停顿时间
		if (c == 27) {//退出
			break;
		}
		applyColorMap(image, dst, colormap[index % 19]);//应用各种风格
		index++;
		imshow("yansefengge", dst);
	}
}

//矩形创建；像素位操作，与或非
void QuickDemo::bitwise_demo(Mat &image) {
	Mat m1 = Mat::zeros(Size(256, 256), CV_8UC3);
	Mat m2 = Mat::zeros(Size(256, 256), CV_8UC3);
	rectangle(m1, Rect(100, 100, 80, 80), Scalar(255, 255, 0), -1, LINE_8, 0);//创建矩形（放入m1；矩形左上方起始坐标，长宽；矩形颜色；正数表示矩形边框粗细，负数表示填充矩形；锯齿处理；不知道）
	rectangle(m2, Rect(150, 150, 80, 80), Scalar(0, 255, 255), -1, LINE_8, 0);
	imshow("m1", m1);
	imshow("m2", m2);
	Mat dst,m3;
	//bitwise_and(m1, m2, dst);//与
	//bitwise_or(m1, m2, dst);//或
	//bitwise_not(image,dst);//非,只有一个输入
	//m3 = ~image;//这个也可以实现图像的非操作
	bitwise_xor(m1, m2, dst);//亦或
	imshow("xiangsuweicaozhuo", dst);
}

