//============================================================================
// Name        : KMeansDemo.cpp
// Author      : Jean Vitor
// Website     : www.jeanvitor.com
//============================================================================
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <string>
#include <vector>
#include <iostream>
#include <chrono>

/*****************************************************************************************************************************/
//Namespaces
using cv::Mat;

/*****************************************************************************************************************************/
//Global Variables
const unsigned int SLIDER_MAX = 25;
const std::string WINDOW_NAME = "KMeans demo - www.jeanvitor.com";
const std::string TRACKBAR_NAME = "Clusters";
int MAX_ITERATIONS = 2;
int sliderValue;
Mat image;

/*****************************************************************************************************************************/
/**
    Returns the processed image using cv::kmeans

    @param const Mat& source The image to be processed.
    @return A reduced color image with (sliderValue) colors
*/
Mat applyKMeans(const Mat& source);

/**
    Callback function for trackbar event

*/
void trackBarMovement(int, void*);

/*****************************************************************************************************************************/

int main () {
	std::string imageName;
	std::cout << "Enter the name of the image" << std::endl;
	std::cin >> imageName;
	image = imread(imageName, cv::IMREAD_COLOR);
	if (!image.data){
		std::cout << "Invalid name" << std::endl;
		cv::destroyAllWindows();
		return EXIT_FAILURE;
	}
	cv::namedWindow(WINDOW_NAME, cv::WINDOW_AUTOSIZE);
	cv::createTrackbar(TRACKBAR_NAME,WINDOW_NAME, &sliderValue, SLIDER_MAX, trackBarMovement );
	cv::waitKey(0);
	cv::destroyAllWindows();
	return EXIT_SUCCESS;
}

/*****************************************************************************************************************************/

Mat applyKMeans(const Mat& source){
	if (sliderValue==0){
		sliderValue=1;
	}

	std::chrono::high_resolution_clock::time_point start,end; // for time measurement
	std::chrono::duration<double> elapsedTime;			 	  // for time measurement
	start = std::chrono::high_resolution_clock::now();
	const unsigned int singleLineSize = source.rows * source.cols;
	Mat data = source.reshape(1, singleLineSize);
	data.convertTo(data, CV_32F);
	std::vector<int> labels;
	cv::Mat1f colors;
	cv::kmeans(data, sliderValue,labels,cv::TermCriteria(cv::TermCriteria::EPS+cv::TermCriteria::COUNT, 10, 1.),MAX_ITERATIONS,cv::KMEANS_PP_CENTERS,colors);
	for (unsigned int i = 0 ; i < singleLineSize ; i++ ){
				data.at<float>(i, 0) = colors(labels[i], 0);
		        data.at<float>(i, 1) = colors(labels[i], 1);
		        data.at<float>(i, 2) = colors(labels[i], 2);
	}

	Mat outputImage = data.reshape(3, source.rows);
	outputImage.convertTo(outputImage, CV_8U);
	end = std::chrono::high_resolution_clock::now();
	elapsedTime = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
	std::cout<< "Elapsed time for processing with " << sliderValue <<" clusters " << elapsedTime.count() << "s" << std::endl;
	return outputImage;
}

/*****************************************************************************************************************************/

void trackBarMovement(int, void*){
	cv::imshow(WINDOW_NAME, applyKMeans(image));
}

/*****************************************************************************************************************************/
