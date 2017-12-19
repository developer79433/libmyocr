#ifndef OCR_H_
#define OCR_H_

#include <cstdlib>
#include <opencv2/opencv.hpp>

namespace ocr {

class Recogniser {
public:
	virtual ~Recogniser() {};
	virtual char recognise(const cv::Mat& img, bool black_on_white = false) = 0;
	virtual void recognise(const cv::Mat &image, const std::vector<std::vector<cv::Rect> > &lines, std::string &text, bool black_on_white = false);
};

}

#endif /* OCR_H_ */
