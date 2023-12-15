#include "../incl/cub3d.h"

void	create_time_string(char *time_str, int time)
{
	if (time <= 0 || time >= 6000000)
	{
		time_str[0] = '0';
		time_str[1] = '0';
		time_str[2] = ':';
		time_str[3] = '0';
		time_str[4] = '0';
		time_str[5] = '.';
		time_str[6] = '0';
		time_str[7] = '0';
	}
	else
	{
		time_str[0] = '0' + time / 600000;
		time_str[1] = '0' + time / 60000 % 10;
		time_str[2] = ':';
		time_str[3] = '0' + time / 10000 % 6;
		time_str[4] = '0' + time / 1000 % 10;
		time_str[5] = '.';
		time_str[6] = '0' + time / 100 % 10;
		time_str[7] = '0' + time / 10 % 10;
	}
	time_str[8] = '\0';
}

record_t *new_record(int time, char* name)
{
	record_t	*new;

	new = malloc(sizeof(record_t));
	if (!new)
		return (NULL);
	new->time = time;
	new->name = name;
	create_time_string(new->time_str, time);
	new->text_name = NULL;
	new->text_time = NULL;
	new->next = NULL;
	return (new);
}

int count_records(record_t *records)
{
	int			count;
	record_t	*ptr;

	count = 0;
	ptr = records;
	while (ptr)
	{
		count++;
		ptr = ptr->next;
	}
	return (count);
}

void	delete_last_record(mlx_t *mlx, record_t **records)
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
	mlx_delete_image(mlx, ptr->text_name);
	mlx_delete_image(mlx, ptr->text_time);
	free_record(ptr);
}

void	set_text_name(cub3d_t *cub3d, record_t *record, int i)
{
	vector_t	pos;
	int			margin;

	margin = cub3d->leaderboard.rect_level[i - 1].height * 0.2;
	pos.x = record->text_time->pos.x + record->text_time->width * 0.5 + margin_x;
	pos.y = record->text_time->pos.y + margin_y + i * (record->text_time->height - 2 * margin_y) / 10;
	record->text_name = mlx_put_string(mlx, record->name, pos.x, pos.y);
}

int	add_record(cub3d_t *cub3d, record_t **records, int time, char* name, int n_entries)
{
	record_t	*new;
	record_t	*temp;
	int			i;

	new = new_record(cub3d, time, name);
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
	while (temp->next && temp->next->time < time && i < n_entries)
	{
		temp = temp->next;
		i++;
	}
	if (i == n_entries)		// if new record is worse than the last record
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
	set_text_name(cub3d, new, i);	// COMPLETE THIS!!!
	set_text_time(cub3d, new, i);	// COMPLETE THIS!!!
	i = count_records(*records);
	while (i > n_entries)
	{
		delete_last_record(cub3d->mlx, records);
		i = count_records(*records);
	}
	return (SUCCESS);
}

int	get_record_time(char *line, int *time)
{
	char	*ptr;

	ptr = line;
	*time = 0;
	while (*ptr && ft_isdigit(*ptr))
	{
		*time = *time * 10 + (*ptr - '0');
		ptr++;
	}
	if (*ptr != ' ')
		return (FAIL);
	return (SUCCESS);
}

int	get_record_name(char *line, char **name)
{
	char	*name_start;
	int		i;

	name_start = ft_strchr(line, ' ');
	if (!name_start)
		return (FAIL);
	name_start++;
	i = 0;
	while (name_start[i] && name_start[i] != '\n')
	{
		if (!ft_isalpha(name_start[i]))
			return (FAIL);
		i++;
	}
	if (i == 0 || i > MAX_NAME_LENGTH || (name_start[i] != '\n' && name_start[i] != '\0'))
		return (FAIL);
	*name = ft_substr(line, name_start - line, i);
	if (!*name)
		return (FAIL);
	return (SUCCESS);
}

int	set_records(mlx_t *mlx, level_t *level, char **line, int n_entries, int fd)
{
	char	*name;
	int		time;

	while (*line && **line != '\n')
	{
		if (!get_record_time(*line, &time))
			return (err("Failed to get time string"));
		if (!get_record_name(*line, &name))
			return (err("Failed to get name string"));
		add_record(mlx, &level->records, time, name, n_entries);
		free(*line);
		*line = get_next_line(fd);
	}
	return (SUCCESS);
}

int	read_records(cub3d_t *cub3d, level_t *levels)
{
	char	*line;
	int		fd;
	int		i;

	(void)levels;
	fd = open("assets/records.txt", O_RDONLY);
	if (fd < 0)
		return (err("Failed to open records file"));
	i = 0;
	line = get_next_line(fd);
	while (line && ++i < cub3d->n_levels)
	{
		if (!set_records(cub3d, &cub3d->levels[i], &line, cub3d->leaderboard.n_entries, fd))
			return (err("Failed to set records"));
		if (line && *line == '\n')
		{
			free(line);
			line = get_next_line(fd);
		}
	}
	close(fd);
	return (SUCCESS);
}
