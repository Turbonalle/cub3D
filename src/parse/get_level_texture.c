/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_level_texture.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbagger <jbagger@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 09:09:17 by slampine          #+#    #+#             */
/*   Updated: 2024/01/10 13:34:23 by jbagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

int	get_texture(level_t *level, int element, char **info)
{
	level->texture[element].path = ft_strdup(info[1]);
	free_info(info);
	if (!level->texture[element].path)
		return (err("Failed to allocate memory"));
	level->texture[element].texture = mlx_load_png(level->texture[element].path);
	if (!level->texture[element].texture)
		return (err("Failed to load texture"));
	return (SUCCESS);
}
