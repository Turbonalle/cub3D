#include "../incl/cub3d.h"

double within_two_pi(double radians)
{
	if (radians < 0)
		radians += 2 * M_PI;
	else if (radians >= 2 * M_PI)
		radians -= 2 * M_PI;
	return (radians);
}

double to_radians(double degrees)
{
	return (degrees * (M_PI / 180));
}