#include "../incl/cub3d.h"

double	elapsed_time(cub3d_t *cub3d)
{
	return (mlx_get_time() - cub3d->start_timestamp);
}

double	elapsed_frame_time(cub3d_t *cub3d)
{
	return (mlx_get_time() - cub3d->frame_start_timestamp);
}

void	handle_fps(cub3d_t *cub3d)
{
	while (elapsed_frame_time(cub3d) < cub3d->frame_time)
		;
	cub3d->delta_time = elapsed_frame_time(cub3d);
	cub3d->frame_start_timestamp = mlx_get_time();
}

void	set_fps(double *frame_time, int fps)
{
	*frame_time = 1.0 / (double)fps;
}

void	start_timer(cub3d_t *cub3d)
{
	cub3d->run_time = 0;
	cub3d->pause_timestamp = 0;
	cub3d->delta_time = 0;
	cub3d->frame_time = 1.0 / (double)cub3d->settings.fps;
	cub3d->start_timestamp = mlx_get_time();
	cub3d->frame_start_timestamp = cub3d->start_timestamp;
}
