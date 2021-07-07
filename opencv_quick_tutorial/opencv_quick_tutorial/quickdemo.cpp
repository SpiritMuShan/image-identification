#include<quickopencv.h>

//ͼ���д��ת��Ϊ�Ҷ�ͼ���HSVͼ��
void QuickDemo::colorSpace_Demo(Mat &image) {
	Mat gray, hsv;
	cvtColor(image, hsv, COLOR_BGR2HSV);//H:0-180,S(����ͼ�񱥺Ͷ�),V(����ͼ������)
	cvtColor(image, gray, COLOR_BGR2GRAY);
	imshow("HSV", hsv);
	imshow("GRAY",gray);
	imwrite("F:/images/hsv.png", hsv);
	imwrite("F:/images/gray.png", gray);
}

//�����հ�ͼ�񲢶��丳ֵ��ͼ�񿽱�
void QuickDemo::mat_creation_demo(Mat &image) {
	//Mat m1, m2;
	//m1 = image.clone();//��¡ͼ�������µľ��󣬾����head��һ���ģ������ж������У�ͨ�����ȣ����Ƶ���datablock����������ݣ�
	//image.copyTo(m2);//����ͼ�����¡Ч��һ���������µľ��󣬾����head��һ���ģ������ж������У�ͨ�����ȣ����Ƶ���datablock

	//�����հ�ͼ��
	Mat m3 = Mat::zeros(Size(8, 8), CV_8UC3);//CV_8UC1�У�1����ͨ����Ϊ1��Mat::zeros()���������������ֱ�Ϊͼ��ĳߴ��Լ�ͼ�����ͣ�zeros��ʾ������ֵȫ��0������ones������ȫ��1�ľ��󣬵����޵�ͨ������ͨ��ֻ�е�һ��ͨ����1������ͨ��Ϊ0��
	m3 = Scalar(0, 0, 255);//�������ľ���ֵ
	std::cout << "width:" << m3.cols << " height:" << m3.rows << " channels:" << m3.channels() << std::endl;//�����ȣ��߶ȣ�ͨ����
	//std::cout << m3 << std::endl;//��������Ŀհ׾���

	imshow("tuxiang", m3);//�����������ͼ��

	Mat m4 = m3;//���ָ�ֵ����ǳ������ֻ����m4ָ��m3����û�������µľ���m4�ı�m3���ű䡣ǰ���ֶ��������µľ��󣬾����head��һ���ģ������ж������У�ͨ�����ȣ����Ƶ���datablock
	m4 = Scalar(0, 255, 0);
	imshow("tuxiang2", m3);
}

//ͼ��������ʼ��޸����ص�����
void QuickDemo::pixel_visit_demo(Mat &image) {
	int w = image.cols;
	int h = image.rows;
	int dims = image.channels();
	
	/*for (int row = 0; row < h; row++) {
		for (int col = 0; col < w; col++) {
			if (dims == 1) {//�Ҷ�ͼ��
				int pv = image.at<uchar>(row, col);
				image.at<uchar>(row, col) = 255 - pv;
			}
			if (dims == 3) {//��ɫͼ��
				Vec3b bgr = image.at<Vec3b>(row, col);//���԰��������һ�����飬���ݾʹ洢���������
				image.at<Vec3b>(row, col)[0] = 255 - bgr[0];
				image.at<Vec3b>(row, col)[1] = 255 - bgr[1];
				image.at<Vec3b>(row, col)[2] = 255 - bgr[2];
		}
		}
	}*/

	//ָ�뷽��
	for (int row = 0; row < h; row++) {
		uchar*current_row = image.ptr<uchar>(row);
		for (int col = 0; col < w; col++) {
			if (dims == 1) {//�Ҷ�ͼ��
				int pv = *current_row;
				*current_row++ = 255 - pv;
			}
			if (dims == 3) {//��ɫͼ��
				*current_row++ = 255 - *current_row;
				*current_row++ = 255 - *current_row;
				*current_row++ = 255 - *current_row;
			}
		}
	}

	imshow("xiangsuduxiexianshi", image);
}

