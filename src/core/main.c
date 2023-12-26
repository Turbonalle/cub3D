#include "../incl/cub3d.h"

void	free_already_allocated(cub3d_t *cub3d, int i)
{
	while (i >= 0)
	{
		free_list(cub3d->levels[i].map_list);
		i--;
		if (i >= 0)
			free_backup(cub3d->levels[i]);
	}
	free(cub3d->levels);
}

char	*create_path(int i)
{
	char	*level_i;
	char	*path;
	char	*full_path;

	level_i = ft_itoa(i);
	if (!level_i)
		return (NULL);
	path = ft_strjoin("assets/levels/level", level_i);
	if (!path)
		return (free(level_i), NULL);
	full_path = ft_strjoin(path, ".cub");
	if (!full_path)
		return (free(level_i), free(path), NULL);
	free(level_i);
	free(path);
	return (full_path);
}

int	read_all_levels(cub3d_t *cub3d)
{
	int		fd;
	int		i;
	char	*full_path;

	i = 1;
	while (i < LEVELS + 1)
	{
		full_path = create_path(i);
		if (full_path == NULL)
			return (free_already_allocated(cub3d, i), err("Malloc error"));
		fd = open(full_path, O_RDONLY);
		if (fd < 0)
			return (free(full_path), free_already_allocated(cub3d, i),
				err("Failed to open level file"));
		if (!read_cub_file(&cub3d->levels[i], full_path))
			return (free(full_path), free_already_allocated(cub3d, i),
				err("Failed to read level file"));
		close(fd);
		free(full_path);
		i++;
	}
	return (1);
}

int	write_records(cub3d_t *cub3d, level_t *levels)
{
	int			fd;
	int			i;
	char		*time;
	record_t	*ptr;
	record_t	*next;

	fd = open("assets/records.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (!err("Failed to open records file"));
	i = 0;
	while (++i < cub3d->n_levels + 1)
	{
		ptr = levels[i].records;
		while (ptr)
		{
			if (ptr->time > 0)
			{
				time = ft_itoa(ptr->time);
				// printf("Time = %d\n", ptr->time);
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
	close(fd);
	return (SUCCESS);
}

int	check_ext(char *str)
{
	int		len;
	int		i;
	char	*ext;

	i = 0;
	len = ft_strlen(str) - 1;
	ext = "buc.";
	while (ext[i])
	{
		if (str[len] != ext[i])
			return (0);
		len--;
		i++;
	}
	return (1);
}

int	main(int ac, char **av)
{
	cub3d_t	cub3d;

	if (ac != 2)
		return (!err("Wrong number of arguments\nUsage: ./cub3D <map.cub>"));
	if (!check_ext(av[1]))
		return (!err("Invalid extension"));
	cub3d.levels = malloc(sizeof(level_t) * (LEVELS + 1));
	if (!cub3d.levels)
		return (!err("Failed to malloc levels"));
	cub3d.level = &cub3d.levels[0];
	if (!read_cub_file(cub3d.level, av[1]))
		return (free(cub3d.levels), 1);
	if (!read_all_levels(&cub3d))
		return (1);
	if (!init_cub3d(&cub3d))
		return (1);
	if (!read_records(&cub3d, cub3d.levels))
		return (!err("Failed to read records"));
	if (!init_leaderboard(&cub3d, &cub3d.leaderboard))
		return (1);
	if (!init_enemy_frames(&cub3d))
		return (1);
	start_game(&cub3d);
	write_records(&cub3d, cub3d.levels);
	if (cub3d.state == 4)
		free_level(&cub3d);
	free_cub3d(&cub3d);
	system("leaks cub3D");
	return (0);
}
