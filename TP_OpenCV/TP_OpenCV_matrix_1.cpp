#include <opencv2/opencv.hpp>
#include "utils.hpp"

int main()
{

    cv::Mat M = (cv::Mat_<float>(2, 3) << 1, 2, 3, 4, 5, 6);
    cv::Mat I = cv::Mat::eye(3,3,CV_64F);
    cv::Mat U = (cv::Mat_<float>(3, 1) << 1, 2, 3);
    cv::Mat V = (cv::Mat_<float>(3, 1) << 1, 1, 1);
    
    
    std::cout << "---- M ----\n" << M << std::endl;
    std::cout << "---- I ----\n" << I << std::endl;
    std::cout << "---- U ----\n" << U << std::endl;
    std::cout << "---- V ----\n" << V << std::endl;
    
    // TODO
    cv::Mat prodMatri = M*V;
    std::cout << "---- MV ----\n" << prodMatri << std::endl;

    double scMatri = U.dot(V);
    std::cout << "---- U.V ----\n" << scMatri << std::endl;

    std::cout << "---- M01 ----\n" << M.at<float>(0,1) << std::endl;

    cv::Mat P = cv::ml::TrainData::loadFromCSV("TP_OpenCV_matrix.csv", 0, -2, 0)->getSamples();

    std::cout << "---- P ----\n" << P << std::endl;

 return 0;
}

