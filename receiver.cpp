#include <iostream>
#include <opencv2/opencv.hpp>
#include <Poco/Net/ServerSocket.h>
#include <Poco/Net/StreamSocket.h>
#include <Poco/Net/SocketStream.h>

using namespace cv;
using namespace Poco::Net;

int main() {
    ServerSocket server(12345);
    StreamSocket client = server.acceptConnection();

    while (true) {
        int size = 0;
        int received = client.receiveBytes(&size, sizeof(int));
        if (received <= 0) break;

        std::vector<uchar> buffer(size);
        received = client.receiveBytes(reinterpret_cast<char*>(buffer.data()), size);
        if (received <= 0) break;

        Mat frame = imdecode(buffer, IMREAD_COLOR);
        if (frame.empty()) continue;

        imshow("Receiver", frame);
        if (waitKey(30) == 27) break; // ESC to exit
    }

    return 0;
}