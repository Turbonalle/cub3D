#include "../incl/cub3d.h"

static void load_png(cub3d_t *cub3d)
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
		cub3d->hearts[i].full.img = mlx_texture_to_image(cub3d->mlx, cub3d->hearts[i].full.texture);
		if (!cub3d->hearts[i].full.img)
			return (err("Failed to create heart image"));
		cub3d->hearts[i].empty.img = mlx_texture_to_image(cub3d->mlx, cub3d->hearts[i].empty.texture);
		if (!cub3d->hearts[i].empty.img)
			return (err("Failed to create heart image"));
	}
	return (SUCCESS);
}

static void	set_positions(cub3d_t *cub3d)
{
	int		i;
	int		gap;
	int		margin;
	int		width;
	int		height;

	i = -1;
	gap = HEART_GAP;
	width = cub3d->hearts[0].full.texture->width;
	height = cub3d->hearts[0].full.texture->height;
	margin = (cub3d->img->width - (width * HEARTS + gap * (HEARTS - 1))) / 2;
	while (++i < HEARTS)
	{
		cub3d->hearts[i].full.pos.x = margin + (width + gap) * i;
		cub3d->hearts[i].full.pos.y = cub3d->img->height * 0.95 - height;
		cub3d->hearts[i].empty.pos.x = margin + (width + gap) * i;
		cub3d->hearts[i].empty.pos.y = cub3d->img->height * 0.95 - height;
	}
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
	set_positions(cub3d);
	if (!put_images_to_window(cub3d))
		return (FAIL);
	disable_hearts(cub3d);
	return (SUCCESS);
}