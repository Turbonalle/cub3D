/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_textured_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbagger <jbagger@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 14:44:02 by jbagger           #+#    #+#             */
/*   Updated: 2024/01/17 15:01:18 by jbagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

uint32_t	get_pixel_color(texture_t texture, vector_t src)
{
	uint32_t	color;
	int			src_i;

	src_i = src.y * texture.texture->width * 4 + src.x * 4;
	color = texture.texture->pixels[src_i];
	color = color << 8;
	color += texture.texture->pixels[src_i + 1];
	color = color << 8;
	color += texture.texture->pixels[src_i + 2];
	color = color << 8;
	color += texture.texture->pixels[src_i + 3];
	return (color);
}

static void	set_src_x(vector_t *src, ray_t ray, texture_t texture)
{
	src->x = fmod(ray.end.y, 1.0) * texture.texture->width;
	if (ray.wall == NO || ray.wall == SO || (ft_strchr("ABCDOG", ray.wall)
			&& (ray.door_dir == NO || ray.door_dir == SO)))
		src->x = fmod(ray.end.x, 1.0) * texture.texture->width;
	if (ray.wall == NO || ray.wall == EA || (ft_strchr("ABCDOG", ray.wall)
			&& (ray.door_dir == NO || ray.door_dir == EA)))
		src->x = texture.texture->width - src->x - 1;
}

void	draw_textured_line_close(cub3d_t *cub3d, dvector_t start, dvector_t end,
	ray_t ray)
{
	texture_t	texture;
	vector_t	src;
	int			y;
	double		wall_height;
	double		src_start;

	texture = find_texture(cub3d, ray);
	y = 0;
	set_src_x(&src, ray, texture);
	while (y < (int)cub3d->img->height)
	{
		wall_height = end.y - start.y;
		src_start = (wall_height - cub3d->img->height) / 2
			* (texture.texture->height / wall_height);
		src.y = round(src_start + (y * texture.texture->height
					/ wall_height) - 0.4999);
		if (src.y > (int)texture.texture->height - 1)
			src.y = (int)texture.texture->height - 1;
		if (src.y < 0)
			src.y = 0;
		mlx_put_pixel(cub3d->img, (int)start.x, y,
			get_pixel_color(texture, src));
		y++;
	}
}

void	draw_textured_line(cub3d_t *cub3d, dvector_t start, dvector_t end,
	ray_t ray)
{
	texture_t	texture;
	uint32_t	color;
	vector_t	src;
	int			y;

	texture = find_texture(cub3d, ray);
	y = round(start.y);
	set_src_x(&src, ray, texture);
	while (y < end.y)
	{
		src.y = round((y - start.y) * texture.texture->height
				/ (end.y - start.y) - 0.4999);
		if (src.y > (int)texture.texture->height - 1)
			src.y = (int)texture.texture->height - 1;
		if (src.y < 0)
			src.y = 0;
		color = get_pixel_color(texture, src);
		mlx_put_pixel(cub3d->img, (int)start.x, y, color);
		y++;
	}
}
