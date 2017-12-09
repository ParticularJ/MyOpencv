// FlipImage.cpp: 定义控制台应用程序的入口点。
#include <iostream>
#include <opencv2/opencv.hpp>



using namespace cv;		//使用OpenCV的命名空间cv
using namespace std;	//使用标准模板库的命名空间std

int main()
{
	Mat src = imread("/root/Desktop/Computer_Vision/image/lena24.bmp");	//原图
	Mat dst;	//新图
	//翻转方向：1：水平翻转；0：垂直翻转； - 1：水平垂直翻转
	flip(src, dst, 1);
	imshow("src", src);	//显示原图
	imshow("dst", dst);	//显示新图
	waitKey();		//等待

    return 0;
}

