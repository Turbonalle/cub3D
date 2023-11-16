/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 14:01:53 by slampine          #+#    #+#             */
/*   Updated: 2023/11/16 14:07:30 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

int	get_texture(cub3d_t *cub3d, int element, char **info)
{
	cub3d->texture[element].path = ft_strdup(info[1]);
	free_info(info);
	if (!cub3d->texture[element].path)
		return (err("Failed to allocate memory"));
	return (SUCCESS);
}
