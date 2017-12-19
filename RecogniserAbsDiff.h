#ifndef RECOGNISERABSDIFF_H_
#define RECOGNISERABSDIFF_H_

#include <opencv2/opencv.hpp>
#include <cassert>

#include "ocr.h"

namespace ocr {

class RecogniserAbsDiff : public Recogniser {
private:
	std::string charset;
	std::vector<cv::Mat> char_images;
public:
	enum subsets {
		NONE = 0,
		ALPHA = 1,
		NUMERIC = 2,
		SPECIAL = 4,
		ALPHANUMERIC = ALPHA + NUMERIC,
		ALL = ALPHANUMERIC + SPECIAL
	};
	RecogniserAbsDiff(const std::string &character_set, const std::string &input_dir);
	virtual ~RecogniserAbsDiff(void) {}
	float compare(const cv::Mat &image, const cv::Mat &char_image, bool black_on_white = false);
	virtual char recognise(const cv::Mat& img, bool black_on_white = false, unsigned int subsets_allowed = subsets::ALL);
	virtual void recognise(const cv::Mat &img, const std::vector<std::vector<cv::Rect> > &lines, std::string &text);
};

}

#endif /* RECOGNISERABSDIFF_H_ */
