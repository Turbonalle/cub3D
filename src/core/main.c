/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:09:19 by vvagapov          #+#    #+#             */
/*   Updated: 2023/11/27 13:45:20 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

	cub3d->levels = malloc(sizeof(level_t) * 10);
	i = 0;
	while (i < 9)
	{
		printf("i: %d\n", i);
		level_i = ft_itoa(i + 1);
		path = ft_strjoin("../assets/levels/level", level_i);
		full_path = ft_strjoin(path, ".cub");
		printf("full_path: %s\n", full_path);
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
		return (err("Invalid extension"));
	if (!read_cub_file(&cub3d.level, av[1]) || !init_cub3d(&cub3d))
		return (1);
	print_level_info(&cub3d.level); // DEBUG
	if (!read_all_levels(&cub3d))
		return (1);
	// for (int i = 0; i < 9; i++)
	// 	print_level_info(&cub3d.levels[i]); // DEBUG
	start_game(&cub3d);
	free_cub3d(&cub3d);
	return (0);
}
