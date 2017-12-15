#include <iostream>
#include <opencv2/opencv.hpp>


using namespace cv;		//ʹ��OpenCV�������ռ�cv
using namespace std;	//ʹ�ñ�׼ģ���������ռ�std


int main()
{
	//��ʼ����Ƶ��׽��
	VideoCapture cap;
	// ��Ĭ������ͷ�����������ͷ��������������δ���
	//cap.open(0);
	//����Ƶ�ļ������ʹ������ͷ����ע�͵�������һ��
	cap.open("/root/Desktop/Computer_Vision/image/crab.mp4");

	// ����Ƿ���������ͷ������Ƶ�ļ��Ƿ�򿪳ɹ�
	if (!cap.isOpened()) {
		cerr << "ERROR!Cannot open video.\n";
		return -1;
	}

	cout << "Start play" << endl
		<< "Stop with press any key." << endl;

	Mat frame;
	while(true)
	{
		// ������ͷ������Ƶ�ļ��ж�ȡһ֡��Ƶͼ�񣬲�������frame��
		cap.read(frame);
		// ����ȡ�Ƿ�ɹ�
		if (frame.empty()) {
			cerr << "ERROR,it's empty!\n";
			break;
		}
		//�ڴ���Live����ʾ��ǰ֡������
		imshow("Live", frame);
		//��ǰ֡�Ļ���ͣ��50����
		if (waitKey(50)>= 0)
			break;
	}

	return 0;
}
