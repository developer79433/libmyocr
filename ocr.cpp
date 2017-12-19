#include <iostream>

#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include <leptonica/bmp.h>

#include <opencv2/opencv.hpp>

#include "ocr.h"
#include "util.h"

namespace ocr {

using namespace std;
using namespace cv;

void Recogniser::recognise(const Mat &image, const vector<vector<Rect> > &lines,
		string &text, bool black_on_white)
{
#if 0
	display_image("recognise_chars image", image);
#endif
	for_each(lines.begin(), lines.end(),
			[&image, &text, black_on_white, this](const vector<Rect> &line) {
				for_each(line.begin(), line.end(), [&image, &text, black_on_white, this](const Rect &bbox) {
							Mat character(image(bbox));
							char s[2] = {0, 0};
							s[0] = recognise(character, black_on_white);
							text.append(s);
#if 0 || defined(DISPLAY_INTERMEDIATE_IMAGES)
			cerr << "Recognised char: " << s[0] << endl;
			display_image("Recognising", character);
#endif /* 0 || defined(DISPLAY_INTERMEDIATE_IMAGES) */
		});
});
}

}
