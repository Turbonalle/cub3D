#include "../incl/cub3d.h"

int	init_floor(cub3d_t *cub3d)
{
	cub3d->floor.path = FLOOR_PNG;
	cub3d->floor.texture = mlx_load_png(FLOOR3_PNG);
	if (!cub3d->floor.texture)
		return (err("Failed to init floor"));
	cub3d->printed = TRUE;	// DEBUG
	return (SUCCESS);
}
