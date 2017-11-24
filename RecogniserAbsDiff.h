#ifndef RECOGNISERABSDIFF_H_
#define RECOGNISERABSDIFF_H_

#include <opencv2/opencv.hpp>
#include <cassert>

#include "ocr.h"

using namespace std;
using namespace cv;

namespace ocr {

class RecogniserAbsDiff : public Recogniser {
private:
	Mat letters;
	Mat charImage(char c);
public:
	RecogniserAbsDiff(const char *letters_image_filename);
	virtual ~RecogniserAbsDiff(void) {}
	virtual char recognise(const cv::Mat& img, bool black_on_white = false) {
		assert(0);
		return '\0'; // TODO
	}
	virtual char recognise(const cv::Mat &img, vector<vector<Rect> > &lines, string &text);
};

}

#endif /* RECOGNISERABSDIFF_H_ */
