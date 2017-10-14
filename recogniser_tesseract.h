#ifndef RECOGNISER_TESSERACT_H
#define RECOGNISER_TESSERACT_H 1

#include <cstdlib>
#include <opencv2/opencv.hpp>
#include <tesseract/baseapi.h>

#include "ocr.h"
#include "mat_pix_glue.h"

namespace ocr {

class RecogniserTesseract : public Recogniser {
private:
    tesseract::TessBaseAPI *api;
    Pix *image;
    void delete_api(void) {
        delete api;
        api = NULL;
    };
public:
    RecogniserTesseract(const char *lang = "eng", const char *data_dir = NULL, const char *whitelist = NULL);
    virtual ~RecogniserTesseract(void);
    void set_image(Pix *image);
    void set_image(
        const unsigned char *imagedata,
        int width,
        int height,
        int bytes_per_pixel,
        int bytes_per_line
    );
    void set_image_bmp(const void *bmp_data);
    virtual char recognise(const cv::Mat & img, bool black_on_white = false);
    void ocr(void);
    void set_image(const char *filename);
};

}

#endif /* RECOGNISER_TESSERACT_H */
