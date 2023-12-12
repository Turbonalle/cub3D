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
	new->next = NULL;
	return (new);
}

int	add_record(record_t **records, int time, char* name, int n_entries)
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
	if ((*records)->time > time)
	{
		new->next = *records;
		*records = new;
		return (SUCCESS);
	}

	temp = *records;
	i = 0;
	while (temp->next && temp->next->time < time && ++i <= n_entries)
		temp = temp->next;
	if (i == n_entries)		// if new record is worse than the last record
		free_record(new);
	else if (temp->next) 	// if new record is better than a record in the middle
	{
		new->next = temp->next;
		temp->next = new;
	}
	else					// if new record is better than the last record
		temp->next = new;
	return (SUCCESS);
}

int	get_record_time(char **buf, int *time)
{
	char	*ptr;

	ptr = *buf;
	*time = 0;
	while (*ptr && *ptr != '\n' && ft_isdigit(*ptr))
	{
		*time = *time * 10 + (*ptr - '0');
		ptr++;
	}
	if (*ptr != ' ')
		return (FAIL);
	*buf = ptr + 1;
	return (SUCCESS);
}

int	get_record_name(char **buf, char **name)
{
	char	*ptr;

	ptr = *buf;
	while (*ptr && *ptr != '\n')
		ptr++;
	*name = ft_substr(*buf, 0, ptr - *buf);
	if (!*name)
		return (FAIL);
	*buf = ptr;
	return (SUCCESS);
}

int	set_records(level_t *level, char **buf, int n_entries)
{
	char	*name;
	int		time;

	while (**buf && **buf != '\n')
	{
		if (!get_record_time(buf, &time))
			return (err("Failed to get time string"));
		if (!get_record_name(buf, &name))
			return (err("Failed to get name string"));
		add_record(&level->records, time, name, n_entries);
		if (**buf == '\n')
			(*buf)++;
		else
			return (err("Invalid record format"));
		if (**buf == '\n')
			break ;
	}
	if (**buf == '\n')
		(*buf)++;
	return (SUCCESS);
}

int	read_records(cub3d_t *cub3d, level_t *levels)
{
	int		fd;
	char	*buf;
	char	*temp;
	int		i;

	(void)levels;
	buf = malloc(sizeof(char) * (2048 + 1));
	if (!buf)
		return (err("Failed to malloc buf"));
	fd = open("assets/records.txt", O_RDONLY);
	if (fd < 0)
		return (free(buf), err("Failed to open records file"));
	int bytes_read = read(fd, buf, 2048);
	if (bytes_read < 0)
		return (free(buf), err("Failed to read records file"));
	buf[bytes_read] = '\0';
	// printf("%s\n", buf);	// DEBUG
	temp = buf;
	i = 0;
	while (*temp && ++i < cub3d->n_levels)
	{
		if (!set_records(&cub3d->levels[i], &temp, cub3d->leaderboard.n_entries))
			return (err("Failed to set records"));
	}
	free(buf);
	close(fd);
	return (SUCCESS);
}
