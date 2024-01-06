#include "../incl/cub3d.h"

void	fill_bottom_flat_triangle(mlx_image_t *img, triangle_t *triangle, int color)
{

	float invslope1 = (triangle->b.x - triangle->a.x) / (triangle->b.y - triangle->a.y);
	float invslope2 = (triangle->c.x - triangle->a.x) / (triangle->c.y - triangle->a.y);

	float curx1 = triangle->a.x;
	float curx2 = triangle->a.x;

	for (int scanlineY = triangle->a.y; scanlineY <= triangle->b.y; scanlineY++)
	{
		draw_line(img, (dvector_t){curx1, scanlineY}, (dvector_t){curx2, scanlineY}, color);
		curx1 += invslope1;
		curx2 += invslope2;
	}
}

void	fill_top_flat_triangle(mlx_image_t *img, triangle_t *triangle, int color)
{
	float invslope1 = (triangle->c.x - triangle->a.x) / (triangle->c.y - triangle->a.y);
	float invslope2 = (triangle->c.x - triangle->b.x) / (triangle->c.y - triangle->b.y);

	float curx1 = triangle->c.x;
	float curx2 = triangle->c.x;

	for (int scanlineY = triangle->c.y; scanlineY > triangle->a.y; scanlineY--)
	{
		draw_line(img, (dvector_t){curx1, scanlineY}, (dvector_t){curx2, scanlineY}, color);
		curx1 -= invslope1;
		curx2 -= invslope2;
	}
}

void	swap(dvector_t *v1, dvector_t *v2)
{
	dvector_t tmp;

	tmp = *v1;
	*v1 = *v2;
	*v2 = tmp;
}

void	sort_vertices_ascending_by_y(triangle_t *triangle)
{
	if (triangle->a.y > triangle->b.y)
		swap(&triangle->a, &triangle->b);
	if (triangle->a.y > triangle->c.y)
		swap(&triangle->a, &triangle->c);
	if (triangle->b.y > triangle->c.y)
		swap(&triangle->b, &triangle->c);
}

void	draw_filled_triangle(mlx_image_t *img, triangle_t *triangle, int color)
{
	sort_vertices_ascending_by_y(triangle);

	if (triangle->b.y == triangle->c.y)
		fill_bottom_flat_triangle(img, triangle, color);
	else if (triangle->a.y == triangle->b.y)
    	fill_top_flat_triangle(img, triangle, color);
	else
	{
		dvector_t v4;
		triangle_t top;
		triangle_t bottom;

		v4.x = triangle->a.x + ((triangle->b.y - triangle->a.y) / (triangle->c.y - triangle->a.y)) * (triangle->c.x - triangle->a.x);
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

void	draw_triangle(mlx_image_t *img, triangle_t triangle, int color)
{
	draw_line(img, triangle.a, triangle.b, color);
	draw_line(img, triangle.b, triangle.c, color);
	draw_line(img, triangle.c, triangle.a, color);
}