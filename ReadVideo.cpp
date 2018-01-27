#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;		//ʹ��OpenCV�������ռ�cv
using namespace std;	//ʹ�ñ�׼ģ���������ռ�std


//int main()
//{
//	//��ʼ����Ƶ��׽��
//	VideoCapture cap;
//	// ��Ĭ������ͷ�����������ͷ��������������δ���
//	//cap.open(0);
//	//����Ƶ�ļ������ʹ������ͷ����ע�͵�������һ��
//	cap.open("/home/ck/Videos/3.mp4");
//
//	// ����Ƿ���������ͷ������Ƶ�ļ��Ƿ�򿪳ɹ�a
//	if (!cap.isOpened()) {
//		cerr << "ERROR!Cannot open video.\n";
//		return -1;
//	}
//
//	cout << "Start play" << endl
//		<< "Stop with press any key." << endl;
//
//
//    double rate=cap.get(CV_CAP_PROP_FPS); // ��ȡ
//    long nFrame=static_cast<long>(cap.get(CV_CAP_PROP_FRAME_COUNT)); // ��ȡ��֡��
//    cout<<rate<<" "<<nFrame<<endl;
//    Mat frame;
//	char filename[99999];
//	int i=531;
//	int j=0;
//
//	while(true)
//	{
//		// ������ͷ������Ƶ�ļ��ж�ȡһ֡��Ƶͼ�񣬲�������frame��
//		cap.read(frame);
//		sprintf(filename,"pic//%d.jpg",i);
//		// ����ȡ�Ƿ�ɹ�
//		if (frame.empty()) {
//			cerr << "ERROR,it's empty!\n";
//			break;
//		}
//		//�ڴ���Live����ʾ��ǰ֡������
//       // imshow("Live", frame);
//		if((j%125)==0){
//            imwrite(filename,frame);
//            ++i;
//		}
//		//��ǰ֡�Ļ���ͣ��50����
//		if(waitKey(1)>=0)
//            break;
//          ++j;
//	}
//	return 0;
//}




 int main()
{
    //������Ƶ���������·��
    string sourceVideoPath = "/home/ck/Videos/3.mp4";
    string outputVideoPath = "/home/ck/Videos/3test.avi";
    //��Ƶ����
    VideoCapture inputVideo(sourceVideoPath);
    //-------------��2���ж���Ƶ��ȡ�Ƿ���ȷ-------------
    if (!inputVideo.isOpened())
    {
        cout << "����Ƶ�ļ�ʧ�ܣ�������������ȷ·����" << endl;
        system("pause");
        return -1;
    }
    VideoWriter outputVideo;
    //��ȡ��Ƶ�ֱ���
    Size videoResolution = Size((int)inputVideo.get(CV_CAP_PROP_FRAME_WIDTH), (int)inputVideo.get(CV_CAP_PROP_FRAME_HEIGHT));
    //��ȡ��Ƶ��֡��
    cout << "��Ƶ��֡��: " << inputVideo.get(CV_CAP_PROP_FRAME_COUNT) << endl;
    //��ȡ��Ƶ֡��
    cout << "��Ƶ֡��: " << inputVideo.get(CV_CAP_PROP_FPS) << endl;
    //��ȡ��Ƶͼ���/��
    cout << "Ƶͼ���/��: " << videoResolution.width << " " << videoResolution.height << endl;

    //open�����������
    int codec = CV_FOURCC('M', 'J', 'P', 'G');  // select desired codec (must be available at runtime)
    double fps = 25.0;                          // framerate of the created video stream
  //  bool isColor = (videoResolution.type() == CV_8UC3);
    outputVideo.open(outputVideoPath, codec, fps, videoResolution, 1);
    // check if we succeeded
    if (!outputVideo.isOpened()) {
        cerr << "Could not open the output video file for write\n";
        return -1;
    }

    Mat frameImg;
    int count = 0;  //��������ǰ֡��
    //vector RGB����
 //   vector<Mat> rgb;
 //  Mat resultImag;//����һ��Mat���������ڴ洢ÿһ֡��ͼ��
    while (true)
    {
        inputVideo >> frameImg;
        //��Ƶ֡�����ж�
        if (!frameImg.empty())
        {
            count++;
            imshow("������Ƶ", frameImg);
            //�������ͨ��rgb
//            split(frameImg, rgb);
//            for (int i = 0; i < 3; i++)
//            {
//                if (i != 0)
//                {
//                    //��ȡBͨ������
//                    rgb[i] = Mat::zeros(videoResolution, rgb[0].type());
//                }
//                //ͨ���ϲ�
//                merge(rgb, resultImag);
//            }
//            imshow("д����Ƶ����", resultImag);
            outputVideo << frameImg; //����һ֡����д�뵽outputVideo��
        }
        else
        {
            break;
        }
        //���¼�����Q��q���˳�
        if (char(waitKey(40)) == 'q' || char(waitKey(40)) == 'Q') //ÿ֡�������40ms����1��25֡
        {
            break;
        }
    }
    cout << "�ܹ�д���֡��: " << count << endl;
    system("pause");
    return 0;
}
