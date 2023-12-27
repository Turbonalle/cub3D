#include "../incl/cub3d.h"

static void	load_png(cub3d_t *cub3d)
{
	int	i;

	i = -1;
	while (++i < HEARTS)
	{
		cub3d->hearts[i].full.texture = mlx_load_png(HEART_FULL_PNG);
		cub3d->hearts[i].empty.texture = mlx_load_png(HEART_EMPTY_PNG);
	}
}

static int	init_images(cub3d_t *cub3d)
{
	int	i;

	i = -1;
	while (++i < HEARTS)
	{
		cub3d->hearts[i].full.img
			= mlx_texture_to_image(cub3d->mlx, cub3d->hearts[i].full.texture);
		if (!cub3d->hearts[i].full.img)
			return (err("Failed to create heart image"));
		cub3d->hearts[i].empty.img
			= mlx_texture_to_image(cub3d->mlx, cub3d->hearts[i].empty.texture);
		if (!cub3d->hearts[i].empty.img)
			return (err("Failed to create heart image"));
	}
	return (SUCCESS);
}

static int	set_positions(cub3d_t *cub3d)
{
	int				i;
	int				margin;
	int				width;
	int				height;
	unsigned int	heart_area;

	i = -1;
	width = cub3d->hearts[0].full.texture->width;
	height = cub3d->hearts[0].full.texture->height;
	heart_area = (width * HEARTS + HEART_GAP * (HEARTS - 1));
	if (heart_area > cub3d->img->width)
		return (err("Hearts are too many for the screen"));
	margin = (cub3d->img->width - heart_area) / 2;
	while (++i < HEARTS)
	{
		cub3d->hearts[i].full.pos.x = margin + (width + HEART_GAP) * i;
		cub3d->hearts[i].full.pos.y = cub3d->img->height * 0.95 - height;
		cub3d->hearts[i].empty.pos.x = margin + (width + HEART_GAP) * i;
		cub3d->hearts[i].empty.pos.y = cub3d->img->height * 0.95 - height;
	}
	return (SUCCESS);
}

static int	put_images_to_window(cub3d_t *cub3d)
{
	int	i;

	i = -1;
	while (++i < HEARTS)
	{
		if (mlx_image_to_window(cub3d->mlx, cub3d->hearts[i].full.img,
				cub3d->hearts[i].full.pos.x, cub3d->hearts[i].full.pos.y) < 0)
			return (err("Failed to create heart image"));
		if (mlx_image_to_window(cub3d->mlx, cub3d->hearts[i].empty.img,
				cub3d->hearts[i].empty.pos.x, cub3d->hearts[i].empty.pos.y) < 0)
			return (err("Failed to create heart image"));
	}
	return (SUCCESS);
}

int	init_hearts(cub3d_t *cub3d)
{
	load_png(cub3d);
	if (!init_images(cub3d))
		return (FAIL);
	if (!set_positions(cub3d))
		return (FAIL);
	if (!put_images_to_window(cub3d))
		return (FAIL);
	disable_hearts(cub3d);
	return (SUCCESS);
}