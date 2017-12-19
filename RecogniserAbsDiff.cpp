#include "RecogniserAbsDiff.h"
#include "debug.h"

namespace ocr {

RecogniserAbsDiff::RecogniserAbsDiff(const std::string &character_set, const std::string &input_dir)
: charset(character_set)
{
	std::for_each(charset.begin(), charset.end(), [this, input_dir](const char c) {
		std::string file_name(input_dir);
		file_name += '/';
		file_name += c;
		file_name += ".png";
		char_images.push_back(cv::imread(file_name, CV_LOAD_IMAGE_GRAYSCALE));
	});
}

float RecogniserAbsDiff::compare(const cv::Mat &input_image, const cv::Mat &char_image, bool black_on_white)
{
	cv::Mat input_scaled;
#if 0
	// OCRB characters are all of uniform height, but their widths differ.
	// Isotropically scale the input image to the same height as the reference image.
	float input_aspect = input_image.rows / input_image.cols;
	final_rows = char_image.rows;
	final_aspect = input_aspect;
	final_aspect = final_rows / final_cols;
	final_cols = final_rows / final_aspect;
	final_cols = final_rows / input_aspect;
	final_cols = char_image.rows / input_aspect;
	final_cols = char_image.rows / (input_image.rows / input_image.cols);
	final_cols = char_image.rows * (input_image.cols / input_image.rows);
	final_cols = char_image.rows * input_image.cols / input_image.rows;
	cv::resize(input_image, input_scaled, cv::Size(char_image.rows * input_image.cols / input_image.rows, char_image.rows), 0, 0, CV_INTER_CUBIC);
#else
 	cv::resize(input_image, input_scaled, cv::Size(char_image.cols, char_image.rows), 0, 0, CV_INTER_CUBIC);
#endif
 	cv::threshold(input_scaled, input_scaled, 127, 255, black_on_white ? CV_THRESH_BINARY_INV : CV_THRESH_BINARY);
#if 0
	display_image("Input image", input_scaled);
#endif
#if 0
	display_image("Char image", char_image);
#endif
	cv::Mat diff = abs(input_scaled - char_image);
	cv::Scalar sum = cv::sum(diff);
	assert(0 == sum[1]);
	assert(0 == sum[2]);
	assert(0 == sum[3]);
	// std::cerr << "Diff sum: " << sum[0] << std::endl;
#if 0
	display_image("Difference", diff);
#endif
	// return sum[0] / (char_image.cols * char_image.rows);
	return sum[0];
}

char RecogniserAbsDiff::recognise(const cv::Mat &input_image, bool black_on_white, unsigned int subsets_allowed)
{
	float min_diff = -1;
	float min_diff_idx = 0;
	size_t i = 0;
	std::for_each(
		char_images.begin(),
		char_images.end(),
		[this, input_image, &i, &min_diff, &min_diff_idx, black_on_white, subsets_allowed]
		(const cv::Mat &char_image) {
			char c = charset[i];
			if (
				((subsets_allowed & SPECIAL) && !isalpha(c) && !isdigit(c))
				|| ((subsets_allowed & ALPHA)   && isalpha(c))
				|| ((subsets_allowed & NUMERIC) && isdigit(c))
			) {
				float new_diff = compare(input_image, char_image, black_on_white);
				if (-1 == min_diff || new_diff < min_diff) {
					min_diff = new_diff;
					min_diff_idx = i;
				}
			}
			i++;
		}
	);
	return charset[min_diff_idx];
}

void RecogniserAbsDiff::recognise(const cv::Mat& img, const std::vector<std::vector<cv::Rect> > &lines, std::string &text)
{
	std::for_each(lines.begin(), lines.end(), [this, img, &text](const std::vector<cv::Rect> &line) {
		std::for_each(line.begin(), line.end(), [this, img, &text](const cv::Rect &char_rect) {
			cv::Mat char_image(img(char_rect));
			text += recognise(char_image, true);
		});
	});
}

}
