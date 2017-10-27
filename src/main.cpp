#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <equalizeHistogram.hpp>

using namespace cv;

int main(int argc, char** argv )
{
    if ( argc != 2 )
    {
        printf("usage: DisplayImage.out <Image_Path>\n");
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
	imshow("Original image", image);
	Mat image1 = image.clone();

	Mat EH_image = equalize_histogram(image1, image.size().width, image.size().height, 255);
	// Display equilized image
	cv::namedWindow("Equilized Image");
	cv::imshow("Equilized Image", EH_image);
    waitKey(0);

    return 0;
}