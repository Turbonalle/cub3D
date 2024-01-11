#include "../incl/cub3d.h"

static double	parametric_blend(double t)
{
	double	sqt;

	sqt = t * t;
	return (sqt / (2 * (sqt - t) + 1));
}

double	get_time_fade(halo_t *halo)
{
	double	fade;
	double	time_delta;

	time_delta = (mlx_get_time() - halo->timestamp);
	if (time_delta < HALO_TIME / 5.0f)
		fade = ((double)parametric_blend(time_delta * 5 / HALO_TIME));
	else
	{
		fade = (double)parametric_blend(1 - (time_delta
					- HALO_TIME / 5.0f) / HALO_TIME * 1.25);
	}
	return (fade);
}
