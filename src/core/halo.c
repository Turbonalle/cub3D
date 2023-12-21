#include "../incl/cub3d.h"

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

static int	set_edge_fade(int distance_from_edge)
{
	int	edge_fade;

	if (distance_from_edge < HALO_THICKNESS)
		edge_fade = distance_from_edge * 100 / HALO_THICKNESS;
	else
		edge_fade = 100;
	return (edge_fade);
}

static int	set_fade(int time_fade, int edge_fade)
{
	int	fade;

	if (time_fade + edge_fade > 100)
		fade = 100;
	else
		fade = time_fade + edge_fade;
	return (fade);
}

void	draw_halo(mlx_image_t *img, halo_t *halo)
{
	unsigned int	column;
	unsigned int	row;
	int				time_fade;
	int				distance_from_edge;
	int				color;

	time_fade = get_time_fade(halo);
	row = -1;
	while (++row < img->height)
	{
		column = -1;
		while (++column < img->width)
		{
			distance_from_edge = get_distance_from_edge(img, row, column);
			color = halo->color;
			color = set_transparency(color, set_fade(time_fade,
						set_edge_fade(distance_from_edge)));
			if (distance_from_edge < HALO_THICKNESS)
				mlx_put_pixel(img, column, row, color);
		}
	}
}
