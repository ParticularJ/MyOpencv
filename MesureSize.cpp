
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
	Mat binary;
	cv::threshold(src, binary, thresh1, 255, THRESH_TOZERO);
	cv::threshold(binary, binary, thresh2, 255, THRESH_TOZERO_INV);
	cv::threshold(binary, binary, thresh1, 255, THRESH_BINARY);
	imshow("binary", binary);
	waitKey();

	//形态学操作，去除细边缘
	int coreSize = 5;	//核的尺寸
	int iterNum = 2;	//迭代次数
	//内核形状可以取方形MORPH_RECT,十字形MORPH_CROSS,椭圆形MORPH_ELLIPSE
	Mat core = getStructuringElement(MORPH_RECT, Size(coreSize, coreSize));

	Mat imgClosed, imgOpened;
	//开操作MORPH_OPEN，闭操作MORPH_CLOSE，形态学梯度MORPH_GRENIENT
	//锚点位置默认值Point(-1,-1),取形状的中心
	//morphologyEx(binary, imgClosed, MORPH_CLOSE, core, Point(-1, -1), 1);
	morphologyEx(binary, imgOpened, MORPH_OPEN, core, Point(-1, -1), iterNum);
	imshow("imgOpened", imgOpened);
	waitKey();

	//提取轮廓线
	vector<vector<Point> > contours;
	cv::findContours(imgOpened, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

	//画轮廓线
	Mat contoursImage(src.rows, src.cols, CV_8U, Scalar(0));
	for (int i = 0; i<contours.size(); i++)
	{
		//忽略很短的轮廓线
		if (contours[i].size() > 200)
		{
			drawContours(contoursImage, contours, i, Scalar(200), 3);

			//测量胶囊的长宽
			RotatedRect box = minAreaRect(contours[i]);

			cout <<"width="<< box.size.width <<",height="<< box.size.height << endl;

			Point2f vec[4];
			box.points(vec);
			for (int i = 0; i < 4; i++)
				line(contoursImage, vec[i], vec[(i + 1) % 4], Scalar(100), 2, LINE_AA);
		}
	}
	imshow("contoursImage", contoursImage);
	waitKey();

	return 0;
}

