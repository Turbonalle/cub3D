/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_level_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 09:09:07 by slampine          #+#    #+#             */
/*   Updated: 2024/01/18 09:48:24 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	set_color(t_level *level, int element, int color)
{
	if (element == F)
		level->floor_color = color;
	else if (element == C)
		level->ceiling_color = color;
}

int	color_comma_checker(char *info)
{
	int	i;
	int	comma;

	if (info[0] == ',')
		return (err("Color: Comma before first number"));
	i = -1;
	comma = 0;
	while (info[++i])
	{
		if (info[i] == ',')
			comma++;
		if (info[i] != ',')
			comma = 0;
		if (comma > 1)
			return (err("Color: Consecutive commas"));
	}
	if (info[i - 1] == ',')
		return (err("Color: Comma after last number"));
	return (SUCCESS);
}

int	get_color(t_level *level, int element, char **info)
{
	int		i;
	int		color_part;
	int		color;
	char	**rgb;

	rgb = ft_split(info[1], ',');
	free_info(info);
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
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
