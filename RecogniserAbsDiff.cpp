#include "RecogniserAbsDiff.h"

using namespace std;
using namespace cv;

namespace ocr {

Mat RecogniserAbsDiff::charImage(char c) {
	int char_idx;
	if (c >= 'A' && c <= 'Z') {
		char_idx = 'A' - c;
	} else if (c >= '0' && c <= '9') {
		char_idx = 26 + '9' - c;
	} else if ('<' == c) {
		char_idx = 36;
	} else {
		char_idx = -1;
	}
	if (char_idx <= 0) {
		return Mat();
	} else {
		Rect letter_rect(char_idx * letters.cols / 37, 0, (char_idx + 1) * letters.cols / 37, letters.rows);
		return Mat(letters, letter_rect);
	}
}

RecogniserAbsDiff::RecogniserAbsDiff(const char *letters_image_filename)
: letters()
{
	Mat grey = imread(letters_image_filename, CV_LOAD_IMAGE_GRAYSCALE);
	if (grey.empty()) {
		cerr << "Unable to read  '" << letters_image_filename << "'" << endl;
	} else {
		threshold(grey, letters, 255/2, 255, THRESH_BINARY);
	}
}

char RecogniserAbsDiff::recognise(const cv::Mat& img, vector<vector<Rect> > &lines, string &text)
{
	// TODO: bitwise_xor
	// TODO: countNonZero
	return '\0' ; // TODO
}

}
