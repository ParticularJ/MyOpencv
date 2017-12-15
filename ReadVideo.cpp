#include <iostream>
#include <opencv2/opencv.hpp>


using namespace cv;		//使用OpenCV的命名空间cv
using namespace std;	//使用标准模板库的命名空间std


int main()
{
	//初始化视频捕捉器
	VideoCapture cap;
	// 打开默认摄像头，如果有摄像头，请启用下面这段代码
	//cap.open(0);
	//打开视频文件，如果使用摄像头，请注释掉下面这一句
	cap.open("/root/Desktop/Computer_Vision/image/crab.mp4");

	// 检查是否开启了摄像头或者视频文件是否打开成功
	if (!cap.isOpened()) {
		cerr << "ERROR!Cannot open video.\n";
		return -1;
	}

	cout << "Start play" << endl
		<< "Stop with press any key." << endl;

	Mat frame;
	while(true)
	{
		// 从摄像头或者视频文件中读取一帧视频图像，并保存在frame中
		cap.read(frame);
		// 检查读取是否成功
		if (frame.empty()) {
			cerr << "ERROR,it's empty!\n";
			break;
		}
		//在窗口Live中显示当前帧的内容
		imshow("Live", frame);
		//当前帧的画面停留50毫秒
		if (waitKey(50)>= 0)
			break;
	}

	return 0;
}
