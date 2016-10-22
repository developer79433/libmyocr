#include <iostream>

#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include <leptonica/bmp.h>

#include "recogniser_tesseract.h"
#include "util.h"

namespace ocr {

using namespace std;
using namespace tesseract;

RecogniserTesseract::RecogniserTesseract(const char *lang, const char *data_dir, const char *whitelist) : api(NULL), image(NULL)
{
    api = new TessBaseAPI();
    if (api->Init(data_dir, lang)) {
        cerr
        << "Could not initialize tesseract with language " << lang
        << " and data directory "
        << (data_dir ? "" : "'")
        << (data_dir || "<default>")
        << (data_dir ? "" : "'")
        << endl;
        delete_api();
    }
    if (!api->SetVariable("load_system_dawg", "F")) {
        delete_api();
    }
    if (!api->SetVariable("load_freq_dawg", "F")) {
        delete_api();
    }
    if (!api->SetVariable("load_unambig_dawg", "F")) {
        delete_api();
    }
    if (!api->SetVariable("load_punc_dawg", "F")) {
        delete_api();
    }
    if (!api->SetVariable("load_number_dawg", "F")) {
        delete_api();
    }
    if (!api->SetVariable("load_fixed_length_dawgs", "F")) {
        delete_api();
    }
    if (!api->SetVariable("load_bigram_dawg", "F")) {
        delete_api();
    }
    if (!api->SetVariable("load_bigram_dawg", "F")) {
        delete_api();
    }
    if (!api->SetVariable("wordrec_enable_assoc", "F")) {
        delete_api();
    }
#if 0 /* Requires ScrollView */
    if (!api->SetVariable("interactive_display_mode", "T")) {
        delete_api();
    }
#endif
    if (whitelist && !api->SetVariable("tessedit_char_whitelist", whitelist)) {
        delete_api();
    }
    if (!api) {
        throw("API init failed");
    }
}

RecogniserTesseract::~RecogniserTesseract(void)
{
    if (api) {
        api->End();
        delete api;
        api = NULL;
    }
    if (image) {
        pixDestroy(&image);
        image = NULL;
    }
}

void RecogniserTesseract::set_image(Pix *image)
{
    // Don't set self->image, because we don't own it
    api->SetImage(image);
}

void RecogniserTesseract::set_image(
    const unsigned char *imagedata,
    int width,
    int height,
    int bytes_per_pixel,
    int bytes_per_line
)
{
    // Don't set self->image, because it is being bypassed
    api->SetImage(imagedata, width, height, bytes_per_pixel, bytes_per_line);
}

void RecogniserTesseract::set_image_bmp(const void *bmp_data)
{
    const unsigned char *ptr =
      reinterpret_cast<const unsigned char *>(bmp_data);
    const struct BMP_FileHeader *hdr = reinterpret_cast<const struct BMP_FileHeader *>(ptr);
    const struct BMP_InfoHeader *info_hdr = reinterpret_cast<const struct BMP_InfoHeader *>(ptr + sizeof(struct BMP_FileHeader));
    const unsigned char *pixel_data = ptr + hdr->bfOffBits;
    set_image(pixel_data, info_hdr->biWidth, info_hdr->biHeight, info_hdr->biPlanes, ROUND_4(info_hdr->biWidth));
}

void RecogniserTesseract::set_image(const char *filename)
{
    if (image) {
        pixDestroy(&image);
        image = NULL;
    }
    // Open input image with leptonica library
    // set self->image, because now we own the image
    image = pixRead(filename);
    set_image(image);
}

void RecogniserTesseract::ocr(void)
{
#ifdef SIMPLE
    // Get OCR result
    char *outText = api->GetUTF8Text();
    cout << "OCR output:" << endl << outText << endl;
    delete [] outText;
#else
    api->Recognize(0);
      ResultIterator* ri = api->GetIterator();
      PageIteratorLevel level = tesseract::RIL_WORD;
      if (ri != 0) {
        do {
          const char* word = ri->GetUTF8Text(level);
          float conf = ri->Confidence(level);
          int x1, y1, x2, y2;
          ri->BoundingBox(level, &x1, &y1, &x2, &y2);
          cout << "word: '" << word << "';  \tconf: " << conf << "; BoundingBox: " << x1 << "," << y1 << "," << x2 << "," << y2 << ";" << endl;
          delete[] word;
        } while (ri->Next(level));
      }
#endif
}

char RecogniserTesseract::recognise(const cv::Mat & img, bool black_on_white)
{
	// TODO
	return '?';
}

}
