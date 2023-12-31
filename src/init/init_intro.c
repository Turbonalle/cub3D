#include "../incl/cub3d.h"

int	init_intro(cub3d_t *cub3d)
{
	cub3d->intro_watched = FALSE;
	cub3d->intro.texture = mlx_load_png(INTRO_PNG);
	cub3d->intro.img = mlx_texture_to_image(cub3d->mlx, cub3d->intro.texture);
	if (!cub3d->intro.img)
		return (err("Failed to load intro image"));
	if (mlx_image_to_window(cub3d->mlx, cub3d->intro.img, 0, 0) < 0)
		return (err("Failed to put intro image to window"));
	disable_intro(cub3d);
	return (SUCCESS);
}