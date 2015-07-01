#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include<iostream>
using namespace cv;
using namespace std;

int main(int argc, char *argv[])
{
    Mat img = imread("lena.jpg", CV_LOAD_IMAGE_COLOR);
    if(img.empty()) {
          cout<<"cann't open file"<<endl;
          return -1;
    }
    cout<<"begin show image"<<endl;
    namedWindow( "lena", CV_WINDOW_AUTOSIZE );
    imshow("lena", img);
    cout<<"end show image"<<endl;
    waitKey(0);
    return 0;
}