//ͼ��Ӽ��˳�����
void QuickDemo::operators_demo(Mat &image) {
	Mat dst = Mat::zeros(image.size(), image.type());;

	//dst = image + Scalar(50, 50, 50);//����һ����ɫ��ȥ���൱�ڱ����ˣ���ͬ��
	//dst = image / Scalar(2, 2, 2);//��2�����䰵���˿��ܻᱨ����ר�ŵĺ���

	Mat m = Mat::zeros(image.size(), image.type());
	m = Scalar(2, 2, 2);

	//�ӷ�����һ��ʵ�ַ�ʽ
	/*int w = image.cols;
	int h = image.rows;
	int dims = image.channels();
	for (int row = 0; row < h; row++) {
		for (int col = 0; col < w; col++) {
			Vec3b p1 = image.at<Vec3b>(row, col);//���԰��������һ�����飬���ݾʹ洢���������
			Vec3b p2 = m.at<Vec3b>(row, col);
			dst.at<Vec3b>(row, col)[0] = saturate_cast<uchar>(p1[0] + p2[0]);//saturate_cast<uchar>()�������Զ����������ݽ����ж�����С��0�������ݱ�Ϊ0��������255�������ݱ�Ϊ255.
			dst.at<Vec3b>(row, col)[1] = saturate_cast<uchar>(p1[1] + p2[1]);
			dst.at<Vec3b>(row, col)[2] = saturate_cast<uchar>(p1[2] + p2[2]);
		}
	}
	*/
	add(image, m, dst);//add�������������ֱ�Ϊԭͼ�񡢼ӵ�ͼ�񡢽��
	//subtract(image, m, dst);//��
	//multiply(image, m, dst);//��
	//divide(image, m, dst);//��
	imshow("jiafacaozhuo", dst);
}


//���ȵ���
/*
Mat src, dst, m;
int lightness = 50;

static void on_track(int, void*) {
	m = Scalar(lightness, lightness, lightness);
	add(src, m, dst);//���õ�����add�����ǰ���substract��
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


//���ȺͶԱȶȵ���
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
	createTrackbar("Value bar:", "liangduduibidutiaozheng", &lightness, max_value, on_lightness, (void*)(&image));//�������ֲ�����ͼƬ���ƣ��������ƣ���ʼֵ�����ֵ�������Ϸ���������֪����
	createTrackbar("Contrast bar:", "liangduduibidutiaozheng", &contrast_value,  200, on_contrast, (void*)(&image));
	on_lightness(50, &image);
}

//�����������
void	QuickDemo::key_demo(Mat &image) {
	Mat dst= Mat::zeros(image.size(),image.type());
	while (true) {
		int c = waitKey(100);
		if (c == 27) {//�˳�
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

//ͼ��ͬ����л�
void QuickDemo::color_style_demo(Mat &image){
	int colormap[]={//���⣬19��
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
		int c = waitKey(1000);//ÿ����Ƭͣ��ʱ��
		if (c == 27) {//�˳�
			break;
		}
		applyColorMap(image, dst, colormap[index % 19]);//Ӧ�ø��ַ��
		index++;
		imshow("yansefengge", dst);
	}
}

//���δ���������λ����������
void QuickDemo::bitwise_demo(Mat &image) {
	Mat m1 = Mat::zeros(Size(256, 256), CV_8UC3);
	Mat m2 = Mat::zeros(Size(256, 256), CV_8UC3);
	rectangle(m1, Rect(100, 100, 80, 80), Scalar(255, 255, 0), -1, LINE_8, 0);//�������Σ�����m1���������Ϸ���ʼ���꣬����������ɫ��������ʾ���α߿��ϸ��������ʾ�����Σ���ݴ�����֪����
	rectangle(m2, Rect(150, 150, 80, 80), Scalar(0, 255, 255), -1, LINE_8, 0);
	imshow("m1", m1);
	imshow("m2", m2);
	Mat dst,m3;
	//bitwise_and(m1, m2, dst);//��
	//bitwise_or(m1, m2, dst);//��
	//bitwise_not(image,dst);//��,ֻ��һ������
	//m3 = ~image;//���Ҳ����ʵ��ͼ��ķǲ���
	bitwise_xor(m1, m2, dst);//���
	imshow("xiangsuweicaozhuo", dst);
}

