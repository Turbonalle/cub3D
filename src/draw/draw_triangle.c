/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_triangle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 13:26:32 by jbagger           #+#    #+#             */
/*   Updated: 2024/01/18 09:53:25 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	fill_bottom_flat_triangle(mlx_image_t *img, t_triangle *triangle,
	int color)
{
	float	invslope1;
	float	invslope2;
	float	curx1;
	float	curx2;
	int		scanline_y;

	curx1 = triangle->a.x;
	curx2 = triangle->a.x;
	invslope2 = (triangle->c.x - triangle->a.x)
		/ (triangle->c.y - triangle->a.y);
	invslope1 = (triangle->b.x - triangle->a.x)
		/ (triangle->b.y - triangle->a.y);
	scanline_y = triangle->a.y;
	while (scanline_y <= triangle->b.y && scanline_y < (int)img->height)
	{
		draw_line(img, (t_dvector){curx1, scanline_y},
			(t_dvector){curx2, scanline_y}, color);
		curx1 += invslope1;
		curx2 += invslope2;
		scanline_y++;
	}
}

void	fill_top_flat_triangle(mlx_image_t *img, t_triangle *triangle,
	int color)
{
	float	invslope1;
	float	invslope2;
	float	curx1;
	float	curx2;
	int		scanline_y;

	invslope1 = (triangle->c.x - triangle->a.x)
		/ (triangle->c.y - triangle->a.y);
	invslope2 = (triangle->c.x - triangle->b.x)
		/ (triangle->c.y - triangle->b.y);
	curx1 = triangle->c.x;
	curx2 = triangle->c.x;
	scanline_y = triangle->c.y;
	while (scanline_y > triangle->a.y)
	{
		if (scanline_y < (int)img->height)
			draw_line(img, (t_dvector){curx1, scanline_y},
				(t_dvector){curx2, scanline_y}, color);
		curx1 -= invslope1;
		curx2 -= invslope2;
		scanline_y--;
	}
}

void	swap_dvectors(t_dvector *v1, t_dvector *v2)
{
	t_dvector	tmp;

	tmp = *v1;
	*v1 = *v2;
	*v2 = tmp;
}

void	sort_vertices_ascending_by_y(t_triangle *triangle)
{
	if (triangle->a.y > triangle->b.y)
		swap_dvectors(&triangle->a, &triangle->b);
	if (triangle->a.y > triangle->c.y)
		swap_dvectors(&triangle->a, &triangle->c);
	if (triangle->b.y > triangle->c.y)
		swap_dvectors(&triangle->b, &triangle->c);
}

void	draw_filled_triangle(mlx_image_t *img, t_triangle *triangle, int color)
{
	t_dvector	v4;
	t_triangle	top;
	t_triangle	bottom;

	sort_vertices_ascending_by_y(triangle);
	if (triangle->b.y == triangle->c.y)
		fill_bottom_flat_triangle(img, triangle, color);
	else if (triangle->a.y == triangle->b.y)
		fill_top_flat_triangle(img, triangle, color);
	else
	{
		v4.x = triangle->a.x + ((triangle->b.y - triangle->a.y)
				/ (triangle->c.y - triangle->a.y))
			* (triangle->c.x - triangle->a.x);
		v4.y = triangle->b.y;
		top.a = triangle->a;
		top.b = triangle->b;
		top.c = v4;
		bottom.a = triangle->b;
		bottom.b = v4;
		bottom.c = triangle->c;
		fill_bottom_flat_triangle(img, &top, color);
		fill_top_flat_triangle(img, &bottom, color);
	}
}
