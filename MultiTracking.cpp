#include<tracking.hpp>
#include<highgui.hpp>
#include<video.hpp>
#include<opencv2/core/utility.hpp>
#include<vector>

using namespace cv;
using namespace std;

int main() {
    Mat frame;
    VideoCapture cap("/home/ck/Documents/tmp/Computer_Vision/addition/123.avi");//输入待处理的视频
    cap >> frame;
    vector<Rect> rois;
    selectROIs("rois", frame, rois, false);
    if (rois.size()<1)
        return 0;
    MultiTracker trackers;
    vector<Rect2d> obj;
    vector<Ptr<Tracker>> algorithms;
    for (auto i = 0; i < static_cast<int>(rois.size()); i++) {
        obj.push_back(rois[i]);
        algorithms.push_back(TrackerKCF::create());
    }
    trackers.add(algorithms, frame, obj);
    while (cap.read(frame)) {
        bool ok = trackers.update(frame);
        if (ok) {
            for (auto j = 0; j < static_cast<int>(trackers.getObjects().size()); j++) {
                rectangle(frame, trackers.getObjects()[j], Scalar(255, 0, 0), 2, 1);
            }
            imshow("tracker", frame);
            waitKey(10);
        }
        if (waitKey(1) == 27)break;
    }
    return 0;
}
