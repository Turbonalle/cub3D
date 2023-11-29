#include "../incl/cub3d.h"

double	elapsed_time(cub3d_t *cub3d)
{
	return (mlx_get_time() - cub3d->start_time);
}

double	elapsed_frame_time(cub3d_t *cub3d)
{
	return (mlx_get_time() - cub3d->frame_start_time);
}

void	handle_fps(cub3d_t *cub3d)
{
	while (elapsed_frame_time(cub3d) < cub3d->frame_time)
		;
	printf("Frame time: %f\n", elapsed_frame_time(cub3d));
	cub3d->frame_start_time = mlx_get_time();
}

void	set_fps(double *frame_time, int fps)
{
	*frame_time = 1.0 / (double)fps;
	printf("FPS: %d\n", fps);
	printf("Frame time: %f\n", *frame_time);
}