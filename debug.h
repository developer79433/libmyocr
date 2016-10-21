#ifndef DEBUG_H_
#define DEBUG_H_

#include <string>
#include <opencv2/opencv.hpp>

#include "util.h"

template <typename T> void dump_array_n(const std::string &name, const T *arr, unsigned int size);
template <typename T> void dump_point_array_n(const std::string &name, const cv::Point_<T> *arr, unsigned int size);
template <typename T> void dump_point_vector(const std::string &name, std::vector<cv::Point_<T> > &vec);
void dump_rect(const std::string &name, const cv::Rect &r);
void display_image(const std::string &name, const cv::Mat &image);
void drawContourBoundingRects(
	cv::Mat &image,
	std::vector<std::vector<cv::Point> > &contours,
	int contourIdx,
	const cv::Scalar& color,
	int thickness=1,
	int lineType=8);

#define dump_array(name, arr) do { dump_array_n(name, &(arr)[0], ELEMENTSOF(arr)); } while (0)
#define dump_point_array(name, arr) do { dump_point_array_n(name, &(arr)[0], ELEMENTSOF(arr)); } while (0)

#endif /* DEBUG_H_ */
