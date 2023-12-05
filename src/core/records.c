#include "../incl/cub3d.h"

record_t *new_record(int time, char* name)
{
	record_t	*new;

	new = malloc(sizeof(record_t));
	if (!new)
		return (NULL);
	new->time = time;
	new->name = name;
	new->next = NULL;
	return (new);
}

int	add_record(record_t *records, int time, char* name)
{
	record_t	*new;
	record_t	*temp;
	int			i;

	new = new_record(time, name);
	if (!new)
		return (err("Failed to malloc new record"));
	if (!records)
	{
		records = new;
		return (SUCCESS);
	}
	temp = records;
	i = 0;
	while (temp->next && temp->next->time < time && ++i <= 10)
		temp = temp->next;
	if (i == 10)
		free_record(new);
	else if (temp->next)
	{
		new->next = temp->next;
		temp->next = new;
	}
	else
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

int	set_records(level_t *level, char **buf)
{
	char	*name;
	int		time;

	while (**buf && **buf != '\n')
	{
		if (!get_record_time(buf, &time))
			return (err("Failed to get time string"));
		printf("time: %d\n", time);	// DEBUG
		if (!get_record_name(buf, &name))
			return (err("Failed to get name string"));
		printf("name: %s\n", name);	// DEBUG
		add_record(level->records, time, name);
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

int	read_records(level_t *levels)
{
	int		fd;
	char	*buf;
	char	*temp;
	int		i;

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
	while (*temp && ++i <= 9)
	{
		printf("LEVEL %d\n", i);	// DEBUG
		if (!set_records(&levels[i], &temp))
			return (err("Failed to set records"));
		printf("\n");	// DEBUG
	}
	free(buf);
	close(fd);
	return (SUCCESS);
}