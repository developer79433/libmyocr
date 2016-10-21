#include <opencv2/opencv.hpp>

#include "distance.h"

double pythagorean_distance(const Point &p1, const Point &p2)
{
	double xdiff = p2.x - p1.x, ydiff = p2.y - p1.y;
	return sqrt(xdiff * xdiff + ydiff * ydiff);
}
