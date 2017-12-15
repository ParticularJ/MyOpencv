// GeometricTrans.cpp: 定义控制台应用程序的入口点。

#include <iostream>
#include <opencv2/opencv.hpp>


using namespace cv;		//使用OpenCV的命名空间cv
using namespace std;	//使用标准模板库的命名空间std

int main()
{
	Mat src = imread("/root/Desktop/Computer_Vision/image/lena24.bmp");	//原图
	Mat dst;	//新图

	//旋转变换
	double angle = -30;	//旋转角度
	cv::Point2f center(src.cols /2, src.rows /2);	//旋转中心

	//根据旋转中心和旋转角度，得到旋转的变换矩阵
	cv::Mat rotMatrix = cv::getRotationMatrix2D(center, angle, 1);
	cv::warpAffine(src, dst, rotMatrix, src.size());	//仿射变换
	imshow("src", src);	//显示原图
	imshow("dst", dst);	//显示新图
	waitKey();		//等待

	//平移变换，变换矩阵是2行3列，tx表示水平平移量，ty表示垂直平移量
	//1 0 tx
	//0 1 ty
	Mat transMatrix = Mat::zeros(2, 3, CV_32FC1);
	transMatrix.at<float>(0, 0) = 1;
	transMatrix.at<float>(1, 1) = 1;
	transMatrix.at<float>(0, 2) = 50; //水平平移量
	transMatrix.at<float>(1, 2) = 50; //垂直平移量
	warpAffine(src, dst, transMatrix, src.size());	//仿射变换
	imshow("dst", dst);	//显示新图
	waitKey();		//等待

	//放缩变换，变换矩阵是2行3列，sx表示水平方向放缩系数，sy垂直方向放缩系数
	//sx 0 0
	//0 sy 0
	Mat scaleMatrix = Mat::zeros(2, 3, CV_32FC1);
	scaleMatrix.at<float>(0, 0) = 0.5;	//水平方向放缩系数
	scaleMatrix.at<float>(1, 1) = 0.5;	//垂直方向放缩系数
	warpAffine(src, dst, scaleMatrix, src.size());	//仿射变换
	imshow("dst", dst);	//显示新图
	waitKey();		//等待

    return 0;
}

