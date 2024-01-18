/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 15:58:41 by slampine          #+#    #+#             */
/*   Updated: 2024/01/18 11:15:34 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

int	read_map(t_level *level, char *map_path)
{
	int	fd;

	fd = open(map_path, O_RDONLY);
	if (fd < 0)
		return (close(fd), err("Failed to open map file"));
	level->nodes = null_textures(level);
	if (!get_elements(level, fd))
		return (free_delete_textures(level), FAIL);
	if (!all_elements_found(level->element_found))
		return (close(fd), err("Missing element(s) in map file"));
	if (!get_map(level, fd))
	{
		free_delete_textures(level);
		free_list(level->map_list);
		return (close(fd), free_info(level->map), FAIL);
	}
	close(fd);
	return (SUCCESS);
}

int	copy_array(char **src, char **dst)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dst[i] = ft_strdup(src[i]);
		if (!dst[i])
		{
			free_info(dst);
			return (FAIL);
		}
		i++;
	}
	return (SUCCESS);
}

int	free_map_helper(t_level *level, int i)
{
	free_delete_textures(level);
	free_list(level->map_list);
	if (i == 0)
		free_info(level->map);
	if (i == 1)
		free_info(level->backup);
	if (i == 2)
	{
		free_info(level->map);
		free_info(level->backup);
	}
	return (FAIL);
}
