#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;		//使用OpenCV的命名空间cv
using namespace std;	//使用标准模板库的命名空间std

int main()
{
	//原图,去掉彩色，变为灰度图
	Mat src = imread("/root/Desktop/Computer_Vision/image/capsulate.bmp", IMREAD_GRAYSCALE);
	imshow("src", src);

	Mat hist;	//直方图
	int dims = 1;
	float hranges[] = { 0, 255 };
	const float *ranges[] = { hranges };   // 这里需要为const类型
	int size = 256;
	int channels = 0;
	// 计算图像的直方图
	calcHist(&src, 1, &channels, Mat(), hist, dims, &size, ranges);

	// 获取最大值和最小值
	double minVal = 0;
	double maxVal = 0;
	minMaxLoc(hist, &minVal, &maxVal, 0, 0);

	//显示直方图的图像
	int scale = 1;
	Mat imageShow(size * scale, size, CV_8U, Scalar(0));
	int hpt = saturate_cast<int>(0.9 * size);
	for (int i = 0; i < 256; i++)
	{
		float value = hist.at<float>(i);           // 注意hist中是float类型
		int realValue = saturate_cast<int>(value * hpt / maxVal);
		rectangle(imageShow, Point(i*scale, size - 1), Point((i + 1)*scale - 1, size - realValue), Scalar(255));
	}
	imshow("Hist", imageShow);
	//cv::imwrite("hist.jpg", imageShow);
	waitKey();

	//图像分割，把灰度值>thresh1,且<thresh2的保留原灰度值，其他变为0
	uchar thresh1 = 30;
	uchar thresh2 = 130;
	Mat dst;
	cv::threshold(src, dst, thresh1, 255, THRESH_TOZERO);
	cv::threshold(dst, dst, thresh2, 255, THRESH_TOZERO_INV);
	imshow("dst", dst);
	waitKey();

    return 0;
}

