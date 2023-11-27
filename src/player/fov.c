/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fov.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 09:09:23 by slampine          #+#    #+#             */
/*   Updated: 2023/11/27 15:29:39 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	increase_fov(cub3d_t *cub3d)
{
	cub3d->fov += FOV_INCREMENT;
	if (cub3d->fov > FOV_MAX)
		cub3d->fov = FOV_MAX;
}

void	decrease_fov(cub3d_t *cub3d)
{
	cub3d->fov -= FOV_INCREMENT;
	if (cub3d->fov < FOV_MIN)
		cub3d->fov = FOV_MIN;
}
