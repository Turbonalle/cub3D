#include "../incl/cub3d.h"

double to_radians(double degrees)
{
	// if (degrees < 0)
	// 	degrees += 360;
	// else if (degrees >= 360)
	// 	degrees -= 360;
	return (degrees * (M_PI / 180));
}