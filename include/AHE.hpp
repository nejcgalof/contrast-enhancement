cv::Mat AHE(cv::Mat image, int window=100, bool cl=false, int treshold = 2000)
{
	cv::Mat image_result = image.clone();
	copyMakeBorder(image, image, window, window, window, window, cv::BORDER_REFLECT101);

	for (int y = 0+window; y < image.rows-window; y++)
	{
		for (int x = 0+window; x < image.cols-window; x++) 
		{
			cv::Rect roi(x-window, y-window, 2*window, 2*window);
			cv::Mat image_roi = image(roi);
			cv::Mat image_roi_hist = equalize_histogram(image_roi,cl,treshold);
			image_result.at<uchar>(y-window, x-window) = cv::saturate_cast<uchar>(image_roi_hist.at<uchar>(floor((2*window)/2), floor((2*window)/2)));
		}
	}
	return  image_result;
}