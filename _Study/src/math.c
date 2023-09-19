#include "../incl/raycaster.h"

//------------------------------------------------------------------------------

void switch_values(int *a, int *b)
{
	*a = *a + *b;
	*b = *a + *b;
	*a = *a - *b;
}

//------------------------------------------------------------------------------

double distance(double_vector_t a, double_vector_t b)
{
	double distance;
	double x_dist;
	double y_dist;

	x_dist = a.x - b.x;
	if (x_dist < 0)
		x_dist = -x_dist;
	y_dist = a.y - b.y;
	if (y_dist < 0)
		y_dist = -y_dist;
	distance = sqrt((x_dist * x_dist) + (y_dist * y_dist));
	return (distance);
}