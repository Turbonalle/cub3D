/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_level_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 09:09:07 by slampine          #+#    #+#             */
/*   Updated: 2024/01/11 15:43:04 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	set_color(level_t *level, int element, int color)
{
	if (element == F)
		level->floor_color = color;
	else if (element == C)
		level->ceiling_color = color;
}

int	get_color(level_t *level, int element, char **info)
{
	int		i;
	int		color_part;
	int		color;
	char	**rgb;

	rgb = ft_split(info[1], ',');
	free_info(info);
	if (!rgb || !rgb[2] || rgb[3])
		return (free_info(rgb), err("Color: Wrong amount of arguments"));
	color = 0;
	i = -1;
	while (++i < 3)
	{
		if (!all_digits(rgb[i]))
			return (free_info(rgb), err("Color: Only digits allowed"));
		color_part = ft_atoi(rgb[i]);
		if (color_part < 0 || color_part > 255)
			return (free_info(rgb), err("Color: Invalid value"));
		color = (color << 8) + color_part;
	}
	color = (color << 8) + 255;
	set_color(level, element, color);
	free_info(rgb);
	return (SUCCESS);
}
