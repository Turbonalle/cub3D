#include "../incl/cub3d.h"

int free_three_strings(char *s1, char *s2, char *s3)
{
	free(s1);
	free(s2);
	free(s3);
	return (0);
}

int	read_all_levels(cub3d_t *cub3d)
{
	int		fd;
	int		i;
	char	*level_i;
	char	*path;
	char	*full_path;


	i = 1;
	while (i <= 9)
	{
		// TODO maybe: add malloc fail handling?
		level_i = ft_itoa(i);
		path = ft_strjoin("assets/levels/level", level_i);
		full_path = ft_strjoin(path, ".cub");
		fd = open(full_path, O_RDONLY);
		if (fd < 0)
			return (free_three_strings(level_i, path, full_path), err("Failed to open level file"));
		if (!read_cub_file(&cub3d->levels[i], full_path))
			return (free_three_strings(level_i, path, full_path), err("Failed to read level file"));
		close(fd);
		free_three_strings(level_i, path, full_path);
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
	record_t	*temp;

	fd = open("assets/records.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (!err("Failed to open records file"));
	i = 0;
	while (++i <= cub3d->n_levels)
	{
		ptr = levels[i].records;
		while (ptr)
		{
			if (ptr->time > 0)
			{
				time = ft_itoa(ptr->time);
				printf("Time = %d\n", ptr->time);
				write(fd, time, ft_strlen(time));
				write(fd, " ", 1);
				write(fd, ptr->name, ft_strlen(ptr->name));
				write(fd, "\n", 1);
				free(time);
			}
			temp = ptr;
			free(ptr->name);
			free(ptr);
			ptr = temp->next;
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

// Store av[1] in cub3d->levels[0]
// Read levels in level folder into cub3d->levels[1-9]

int	main(int ac, char **av)
{
	cub3d_t	cub3d;

	if (ac != 2)
		return (!err("Wrong number of arguments\nUsage: ./cub3D <map.cub>"));
	if (!check_ext(av[1]))
		return (!err("Invalid extension"));
	cub3d.levels = malloc(sizeof(level_t) * 10);
	cub3d.level = &cub3d.levels[0];
	if (!cub3d.levels)
		return (!err("Failed to malloc levels"));
	if (!read_cub_file(cub3d.level, av[1]) || !init_cub3d(&cub3d))
		return (1);
	// print_level_info(cub3d.level); // DEBUG
	if (!read_all_levels(&cub3d))
		return (1);
	if (!read_records(&cub3d, cub3d.levels))
		return (!err("Failed to read records"));
	start_game(&cub3d);
	write_records(&cub3d, cub3d.levels);
	free_cub3d(&cub3d);
	printf("freed!\n");
	return (0);
}
