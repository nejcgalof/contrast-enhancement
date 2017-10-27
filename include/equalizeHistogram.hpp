void image_histogram(cv::Mat image, int histogram[])
{
	// All intensity values to 0
	for (int i = 0; i < 256; i++)
	{
		histogram[i] = 0;
	}

	// Calculate number of pixels for each intensity values
	for (int y = 0; y < image.rows; y++) {
		for (int x = 0; x < image.cols; x++) {
			histogram[(int)image.at<uchar>(y, x)]++;
		}
	}
}

void cumulative_histogram(int histogram[], int* cum_hist)
{
	cum_hist[0] = histogram[0];
	for (int i = 1; i < 256; i++)
	{
		cum_hist[i] = histogram[i] + cum_hist[i - 1];
	}
}

void scale_histogram(int cum_hist[], double num_pixels, int scale_hist[])
{
	// From histogram equalization formula
	int smallest = INT_MAX;
	for (int i = 0; i < 256; i++) {
		if (cum_hist[i] < smallest && cum_hist[i] > 0) {
			smallest = cum_hist[i];
		}
	}
	for (int i = 0; i < 256; i++)
	{
		scale_hist[i] = cvRound(((cum_hist[i] - smallest) / (num_pixels - 1)) * 255);
	}
}

cv::Mat equalize_histogram(cv::Mat image, int width, int height, int max_val = 255)
{
	int hist[256];
	int cum_hist[256];
	int scale_hist[256];

	image_histogram(image, hist);
	cumulative_histogram(hist, cum_hist);
	scale_histogram(cum_hist, (image.rows * image.cols), scale_hist);

	cv::Mat new_image = image.clone();
	for (int y = 0; y < image.rows; y++) {
		for (int x = 0; x < image.cols; x++) {
			new_image.at<uchar>(y, x) = cv::saturate_cast<uchar>(scale_hist[image.at<uchar>(y, x)]);
		}
	}
	return new_image;
}
