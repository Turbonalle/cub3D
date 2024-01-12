#include "../incl/cub3d.h"

static void write_record(record_t *level_records, int fd)
{
	char		*time;
	record_t	*ptr;
	record_t	*next;

	ptr = level_records;
	while (ptr)
	{
		if (ptr->time > 0)
		{
			time = ft_itoa(ptr->time);
			write(fd, time, ft_strlen(time));
			write(fd, " ", 1);
			write(fd, ptr->name, ft_strlen(ptr->name));
			write(fd, "\n", 1);
			free(time);
		}
		next = ptr->next;
		free(ptr->name);
		free(ptr);
		ptr = next;
	}
	write(fd, "\n", 1);
}

static int	write_records(cub3d_t *cub3d, level_t *levels)
{
	int			fd;
	int			i;
	// char		*time;
	// record_t	*ptr;
	// record_t	*next;

	fd = open(RECORD_FILE, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (!err("Failed to open records file"));
	i = 0;
	while (++i < cub3d->n_levels + 1)
	{
		write_record(levels[i].records, fd);	// & or not?
		// ptr = levels[i].records;
		// while (ptr)
		// {
		// 	if (ptr->time > 0)
		// 	{
		// 		time = ft_itoa(ptr->time);
		// 		write(fd, time, ft_strlen(time));
		// 		write(fd, " ", 1);
		// 		write(fd, ptr->name, ft_strlen(ptr->name));
		// 		write(fd, "\n", 1);
		// 		free(time);
		// 	}
		// 	next = ptr->next;
		// 	free(ptr->name);
		// 	free(ptr);
		// 	ptr = next;
		// }
		// write(fd, "\n", 1);
	}
	close(fd);
	return (SUCCESS);
}

void	close_game(cub3d_t *cub3d)
{
	write_records(cub3d, cub3d->levels);
	if (cub3d->state == STATE_GAME)
		free_level(cub3d);
	free_cub3d(cub3d);
	mlx_terminate(cub3d->mlx);
}