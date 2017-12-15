// GrayTrans.cpp: 定义控制台应用程序的入口点。

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;		//使用OpenCV的命名空间cv
using namespace std;	//使用标准模板库的命名空间std

int main()
{
	//原图,去掉彩色，变为灰度图
	Mat src = imread("/root/Desktop/Computer_Vision/image/lena24.bmp", IMREAD_GRAYSCALE);
	Mat dst;	//新图

	//图像求反
	dst = 255 - src;
	imshow("src", src);	//显示原图
	imshow("dst", dst);	//显示新图
	waitKey();		//等待

	//二值化,阈值为100，小于该值的灰度值变为0，否则变为255
	cv::threshold(src, dst, 100, 255, THRESH_BINARY);
	imshow("dst", dst);
	waitKey();

	//对数变换,对图像中低灰度细节进行增强 t = c log( 1 + s )
	//系数c确保新的灰度值取值范围在区间[0,255]
	float c = 255.0f / log(256);
	//使用查表法:先将每个灰度值映射后的结果计算出来，
	//在变换时，通过查表得到变换后的灰度值，可以加快速度
	//这里的表就是数组newGray
	uchar newGray[256];
	for (int i = 0; i < 256; i++)
		newGray[i] = uchar( c * log(1 + i) );
	for (int y = 0; y<src.rows; y++)
		for (int x = 0; x < src.cols; x++)
		{
			uchar oldGray = src.at<uchar>(y, x);
			dst.at<uchar>(y, x) = newGray[oldGray];
		}
	imshow("dst", dst);	//显示新图
	waitKey();		//等待

	return 0;
}

