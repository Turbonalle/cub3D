/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsorted_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:31:32 by slampine          #+#    #+#             */
/*   Updated: 2024/01/18 09:48:24 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

int	set_records(t_cub3d *cub3d, t_level *level, char **line, int fd)
{
	char	*name;
	int		time;

	while (*line && **line != '\n')
	{
		if (!get_record_time(*line, &time))
			return (err("Failed to get time string"));
		if (!get_record_name(*line, &name))
			return (err("Failed to get name string"));
		add_record(cub3d, &level->records, time, name);
		free(*line);
		*line = get_next_line(fd);
	}
	return (SUCCESS);
}
