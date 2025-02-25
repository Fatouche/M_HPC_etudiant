#include <opencv2/opencv.hpp>
#include "utils.hpp"

const double COEF = 0.5;

int main(int argc, char ** argv) 
{ 
    if (argc != 2) 
    {
        std::cerr << "usage: " << argv[0] << " <filename> \n";
        exit(-1);
    }
    const char * filename = argv[1];
    std::string basename, extension;
    getBasenameAndExtension(filename, basename, extension);

    // load input image
    cv::Mat imgInput = cv::imread(filename);
    if (imgInput.channels()!=3 or imgInput.depth()!=CV_8U)
    {
        std::cerr << "error: only 3-channel 8-bits images are supported\n";
        exit(-1);
    }

    // operator*=
    timePoint_t tpMul0 = now();
    cv::Mat imgMul = imgInput.clone();
    imgMul *= COEF;
    timePoint_t tpMul1 = now();

    // foreach loop
    // TODO
    timePoint_t tForeach = now();

    cv::Mat imgForeach = imgInput.clone();
    imgForeach.forEach<cv::Vec3b>([](cv::Vec3b &p, const int * position) -> void{
	  p *= COEF;
       });
      
    timePoint_t tForeach1 = now();

    
    // 2D loop
    // TODO
    timePoint_t tBoucle = now();
    
    cv::Mat imgLoop = imgInput.clone();
    
    for(int col = 0; col < imgLoop.rows; col++){
      for(int ligne = 0; ligne < imgLoop.cols; ligne++){
	//imgLoop.at<int>(col,ligne) *= COEF;
	imgLoop.at<cv::Vec3b>(col,ligne) *= COEF; 
      } 
    }
    
    timePoint_t tBoucle1 = now();
    
    // print computation times
    std::cout << "imgMul: " << duration(tpMul0, tpMul1) << " s\n";
    // TODO
    std::cout << "imgLoop: " << duration(tBoucle, tBoucle1) << " s\n";
    std::cout << "imgForEach: " << duration(tForeach, tForeach1) << " s\n";
    
    // write image files
    imwrite(basename + "_imgMul" + extension, imgMul);
    // TODO
    imwrite(basename + "_imgLoop" + extension, imgLoop);
    imwrite(basename + "_imgForEach" + extension, imgForeach);
    
    // display images
    cv::imshow("imgInput", imgInput);
    cv::imshow("imgMul", imgMul);
    // TODO
    cv::imshow("imgLoop", imgLoop);
    cv::imshow("imgForEach", imgForeach);
      
    // wait for "esc"
    while (true)
    {
        int k = cv::waitKey(100) % 0x100;
        if (k == 27)
            break;
    }

    return 0;
}


