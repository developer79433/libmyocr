#ifndef OCR_H_
#define OCR_H_

#include <cstdlib>
#include <tesseract/baseapi.h>

namespace ocr {

class Recogniser {
public:
	virtual ~Recogniser() {};
};

}

#endif /* OCR_H_ */
