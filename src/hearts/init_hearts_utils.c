#include "../incl/cub3d.h"

int	load_heart_png(cub3d_t *cub3d)
{
	int	i;

	i = -1;
	while (++i < HEARTS)
	{
		cub3d->hearts[i].full.texture = mlx_load_png(HEART_FULL_PNG);
		if (!cub3d->hearts[i].full.texture)
		{
			delete_full_heart_texture(cub3d, i);
			return (FAIL);
		}
	}
	i = -1;
	while (++i < HEARTS)
	{
		cub3d->hearts[i].empty.texture = mlx_load_png(HEART_EMPTY_PNG);
		if (!cub3d->hearts[i].empty.texture)
		{
			delete_full_heart_texture(cub3d, HEARTS);
			delete_empty_heart_texture(cub3d, i);
			return (FAIL);
		}
	}
	return (SUCCESS);
}

int	init_full_hearts(cub3d_t *cub3d)
{
	int	i;

	i = -1;
	while (++i < HEARTS)
	{
		cub3d->hearts[i].full.img
			= mlx_texture_to_image(cub3d->mlx, cub3d->hearts[i].full.texture);
		if (!cub3d->hearts[i].full.img)
		{
			delete_full_heart_texture(cub3d, HEARTS);
			delete_empty_heart_texture(cub3d, HEARTS);
			delete_full_heart_image(cub3d, i);
			return (FAIL);
		}
	}
	return (SUCCESS);
}

int	init_empty_hearts(cub3d_t *cub3d)
{
	int	i;

	i = -1;
	while (++i < HEARTS)
	{
		cub3d->hearts[i].empty.img
			= mlx_texture_to_image(cub3d->mlx, cub3d->hearts[i].empty.texture);
		if (!cub3d->hearts[i].empty.img)
		{
			delete_full_heart_texture(cub3d, HEARTS);
			delete_empty_heart_texture(cub3d, HEARTS);
			delete_full_heart_image(cub3d, HEARTS);
			delete_empty_heart_image(cub3d, i);
			return (FAIL);
		}
	}
	return (SUCCESS);
}

int	set_heart_positions(cub3d_t *cub3d)
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

int	put_hearts_to_window(cub3d_t *cub3d)
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
