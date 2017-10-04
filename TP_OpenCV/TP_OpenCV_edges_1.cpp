#include <opencv2/opencv.hpp>
#include "utils.hpp"

int main() 
{
    const std::string inputName = "parrots.jpg";
    const std::string outputName = "parrotsModifier.jpg";

    timePoint_t tp0 = now();

    cv::Mat img = cv::imread(inputName);
    cv::UMat inputFrame;
    cv::UMat edgeFrame;
    
    img.copyTo(inputFrame);
    
    
    cv::GaussianBlur(inputFrame, edgeFrame, cv::Size(9,9),1.5,1.5);
    cv::Canny(edgeFrame, edgeFrame, 0, 40);  
    cv::cvtColor(edgeFrame, gray, cv::COLOR_BGR2GRAY);

    cv::imshow("test",edgeFrame);

    // video capture
    // TODO

    /* cv::VideoCapture cap(inputName);
    assert(cap.isOpened());
    int width = cap.get(CV_CAP_PROP_FRAME_WIDTH);
    int height = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
    int fps = cap.get(CV_CAP_PROP_FPS);*/

    // video writer
    // TODO : fourcc=MJPG
    /*cv::VideoWriter video(outputName, CV_FOURCC('M','J','P','G'), fps, cv::Size(width, height));*/
    
    // process video
    /*   cv::Mat inputFrame, edgeFrame;
    while (true)
    {
        // get frame
        // TODO
      cap >> inputFrame;
      if (inputFrame.rows<=0 || inputFrame.cols<=0) break;
      
        // detect edges 
        // TODO : gray, gaussian blur, canny, rgb
      cv::Mat gray;
      
      cv::GaussianBlur(inputFrame, edgeFrame, cv::Size(9,9),1.5,1.5);
      cv::Canny(edgeFrame, edgeFrame, 0, 40);  
      cv::cvtColor(edgeFrame, gray, cv::COLOR_BGR2GRAY);
      
      
        // write edges 
        // TODO
      video.write(edgeFrame);
      }*/

    timePoint_t tp1 = now();
    std::cout << duration(tp0, tp1) << " s\n";

    return 0;
}

