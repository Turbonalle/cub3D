/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 20:46:43 by vvagapov          #+#    #+#             */
/*   Updated: 2024/01/18 09:45:51 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	copy_pixel(mlx_image_t *img, t_uvector res, mlx_texture_t *texture,
	t_uvector src)
{
	ft_memcpy(img->pixels + res.row * img->width * 4 + res.col * 4,
		texture->pixels + src.row * texture->width * 4 + src.col * 4,
		4);
}

void	empty_image(mlx_image_t *img)
{
	ft_memset(img->pixels, 0, img->width * img->height * 4);
}

void	set_src_coordinates(t_uvector *src, t_uvector res, double factor,
	mlx_texture_t *texture)
{
	src->row = (uint32_t)round(res.row / factor);
	if (src->row >= texture->height)
		src->row--;
	src->col = (uint32_t)round(res.col / factor);
	if (src->col >= texture->width)
		src->col--;
}

int	get_ray_i(double pos_screen_x, mlx_texture_t *texture,
	double factor, t_uvector res)
{
	return ((int)(pos_screen_x - texture->width * factor * 0.5 + res.col));
}

int	column_visible(t_cub3d *cub3d, double distance_to_entity,
	int ray_index)
{
	return (ray_index >= 0
		&& ray_index < WIDTH
		&& cub3d->rays[ray_index].length > distance_to_entity
	);
}
