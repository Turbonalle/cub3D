#include "../incl/cub3d.h"

void	delete_last_record(cub3d_t *cub3d, mlx_t *mlx, record_t **records)
{
	record_t	*ptr;
	record_t	*prev;

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

int	add_record(cub3d_t *cub3d, record_t **records, int time, char *name)
{
	record_t	*new;
	record_t	*temp;
	int			i;

	new = new_record(time, name);
	if (!new)
		return (err("Failed to malloc new record"));
	
	// if no records yet
	if (!*records)
	{
		*records = new;
		return (SUCCESS);
	}

	// if new record is better than the first record
	if (time < (*records)->time)
	{
		new->next = *records;
		*records = new;
		return (SUCCESS);
	}

	temp = *records;
	i = 1;
	while (temp->next && temp->next->time < time && i < cub3d->leaderboard.n_entries)
	{
		temp = temp->next;
		i++;
	}
	if (i > cub3d->leaderboard.n_entries)		// if new record is worse than the last record
	{
		free_record(new);
	}
	if (temp->next) 	// if new record is better than a record in the middle
	{
		new->next = temp->next;
		temp->next = new;
	}
	else					// if new record is better than the last record
		temp->next = new;
	i = count_records(*records);
	while (i > cub3d->leaderboard.n_entries)
	{
		delete_last_record(cub3d, cub3d->mlx, records);
		i = count_records(*records);
	}
	return (SUCCESS);
}

int	set_records(cub3d_t *cub3d, level_t *level, char **line, int fd)
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

int	read_records(cub3d_t *cub3d)
{
	char	*line;
	int		fd;
	int		i;

	//TODO: remove levels parameter
	fd = open(RECORD_FILE, O_RDONLY);
	if (fd < 0)
	{
		free_all(cub3d, -1);
		return (err("Failed to open records file"));
	}
	i = 0;
	line = get_next_line(fd);
	while (line && ++i < cub3d->n_levels + 1)
	{
		if (!set_records(cub3d, &cub3d->levels[i], &line, fd))
		{
			free_all(cub3d, -1);
			free(line);
			return (err("Failed to set records"));
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
