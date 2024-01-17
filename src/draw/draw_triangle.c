/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_triangle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbagger <jbagger@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 13:26:32 by jbagger           #+#    #+#             */
/*   Updated: 2024/01/17 13:26:50 by jbagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	fill_bottom_flat_triangle(mlx_image_t *img, triangle_t *triangle,
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
		draw_line(img, (dvector_t){curx1, scanline_y},
			(dvector_t){curx2, scanline_y}, color);
		curx1 += invslope1;
		curx2 += invslope2;
		scanline_y++;
	}
}

void	fill_top_flat_triangle(mlx_image_t *img, triangle_t *triangle,
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
			draw_line(img, (dvector_t){curx1, scanline_y},
				(dvector_t){curx2, scanline_y}, color);
		curx1 -= invslope1;
		curx2 -= invslope2;
		scanline_y--;
	}
}

void	swap_dvectors(dvector_t *v1, dvector_t *v2)
{
	dvector_t	tmp;

	tmp = *v1;
	*v1 = *v2;
	*v2 = tmp;
}

void	sort_vertices_ascending_by_y(triangle_t *triangle)
{
	if (triangle->a.y > triangle->b.y)
		swap_dvectors(&triangle->a, &triangle->b);
	if (triangle->a.y > triangle->c.y)
		swap_dvectors(&triangle->a, &triangle->c);
	if (triangle->b.y > triangle->c.y)
		swap_dvectors(&triangle->b, &triangle->c);
}

void	draw_filled_triangle(mlx_image_t *img, triangle_t *triangle, int color)
{
	dvector_t	v4;
	triangle_t	top;
	triangle_t	bottom;

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
