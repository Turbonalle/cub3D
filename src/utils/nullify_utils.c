/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nullify_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 08:57:54 by slampine          #+#    #+#             */
/*   Updated: 2024/01/18 09:40:00 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	nullify_png(t_png *png)
{
	png->img = NULL;
	png->texture = NULL;
}

void	nullify_texture(t_texture *texture)
{
	texture->path = NULL;
	texture->texture = NULL;
}
