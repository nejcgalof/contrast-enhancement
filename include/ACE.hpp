double euclidean_distance(double x1, double y1, double x2, double y2)
{
	double x = x1 - x2;
	double y = y1 - y2;
	double dist;

	dist = pow(x, 2) + pow(y, 2);       //calculating Euclidean distance
	dist = sqrt(dist);

	return dist;
}

cv::Mat ACE(cv::Mat image, double alfa)
{
	double** arr_image = new double*[image.rows];
	for (int i = 0; i < image.rows; ++i) {
		arr_image[i] = new double[image.cols];
	}
	cv::Mat image_result = image.clone();
	for (int x = 0; x < image.rows; x++) {
		for (int y = 0; y < image.cols; y++) {
			double sum = 0;
			for (int xi = 0; xi < image.rows; xi++) {
				for (int yi = 0; yi < image.cols; yi++) {
					if (xi == x && yi == y) {
						continue;
					}
					double up =  MIN(MAX(alfa * (((double)image.at<uchar>(x,y)/255) - (double)image.at<uchar>(xi, yi)/255),-1),1);
					double down = euclidean_distance(x, y, xi, yi);
					sum += up / down;
				}
			}
			arr_image[x][y] = sum;
		}
	}
	int max = arr_image[0][0], min = arr_image[0][0];
	int i, j;

	for (i = 0; i < image.rows; i++) {
		for (j = 0; j < image.cols; j++)
		{
			if (arr_image[i][j] > max) {
				max = arr_image[i][j];
			}
			if (arr_image[i][j] < min) {
				min = arr_image[i][j];
			}
		}
	}
	for (int x = 0; x < image.rows; x++) {
		for (int y = 0; y < image.cols; y++) {
			image_result.at<uchar>(x, y) = 255*((arr_image[x][y] - min) / (max-min));
		}
	}
	return image_result;
}