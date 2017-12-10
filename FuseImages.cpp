// FuseImages.cpp: 定义控制台应用程序的入口点。

#include <iostream>
#include <opencv2/opencv.hpp>


using namespace cv;		//使用OpenCV的命名空间cv
using namespace std;	//使用标准模板库的命名空间std

int main()
{
	//原图,彩色
	Mat src = imread("/root/Desktop/Computer_Vision/image/lena24.bmp", IMREAD_COLOR);
	//logo，彩色，比src小
	Mat logo = imread("/root/Desktop/Computer_Vision/image/simpleLogo.bmp", IMREAD_COLOR);
	imshow("src1", src);
	imshow("logo", logo);
	waitKey();

	Mat dst = src.clone();	//从原图克隆
	float alpha = 0.8f;		//融合系数
	for(int y = 0; y<logo.rows; y++)
		for (int x = 0; x < logo.cols; x++)
		{
			const Vec3b &srcVal = src.at<Vec3b>(y, x);
			const Vec3b &logoVal = logo.at<Vec3b>(y, x);
			Vec3b &dstVal = dst.at<Vec3b>(y, x);
			dstVal[0] = srcVal[0] * alpha + (logoVal[0]) * (1-alpha);
			dstVal[1] = srcVal[1] * alpha + (logoVal[1]) * (1 - alpha);
			dstVal[2] = srcVal[2] * alpha + (logoVal[2]) * (1 - alpha);
		}

	imshow("dst", dst);
	waitKey();

	return 0;
}

