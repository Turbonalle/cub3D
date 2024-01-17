#include "../incl/cub3d.h"

void	free_already_allocated(cub3d_t *cub3d, int i)
{
	while (i >= 0)
	{
		free_list(cub3d->levels[i].map_list);
		i--;
		if (i >= 0)
		{
			printf("freeing BACKUP for level %d on malloc fail\n", i);
			free_backup(cub3d->levels[i]);
		}
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
	path = ft_strjoin(LEVEL_PREFIX, level_i);
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

	fd = open(RECORD_FILE, O_RDWR | O_CREAT | O_TRUNC, 0644);
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
	char	*last_slash;
	char	*ext;

	last_slash = ft_strchr(str, '/');
	if (!last_slash)
		ext = ft_strchr(str, '.');
	else
	{
		last_slash = ft_strrchr(str, '/');
		ext = ft_strchr(last_slash, '.');
	}
	if (!ext)
		return (FAIL);
	if (ft_strcmp(ext, ".cub") != 0)
		return (FAIL);
	return (SUCCESS);
}

int	init_floor(cub3d_t *cub3d)
{
	cub3d->floor.path = FLOOR_PNG;
	cub3d->floor.texture = mlx_load_png(FLOOR3_PNG);
	if (!cub3d->floor.texture)
		return (FAIL);
	return (SUCCESS);
}

void	free_records(cub3d_t *cub3d)
{
	int			i;
	record_t	*next_rec;

	i = -1;
	while (++i < LEVELS + 1)
	{
		printf("free_records i: %d\n", i);
		printf("cub3d->levels: %p\n", cub3d->levels);
		printf("cub3d->levels[i].records: %p\n", cub3d->levels[i].records);
		while (cub3d->levels[i].records)
		{
			next_rec = cub3d->levels[i].records->next;
			printf("freeing pointer: %p\n", cub3d->levels[i].records);
			free_record(cub3d->levels[i].records);
			cub3d->levels[i].records = next_rec;
		}
	}
}

int	main(int ac, char **av)
{
	cub3d_t	cub3d;

	if (ac != 2)
		return (!err("Wrong number of arguments\nUsage: ./cub3D <map.cub>"));
	if (!check_ext(av[1]))
		return (!err("Invalid extension"));
	nullify_everything(&cub3d);
	cub3d.levels = malloc(sizeof(level_t) * (LEVELS + 1));
	if (!cub3d.levels)
		return (!err("Failed to malloc levels"));
	cub3d.level = &cub3d.levels[0];
	if (!read_cub_file(cub3d.level, av[1]))
		return (free(cub3d.levels), 1);
	printf("READ MAIN CUB FILE\n");
	if (!read_all_levels(&cub3d))
		return (1);
	printf("init_cub3d\n");
	if (!init_cub3d(&cub3d))
		return (1);
	printf("init_records\n");
	if (!read_records(&cub3d))
		return (!free_all(&cub3d, 16));
	if (!init_leaderboard(&cub3d, &cub3d.leaderboard))
		return (!free_all(&cub3d, 17));
	if (!init_enemy_frames(&cub3d))
		return (!free_all(&cub3d, 18));
	if (!init_floor(&cub3d))
		return (!free_all(&cub3d, 19));
	start_game(&cub3d);
	write_records(&cub3d, cub3d.levels);
	if (cub3d.state == STATE_GAME)
		free_level(&cub3d);
	free_cub3d(&cub3d);
	mlx_terminate(cub3d.mlx);
	system("leaks cub3D");
	return (0);
}
