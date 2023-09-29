#include "../incl/cub3d.h"

int init_cub3d(cub3d_t *cub3d)
{
	cub3d->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", TRUE);
	if (!cub3d->mlx)
		return (!err("Failed to initialize mlx"));
	cub3d->img = mlx_new_image(cub3d->mlx, WIDTH, HEIGHT);
	if (!cub3d->img || (mlx_image_to_window(cub3d->mlx, cub3d->img, 0, 0) < 0))
		return (!err("Failed to create image"));
	return (SUCCESS);
}