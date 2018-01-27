#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;		//使用OpenCV的命名空间cv
using namespace std;	//使用标准模板库的命名空间std


//int main()
//{
//	//初始化视频捕捉器
//	VideoCapture cap;
//	// 打开默认摄像头，如果有摄像头，请启用下面这段代码
//	//cap.open(0);
//	//打开视频文件，如果使用摄像头，请注释掉下面这一句
//	cap.open("/home/ck/Videos/3.mp4");
//
//	// 检查是否开启了摄像头或者视频文件是否打开成功a
//	if (!cap.isOpened()) {
//		cerr << "ERROR!Cannot open video.\n";
//		return -1;
//	}
//
//	cout << "Start play" << endl
//		<< "Stop with press any key." << endl;
//
//
//    double rate=cap.get(CV_CAP_PROP_FPS); // 获取
//    long nFrame=static_cast<long>(cap.get(CV_CAP_PROP_FRAME_COUNT)); // 获取总帧数
//    cout<<rate<<" "<<nFrame<<endl;
//    Mat frame;
//	char filename[99999];
//	int i=531;
//	int j=0;
//
//	while(true)
//	{
//		// 从摄像头或者视频文件中读取一帧视频图像，并保存在frame中
//		cap.read(frame);
//		sprintf(filename,"pic//%d.jpg",i);
//		// 检查读取是否成功
//		if (frame.empty()) {
//			cerr << "ERROR,it's empty!\n";
//			break;
//		}
//		//在窗口Live中显示当前帧的内容
//       // imshow("Live", frame);
//		if((j%125)==0){
//            imwrite(filename,frame);
//            ++i;
//		}
//		//当前帧的画面停留50毫秒
//		if(waitKey(1)>=0)
//            break;
//          ++j;
//	}
//	return 0;
//}




 int main()
{
    //设置视频读入于输出路径
    string sourceVideoPath = "/home/ck/Videos/3.mp4";
    string outputVideoPath = "/home/ck/Videos/3test.avi";
    //视频输入
    VideoCapture inputVideo(sourceVideoPath);
    //-------------【2】判断视频读取是否正确-------------
    if (!inputVideo.isOpened())
    {
        cout << "打开视频文件失败，请重新输入正确路径！" << endl;
        system("pause");
        return -1;
    }
    VideoWriter outputVideo;
    //获取视频分辨率
    Size videoResolution = Size((int)inputVideo.get(CV_CAP_PROP_FRAME_WIDTH), (int)inputVideo.get(CV_CAP_PROP_FRAME_HEIGHT));
    //获取视频总帧数
    cout << "视频总帧数: " << inputVideo.get(CV_CAP_PROP_FRAME_COUNT) << endl;
    //获取视频帧率
    cout << "视频帧率: " << inputVideo.get(CV_CAP_PROP_FPS) << endl;
    //获取视频图像宽/高
    cout << "频图像宽/高: " << videoResolution.width << " " << videoResolution.height << endl;

    //open方法相关设置
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
    int count = 0;  //计数，当前帧号
    //vector RGB分量
 //   vector<Mat> rgb;
 //  Mat resultImag;//定义一个Mat变量，用于存储每一帧的图像
    while (true)
    {
        inputVideo >> frameImg;
        //视频帧结束判断
        if (!frameImg.empty())
        {
            count++;
            imshow("读入视频", frameImg);
            //分离出三通道rgb
//            split(frameImg, rgb);
//            for (int i = 0; i < 3; i++)
//            {
//                if (i != 0)
//                {
//                    //提取B通道分离
//                    rgb[i] = Mat::zeros(videoResolution, rgb[0].type());
//                }
//                //通道合并
//                merge(rgb, resultImag);
//            }
//            imshow("写入视频窗口", resultImag);
            outputVideo << frameImg; //把这一帧画面写入到outputVideo中
        }
        else
        {
            break;
        }
        //按下键盘上Q或q键退出
        if (char(waitKey(40)) == 'q' || char(waitKey(40)) == 'Q') //每帧画面存在40ms，即1秒25帧
        {
            break;
        }
    }
    cout << "总共写入的帧数: " << count << endl;
    system("pause");
    return 0;
}
