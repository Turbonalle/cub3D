/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 20:46:43 by vvagapov          #+#    #+#             */
/*   Updated: 2024/01/15 21:15:06 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	copy_pixel(mlx_image_t *img, uvector_t res, mlx_texture_t *texture,
	uvector_t src)
{
	ft_memcpy(img->pixels + res.row * img->width * 4 + res.col * 4,
		texture->pixels + src.row * texture->width * 4 + src.col * 4,
		4);
}

void	empty_image(mlx_image_t *img)
{
	ft_memset(img->pixels, 0, img->width * img->height * 4);
}

void	set_src_coordinates(uvector_t *src, uvector_t res, double factor,
	mlx_texture_t *texture)
{
	src->row = (uint32_t)round(res.row / factor);
	if (src->row >= texture->height)
		src->row--;
	src->col = (uint32_t)round(res.col / factor);
	if (src->col >= texture->width)
		src->col--;
}

int	get_ray_index(double pos_screen_x, mlx_texture_t *texture,
	double factor, uvector_t res)
{
	return ((int)(pos_screen_x - texture->width * factor * 0.5 + res.col));
}

int	column_visible(cub3d_t *cub3d, double distance_to_entity,
	int ray_index)
{
	return (ray_index >= 0
		&& ray_index < WIDTH
		&& cub3d->rays[ray_index].length > distance_to_entity
	);
}
