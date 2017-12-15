
#include <iostream>
#include <opencv2/opencv.hpp>


using namespace cv;		//使用OpenCV的命名空间cv
using namespace std;	//使用标准模板库的命名空间std

int main()
{
	//原图,去掉彩色，变为灰度图
	Mat src = imread("/root/Desktop/Computer_Vision/image/capsulate.bmp", IMREAD_GRAYSCALE);
	imshow("src", src);

	//图像分割，把灰度值>thresh1,且<thresh2的保留原灰度值，其他变为0
	uchar thresh1 = 30;
	uchar thresh2 = 130;
	Mat dst;
	cv::threshold(src, dst, thresh1, 255, THRESH_TOZERO);
	cv::threshold(dst, dst, thresh2, 255, THRESH_TOZERO_INV);
	imshow("dst", dst);
	waitKey();

	//形态学操作，去除细边缘
	int coreSize = 5;	//核的尺寸
	int iterNum = 2;	//迭代次数
	//内核形状可以取方形MORPH_RECT,十字形MORPH_CROSS,椭圆形MORPH_ELLIPSE
	Mat core = getStructuringElement(MORPH_RECT, Size(coreSize, coreSize));

	Mat imgOpened;
	//开操作MORPH_OPEN，闭操作MORPH_CLOSE，形态学梯度MORPH_GRENIENT
	//锚点位置默认值Point(-1,-1),取形状的中心
	morphologyEx(dst, imgOpened, MORPH_CLOSE, core, Point(-1, -1), iterNum);
	morphologyEx(dst, imgOpened, MORPH_OPEN, core, Point(-1, -1), iterNum);
	imshow("imgOpened", imgOpened);
	waitKey();

	return 0;
}

