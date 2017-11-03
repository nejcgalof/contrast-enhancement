#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <equalizeHistogram.hpp>
#include <AHE.hpp>
#include <ACE.hpp>

using namespace cv;

int main(int argc, char** argv )
{
    if ( argc > 5 || argc < 1 )
    {
        printf("Usage: Contrast_enhancement.exe <Image_Path> <HE|AHE|CLHE|CLAHE> <window_size> <treshold>\n");
        return -1;
    }

    Mat image;
    image = imread( argv[1], 1 );

    if ( !image.data )
    {
        printf("No image data \n");
        return -1;
    }

	cvtColor(image, image, CV_BGR2GRAY);
	string name = std::string(argv[1]);
	Mat image_result;
	if (std::string(argv[2]) == "HE") {
		image_result = equalize_histogram(image);
		cv::imwrite(name.substr(0, name.length() - 4) + "_" + std::string(argv[2]) + ".jpg", image_result);
	}
	else if (std::string(argv[2]) == "AHE") {
		image_result = AHE(image, atoi(argv[3]));
		cv::imwrite(name.substr(0, name.length() - 4) + "_" + std::string(argv[2]) +"_"+string(argv[3]) + ".jpg", image_result);
	}
	else if (std::string(argv[2]) == "CLHE") {
		image_result = equalize_histogram(image, true, atoi(argv[3]));
		cv::imwrite(name.substr(0, name.length() - 4) + "_" + std::string(argv[2]) + "_"+string(argv[3])+ ".jpg", image_result);
	}
	else if (std::string(argv[2]) == "CLAHE") {
		image_result = AHE(image, atoi(argv[3]),true, atoi(argv[4]));
		cv::imwrite(name.substr(0, name.length() - 4) + "_" + std::string(argv[2])  +"_" + string(argv[3]) +"_" + string(argv[4])+ ".jpg", image_result);
	}
	else if (std::string(argv[2]) == "ACE") {
		image_result = ACE(image, strtod(argv[3], NULL));
		cv::imwrite(name.substr(0, name.length() - 4) + "_" + std::string(argv[2]) +"_" + string(argv[3]) + ".jpg", image_result);
	}
	else {
		printf("Wrong algorithm! \n");
		return -1;
	}
    return 0;
}