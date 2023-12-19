#include "../incl/cub3d.h"

void	init_halo(cub3d_t *cub3d, halo_t *halo)
{
	halo->img = mlx_new_image(cub3d->mlx, cub3d->img->width, cub3d->img->height);
	if (!halo->img || (mlx_image_to_window(cub3d->mlx, halo->img, 0, 0) < 0))
		err("Failed to create halo image");
	halo->img->instances[0].enabled = FALSE;
	halo->active = FALSE;
	halo->color = 0;
	halo->timestamp = 0;
}

void	activate_halo(halo_t *halo, int color)
{
	halo->img->instances[0].enabled = TRUE;
	halo->active = TRUE;
	halo->color = color;
	halo->timestamp = mlx_get_time();
}

static void	set_halo_fade(halo_t *halo)
{
	int	fade;

	fade = (mlx_get_time() - halo->timestamp) * 100 / HALO_TIME;
	halo->color = set_transparency(halo->color, fade);
}

static void	draw_halo(mlx_image_t *img, halo_t *halo)
{
	unsigned int	column;
	unsigned int	row;

	set_halo_fade(halo);
	row = -1;
	while (++row < img->height)
	{
		column = -1;
		while (++column < img->width)
		{
			if (row < HALO_THICKNESS
				|| row > img->height - HALO_THICKNESS
				|| column < HALO_THICKNESS
				|| column > img->width - HALO_THICKNESS)
				mlx_put_pixel(img, column, row, halo->color);
		}
	}
}

static int	halo_is_active(halo_t *halo)
{
	return (mlx_get_time() - halo->timestamp < HALO_TIME);
}

void	handle_halo(halo_t *halo)
{
	if (halo->active)
	{
		if (halo_is_active(halo))
			draw_halo(halo->img, halo);
		else
		{
			halo->img->instances[0].enabled = FALSE;
			halo->active = FALSE;
		}
	}
}