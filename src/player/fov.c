/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fov.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 09:09:23 by slampine          #+#    #+#             */
/*   Updated: 2024/01/18 09:45:51 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	increase_fov(t_cub3d *cub3d)
{
	cub3d->fov += FOV_INCREMENT;
	if (cub3d->fov > FOV_MAX)
		cub3d->fov = FOV_MAX;
}

void	decrease_fov(t_cub3d *cub3d)
{
	cub3d->fov -= FOV_INCREMENT;
	if (cub3d->fov < FOV_MIN)
		cub3d->fov = FOV_MIN;
}
