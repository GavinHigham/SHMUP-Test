#include "trig.h"
#include <math.h>
#ifdef _WIN32
const float M_PI = 3.14159265359;
#endif

float deg_to_rad(float degrees)
{
	return degrees * M_PI / 180;
}

float rad_to_deg(float radians)
{
	return radians * 180 / M_PI;
}