/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_elements.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 09:09:08 by slampine          #+#    #+#             */
/*   Updated: 2023/11/20 09:09:10 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

int all_elements_found(int *element_found)
{
	int i;

	i = -1;
	while (++i < 6)
	{
		if (!element_found[i])
			return (FAIL);
	}
	return (SUCCESS);
}

int get_element(level_t *level, int element, char **info)
{
	if (level->element_found[element])
		return (free_info(info), err("Duplicate element found"));
	level->element_found[element] = 1;
	if (element == F || element == C)
		return (get_color(level, element, info));
	else
		return (get_texture(level, element, info));
}

int	find_element(level_t *level, char *line)
{
	char	**info;

	info = ft_split(line, ' ');
	if (!info || !info[0] || !info[1])
		return (FAIL);
	if (ft_strcmp(info[0], "NO") == 0)
		return (get_element(level, NO, info));
	else if (ft_strcmp(info[0], "SO") == 0)
		return (get_element(level, SO, info));
	else if (ft_strcmp(info[0], "WE") == 0)
		return (get_element(level, WE, info));
	else if (ft_strcmp(info[0], "EA") == 0)
		return (get_element(level, EA, info));
	else if (ft_strcmp(info[0], "F") == 0)
		return (get_element(level, F, info));
	else if (ft_strcmp(info[0], "C") == 0)
		return (get_element(level, C, info));
	return (FAIL);
}

void remove_newline(char *line)
{
	int i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == '\n')
			line[i] = '\0';
	}
}

int get_elements(level_t *level, int fd)
{
	char *line;
	int i;

	i = 0;
	while (i < 6)
		level->element_found[i++] = 0;
	while (!all_elements_found(level->element_found))
	{
		line = get_next_line(fd);
		if (!line)
			return (err("Failed to read map file"));
		if (line[0] == '\n')
		{
			free(line);
			continue ;
		}
		remove_newline(line);
		if (!find_element(level, line))
		{
			free(line);
			return (FAIL);
		}
		free(line);
	}
	return (SUCCESS);
}
