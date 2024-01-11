#include "../incl/cub3d.h"

static int	load_png(cub3d_t *cub3d)
{
	printf("cub3d->shroom: %p\n", cub3d->shroom);
	//printf("cub3d->shroom->shroom: %p\n", cub3d->shroom->shroom);
	printf("cub3d->shroom->shroom.texture: %p\n", cub3d->shroom->shroom.texture);
	cub3d->shroom->shroom.texture = mlx_load_png(TEXTURE_MUSHROOM_COUNTER);
	if (!cub3d->shroom->shroom.texture)
		return (0);
	return (1);
}

static int	init_images(cub3d_t *cub3d)
{
	cub3d->shroom->shroom.img = mlx_texture_to_image(cub3d->mlx, cub3d->shroom->shroom.texture);
	if (!cub3d->shroom->shroom.img)
		return (0);
	return (1);
}

static void	set_position(cub3d_t *cub3d)
{
	cub3d->shroom->shroom.pos.x = cub3d->mlx->width * 0.95 - cub3d->shroom->shroom.img->width;
	cub3d->shroom->shroom.pos.y = cub3d->mlx->height * 0.95 - cub3d->shroom->shroom.img->height;
}

static int	put_image_to_window(cub3d_t *cub3d)
{
	if (mlx_image_to_window(cub3d->mlx, cub3d->shroom->shroom.img, cub3d->shroom->shroom.pos.x, cub3d->shroom->shroom.pos.y) == -1)
		return (0);
	return (1);
}

int	init_shroom(cub3d_t *cub3d)
{
	cub3d->shroom = ft_calloc(1, sizeof(shroom_t));
	if (!load_png(cub3d))
		return (0);
	if (!init_images(cub3d))
		return (0);
	set_position(cub3d);
	if (!put_image_to_window(cub3d))
		return (0);
	disable_shroom(cub3d);
	return (1);
}
