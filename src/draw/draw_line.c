#include "../incl/cub3d.h"

void bresenham_low_slope(mlx_image_t *img, vector_t start, vector_t end, int color)
{
	vector_t delta;
	vector_t pixel;
	int yi;
	int D;

	delta.x = end.x - start.x;
	delta.y = end.y - start.y;
	yi = 1;
	if (delta.y < 0)
	{
		yi = -1;
		delta.y = -delta.y;
	}
	D = (2 * delta.y) - delta.x;
	pixel.x = start.x;
	pixel.y = start.y;
	while (pixel.x <= end.x)
	{
		if (pixel.x >= 0 && pixel.x < (int)img->width && pixel.y >= 0 && pixel.y < (int)img->height)
			mlx_put_pixel(img, pixel.x, pixel.y, color);
		else
		{
			printf("bresenham_low_slope FAIL!\n");
			printf("pixel.x: %d\n", pixel.x);
			printf("pixel.y: %d\n", pixel.y);
		}
		if (D > 0)
		{
			pixel.y = pixel.y + yi;
			D = D + (2 * (delta.y - delta.x));
		}
		else
			D = D + 2 * delta.y;
		pixel.x++;
	}
}

void bresenham_high_slope(mlx_image_t *img, vector_t start, vector_t end, int color)
{
	vector_t	delta;
	vector_t	pixel;
	int			xi;
	int			D;

	delta.x = end.x - start.x;
	delta.y = end.y - start.y;
	xi = 1;
	if (delta.x < 0)
	{
		xi = -1;
		delta.x = -delta.x;
	}
	D = (2 * delta.x) - delta.y;
	pixel.y = start.y;
	pixel.x = start.x;
	while (pixel.y <= end.y)
	{
		if (pixel.x >= 0 && pixel.x < (int)img->width && pixel.y >= 0 && pixel.y < (int)img->height)
			mlx_put_pixel(img, pixel.x, pixel.y, color);
		else
		{
			printf("bresenham_high_slope FAIL!\n");
			printf("pixel.x: %d\n", pixel.x);
			printf("pixel.y: %d\n", pixel.y);
		}
		if (D > 0)
		{
			pixel.x = pixel.x + xi;
			D = D + (2 * (delta.x - delta.y));
		}
		else
			D = D + 2 * delta.x;
		pixel.y++;
	}
}

void	draw_line(mlx_image_t *img, dvector_t start_d, dvector_t end_d, int color)
{
	vector_t	start;
	vector_t	end;

	start.x = start_d.x;
	start.y = start_d.y;
	end.x = end_d.x;
	end.y = end_d.y;
	if (start.x < 0 || start.x >= (int)img->width || end.y < 0 || end.y >= (int)img->height)
	{
		printf("draw_line FAIL!\n");
		printf("start.x: %d\n", start.x);
		printf("start.y: %d\n", start.y);
		printf("end.x: %d\n", end.x);
		printf("end.y: %d\n", end.y);
		return ;
	}
	if (abs(end.y - start.y) < abs(end.x - start.x))
	{
		if (start.x > end.x)
			bresenham_low_slope(img, end, start, color);
		else
			bresenham_low_slope(img, start, end, color);
	}
	else
	{
		if (start.y > end.y)
			bresenham_high_slope(img, end, start, color);
		else
			bresenham_high_slope(img, start, end, color);
	}
}

void	draw_vertical_line(mlx_image_t *img, dvector_t start, dvector_t end, int color)
{
	while (start.y <= end.y)
	{
		mlx_put_pixel(img, start.x, start.y, color);
		start.y++;
	}
}

texture_t	find_texture(cub3d_t *cub3d, ray_t ray)
{
	texture_t	texture;

	if (ray.wall == NO)
		texture = cub3d->level->texture[0];
	if (ray.wall == SO)
		texture = cub3d->level->texture[1];
	if (ray.wall == EA)
		texture = cub3d->level->texture[2];
	if (ray.wall == WE)
		texture = cub3d->level->texture[3];
	return (texture);
}

void	draw_textured_line(cub3d_t *cub3d, dvector_t start, dvector_t end, ray_t ray)
{
	texture_t	texture;
	int			y;
	int			src_x;
	int			src_y;
	int			dst_x;
	int			dst_y;
	int			y_count;
	uint32_t	color;
	int			src_i;

	texture = find_texture(cub3d, ray);
	y_count = round(end.y) - round(start.y);
	y = 0;
	while (y <= y_count)
	{
		dst_x = start.x;
		dst_y = start.y + y;
		src_x = fmod(ray.end.x, 1.0) * texture.texture->width;
		if (ray.wall == NO)
			src_x = texture.texture->width - src_x;
		src_y = y * texture.texture->height / (end.y - start.y);
		src_i = round(src_y * texture.texture->width * 4 + src_x * 4);
		color = texture.texture->pixels[src_i];
		color = color << 8;
		color += texture.texture->pixels[src_i + 1];
		color = color << 8;
		color += texture.texture->pixels[src_i + 2];
		color = color << 8;
		color += texture.texture->pixels[src_i + 3];
		mlx_put_pixel(cub3d->img, dst_x, dst_y, color);
		y++;
	}
}
