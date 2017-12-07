#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;		//使用OpenCV的命名空间cv
using namespace std;	//使用标准模板库的命名空间std

int main()
{
	Mat img = imread("/root/Desktop/Computer_Vision/image/capsulate.bmp", CV_LOAD_IMAGE_UNCHANGED);
	if (img.empty())
	{
		cerr << "Can not open the file,please check the directory.\n";
	}
	imshow("title", img);
	waitKey(); //等待，按任意键结束显示图像
    return 0;
}

