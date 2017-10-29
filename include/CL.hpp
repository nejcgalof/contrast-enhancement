void CL(int histogram[], int treshold = 2000) {
	int sum = 0;
	for (int i = 0; i < 256; i++)
	{
		if (histogram[i] > treshold) {
			sum += (histogram[i] - treshold);
			histogram[i] = treshold;
		}
	}
	int for_one = sum / 256;
	for (int i = 0; i < 256; i++)
	{
		histogram[i] += for_one;
	}
}