/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   records.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 14:00:47 by slampine          #+#    #+#             */
/*   Updated: 2024/01/18 09:49:06 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	delete_last_record(t_cub3d *cub3d, mlx_t *mlx, t_record **records)
{
	t_record	*ptr;
	t_record	*prev;

	ptr = *records;
	while (ptr->next)
	{
		prev = ptr;
		ptr = ptr->next;
	}
	prev->next = NULL;
	if (cub3d->state != STATE_START)
	{
		mlx_delete_image(mlx, ptr->text_name);
		mlx_delete_image(mlx, ptr->text_time);
	}
	free_record(ptr);
}

int	record_is_top(t_record **records, t_record *new, int time)
{
	if (!*records)
	{
		*records = new;
		return (SUCCESS);
	}
	if (time < (*records)->time)
	{
		new->next = *records;
		*records = new;
		return (SUCCESS);
	}
	return (FAIL);
}

void	delete_extra_records(t_cub3d *cub3d, t_record **records)
{
	int			i;

	i = count_records(*records);
	while (i > cub3d->leaderboard.n_entries)
	{
		delete_last_record(cub3d, cub3d->mlx, records);
		i = count_records(*records);
	}
}

int	add_record(t_cub3d *cub3d, t_record **records, int time, char *name)
{
	t_record	*new;
	t_record	*temp;
	int			i;

	new = new_record(time, name);
	if (!new)
		return (err("Failed to malloc new record"));
	if (record_is_top(records, new, time))
		return (SUCCESS);
	temp = *records;
	i = 0;
	while (temp->next && temp->next->time < time
		&& ++i < cub3d->leaderboard.n_entries)
		temp = temp->next;
	if (i > cub3d->leaderboard.n_entries)
		free_record(new);
	if (temp->next)
	{
		new->next = temp->next;
		temp->next = new;
	}
	else
		temp->next = new;
	delete_extra_records(cub3d, records);
	return (SUCCESS);
}

int	read_records(t_cub3d *cub3d)
{
	char	*line;
	int		fd;
	int		i;

	fd = open(RECORD_FILE, O_RDONLY);
	if (fd < 0)
		return (!free_all(cub3d, -1));
	i = 0;
	line = get_next_line(fd);
	while (line && ++i < cub3d->n_levels + 1)
	{
		if (!set_records(cub3d, &cub3d->levels[i], &line, fd))
		{
			free(line);
			return (!free_all(cub3d, -1));
		}
		if (line && *line == '\n')
		{
			free(line);
			line = get_next_line(fd);
		}
	}
	free(line);
	close(fd);
	return (SUCCESS);
}
