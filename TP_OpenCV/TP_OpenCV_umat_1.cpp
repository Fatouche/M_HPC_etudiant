#include <opencv2/opencv.hpp>
#include "utils.hpp"

int main(int argc, char ** argv) 
{ 
    // check command line arguments
    if (argc != 4) 
    {
        std::cerr << "usage: " << argv[0] << " <filename> <blur size> <blur sigma>\n";
        exit(-1);
    }
    // filename 
    const char * filename = argv[1];
    std::string basename, extension;
    getBasenameAndExtension(filename, basename, extension);
    // blur size
    int blurSize = atoi(argv[2]);
    if (blurSize % 2 != 1) blurSize++;  // ensure blur size is odd
    // blur sigma
    double blurSigma = atof(argv[3]);

    const int NB_REPEAT = 3;

    // blur image using cv::Mat
    for (int n=0; n<NB_REPEAT; ++n)
    {
        std::cout << "cv::Mat" << std::endl;
        timePoint_t tp0 = now();

        // TODO read image
	cv::Mat img = cv::imread(filename);
	cv::UMat imgGpu;
	img.copyTo(imgGpu);
	timePoint_t tp1 = now();

	
        // TODO compute gaussian blur
	cv::UMat imgGpu2;
	cv::GaussianBlur(imgGpu, imgGpu2, cv::Size(blurSize,blurSize), blurSigma, blurSigma);
	timePoint_t tp2 = now();

	
        // TODO write image
	cv::imwrite("imgModifier.png", imgGpu2);
	timePoint_t tp3 = now();
	cv::imshow("ImgModifier",imgGpu2);
	
        timePoint_t tp4 = now();
	std::cout << "  imread: " << duration(tp0, tp1) << " s\n";
	std::cout << "  GaussianBlur: " << duration(tp0, tp2) << " s\n";
	std::cout << "  inwrite: " << duration(tp0, tp3) << " s\n";
        std::cout << "  total: " << duration(tp0, tp4) << " s\n";
    }

    return 0;
}

