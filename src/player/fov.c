/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fov.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 14:27:33 by slampine          #+#    #+#             */
/*   Updated: 2023/11/15 14:46:05 by slampine         ###   ########.fr       */
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
