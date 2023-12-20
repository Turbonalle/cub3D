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

static int	get_distance_from_edge(mlx_image_t *img, unsigned int row, unsigned int column)
{
	int	distance_from_edge;

	distance_from_edge = row;
	distance_from_edge = min(distance_from_edge, img->height - row);
	distance_from_edge = min(distance_from_edge, column);
	distance_from_edge = min(distance_from_edge, img->width - column);
	return (distance_from_edge);
}

static int	get_time_fade(halo_t *halo)
{
	int	fade;

	fade = (mlx_get_time() - halo->timestamp) * 100 / HALO_TIME;
	return (fade);
}

static void	draw_halo(mlx_image_t *img, halo_t *halo)
{
	unsigned int	column;
	unsigned int	row;
	int				time_fade;
	int				edge_fade;
	int				distance_from_edge;
	int				fade;
	int				color;

	time_fade = get_time_fade(halo);
	row = -1;
	while (++row < img->height)
	{
		column = -1;
		while (++column < img->width)
		{
			distance_from_edge = get_distance_from_edge(img, row, column);
			if (distance_from_edge < HALO_THICKNESS)
				edge_fade = distance_from_edge * 100 / HALO_THICKNESS;
			else
				edge_fade = 100;
			color = halo->color;
			if (time_fade + edge_fade > 100)
				fade = 100;
			else
				fade = time_fade + edge_fade;
			color = set_transparency(color, fade);
			if (distance_from_edge < HALO_THICKNESS)
				mlx_put_pixel(img, column, row, color);
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