#include <iostream>
#include <opencv2/opencv.hpp>
#include <Poco/Net/StreamSocket.h>
#include <Poco/Net/SocketAddress.h>

using namespace cv;
using namespace Poco::Net;

int main() {
    VideoCapture cap(0);
    if (!cap.isOpened()) {
        std::cerr << "Error: Webcam not accessible\n";
        return -1;
    }

    SocketAddress sa("127.0.0.1", 12345);
    StreamSocket socket(sa);
    std::vector<uchar> buffer;

    while (true) {
        Mat frame;
        cap >> frame;
        if (frame.empty()) break;

        imencode(".jpg", frame, buffer);
        int size = buffer.size();
        socket.sendBytes(&size, sizeof(int));
        socket.sendBytes(reinterpret_cast<char*>(buffer.data()), size);

        if (waitKey(30) == 27) break; 
    }

    cap.release();
    return 0;
}