#include "../incl/cub3d.h"

int	set_transparency(int color, int transparency)
{
	float	alpha;

	alpha = 100 - transparency;
	if (alpha < 0)
		alpha = 0;
	else
		alpha *= 255 / 100;
	color = set_a(color, (int)alpha);
	return (color);
}