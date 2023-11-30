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

int	read_all_levels(cub3d_t *cub3d)
{
	int		fd;
	int		i;
	char	*level_i;

	cub3d->levels = malloc(sizeof(level_t) * 10);
	i = 0;
	while (i < 10)
	{
		level_i = ft_itoa(i);
		fd = open(ft_strjoin("assets/levels/level", level_i), O_RDONLY);
		if (fd < 0)
			return (err("Failed to open level file"));
		if (!read_cub_file(&cub3d->levels[i], ft_strjoin("levels/level", level_i)))
			return (err("Failed to read level file"));
		close(fd);
		free(level_i);
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
	printf("TEST\n");
	if (!read_cub_file(&cub3d.level, av[1]) || !init_cub3d(&cub3d))
		return (1);
	printf("TEST\n");
	print_info(&cub3d); // DEBUG
	// read_all_levels(&cub3d);
	start_game(&cub3d);
	free_cub3d(&cub3d);
	return (0);
}
