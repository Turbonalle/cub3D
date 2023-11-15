/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:41:53 by vvagapov          #+#    #+#             */
/*   Updated: 2023/11/14 13:38:28 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cub3d.h"

void	free_info(char **info)
{
	int	i;

	i = -1;
	if (info)
	{
		while (info[++i])
			free(info[i]);
		free(info);
	}
}

void	free_cub3d(cub3d_t *cub3d)
{
	int i;

	i = -1;
	while (++i < 4)
	{
		if (cub3d->texture[i].path)
			free(cub3d->texture[i].path);

		// if (cub3d->texture[i].img)
		// 	free(cub3d->texture[i].img);
	}
	i = -1;
	while (cub3d->map[++i])
		free(cub3d->map[i]);
	if (cub3d->map)
		free(cub3d->map);
}
