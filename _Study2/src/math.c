#include "../incl/raycaster.h"

//------------------------------------------------------------------------------

void switch_values(int *a, int *b)
{
	*a = *a + *b;
	*b = *a + *b;
	*a = *a - *b;
}

//------------------------------------------------------------------------------

double distance(vector_t a, vector_t b)
{
	double distance;
	double x_dist;
	double y_dist;

	x_dist = abs(a.x - b.x);
	y_dist = abs(a.y - b.y);
	distance = sqrt((x_dist * x_dist) + (y_dist * y_dist));
	return (distance);
}