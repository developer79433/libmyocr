#include <opencv2/opencv.hpp>
#include <tesseract/baseapi.h>

#if 0

struct Pix Mat2Pix(cv::Mat &m)
{
    struct Pix ret = {
        w: static_cast<uint32_t>(m.size().width),
        h: static_cast<uint32_t>(m.size().height),
        d: static_cast<uint32_t>(m.depth()),
        spp: static_cast<uint32_t>(m.channels()),
        wpl: static_cast<uint32_t>(m.size().width * m.depth()),
        refcount: 1,
        xres: 0,
        yres: 0,
        informat: IFF_UNKNOWN,
        special: 0,
        text: NULL,
        colormap: NULL,
        data: reinterpret_cast<l_uint32 *>(m.data)
    };

    return ret;
}

cv::Mat Pix2Mat(struct Pix &p)
{
    cv::Mat ret;
    // TODO
    return ret;
}

#endif
