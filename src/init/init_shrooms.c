#include "../incl/cub3d.h"

static void	load_png(cub3d_t *cub3d)
{
	cub3d->shroom->shroom.texture = mlx_load_png(TEXTURE_MUSHROOM);
}

static int	init_images(cub3d_t *cub3d)
{
	cub3d->shroom->shroom.img = mlx_texture_to_image(cub3d->mlx, cub3d->shroom->shroom.texture);
	return (1);
}

static int	set_position(cub3d_t *cub3d)
{
	cub3d->shroom->shroom.pos.x = cub3d->mlx->width * 0.9;
	cub3d->shroom->shroom.pos.y = cub3d->mlx->height * 0.95;
	return (1);
}

static int	put_image_to_window(cub3d_t *cub3d)
{
	mlx_image_to_window(cub3d->mlx, cub3d->shroom->shroom.img, cub3d->shroom->shroom.pos.x, cub3d->shroom->shroom.pos.y);
	return (1);
}

int	init_shroom(cub3d_t *cub3d)
{
	load_png(cub3d);
	init_images(cub3d);
	set_position(cub3d);
	put_image_to_window(cub3d);
	disable_shroom(cub3d);
	return (1);
}
