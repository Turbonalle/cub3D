/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_level_texture.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 09:09:17 by slampine          #+#    #+#             */
/*   Updated: 2023/12/22 14:49:15 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

int get_texture(level_t *level, int element, char **info)
{
	level->texture[element].path = ft_strdup(info[1]);
	free_info(info);
	if (!level->texture[element].path)
		return (err("Failed to allocate memory"));
	return (SUCCESS);
}
