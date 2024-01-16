/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nullify_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 08:57:54 by slampine          #+#    #+#             */
/*   Updated: 2024/01/16 08:57:55 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	nullify_png(png_t *png)
{
	png->img = NULL;
	png->texture = NULL;
}

void	nullify_texture(texture_t *texture)
{
	texture->path = NULL;
	texture->texture = NULL;
}
