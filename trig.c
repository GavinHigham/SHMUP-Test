#include "trig.h"
#include <math.h>

float deg_to_rad(float degrees)
{
	return (M_PI / 180) * degrees; //Floating point mult/div is not commutative. Parens help the compiler optimize.
}

float rad_to_deg(float radians)
{
	return (180 / M_PI) * radians; //Floating point mult/div is not commutative. Parens help the compiler optimize.
}