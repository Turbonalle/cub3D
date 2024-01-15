#include "../incl/cub3d.h"

static void scale_distraction(cub3d_t *cub3d, distraction_t *distraction, mlx_texture_t *src, double factor)
{
	uint32_t	row_src;
	uint32_t	col_src;
	uint32_t	row_res;
	uint32_t	col_res;
	int			ray_index;

	distraction->img_distraction->instances[0].enabled = TRUE;
	ft_memset(distraction->img_distraction->pixels, 0, distraction->img_distraction->width * distraction->img_distraction->height * 4);
	row_res = 0;
	while (row_res < src->height * factor)
	{
		col_res = 0;
		if (row_res < distraction->img_distraction->height)
		{
			while (col_res < src->width * factor)
			{
				if (col_res < distraction->img_distraction->width)
				{
					row_src = (uint32_t)round(row_res / factor);
					if (row_src >= src->height)
						row_src--;
					col_src = (uint32_t)round(col_res / factor);
					if (col_src >= src->width)
						col_src--;
					ray_index = (int)(distraction->pos_screen.x - src->width * factor * 0.5 + col_res);
					if (ray_index >= 0 && ray_index < WIDTH && cub3d->rays[(int)(distraction->pos_screen.x - src->width * factor * 0.5 + col_res)].length > distraction->dist_to_player)
						ft_memcpy(distraction->img_distraction->pixels + row_res * distraction->img_distraction->width * 4 + col_res * 4,
							src->pixels + row_src * src->width * 4 + col_src * 4,
							4);
				}
				col_res++;
			}
		}
		row_res++;
	}
	distraction->img_distraction->instances[0].x = distraction->pos_screen.x - src->width * factor * 0.5;
	distraction->img_distraction->instances[0].y = distraction->pos_screen.y - src->height * factor * 1.5;
}

static void draw_distraction_frame(cub3d_t *cub3d, distraction_t *distraction)
{
	double 			scale_factor;
	mlx_texture_t	*texture;

	scale_factor = calculate_scale_factor(distraction->dist_to_player, DISTRACTION_NORMAL_SCALE_DISTANCE);
	if (distraction->thrown == TRUE)
		texture = cub3d->distraction_thrown_texture;
	else
		texture = cub3d->distraction_texture;
	scale_distraction
	(
		cub3d,
		distraction,
		texture,
		scale_factor
	);
}

void    draw_all_distractions(cub3d_t *cub3d, distraction_t **distractions)
{
	int	i;

	i = 0;
	while (distractions[i])
	{
		draw_distraction_frame(cub3d, distractions[i]);
		i++;
	}
}
