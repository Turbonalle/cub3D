#include "../incl/cub3d.h"

void center(mlx_image_t *img)
{
	img->instances[0].x -= img->width * 0.5;
	img->instances[0].y -= img->height * 0.5;
}

void center_vertically(mlx_image_t *img)
{
	img->instances[0].y -= img->height * 0.5;
}

void center_horizontally(mlx_image_t *img)
{
	img->instances[0].x -= img->width * 0.5;
}