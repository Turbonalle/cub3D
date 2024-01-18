/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:46:36 by vvagapov          #+#    #+#             */
/*   Updated: 2024/01/18 11:44:09 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

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

int	init_floor(t_cub3d *cub3d)
{
	cub3d->floor.path = FLOOR_PNG;
	cub3d->floor.texture = mlx_load_png(FLOOR_PNG);
	if (!cub3d->floor.texture)
		return (FAIL);
	return (SUCCESS);
}

void	free_records(t_cub3d *cub3d)
{
	int			i;
	t_record	*next_rec;

	i = -1;
	while (++i < LEVELS + 1)
	{
		while (cub3d->levels[i].records)
		{
			next_rec = cub3d->levels[i].records->next;
			free_record(cub3d->levels[i].records);
			cub3d->levels[i].records = next_rec;
		}
	}
}

int	init_half(t_cub3d *cub3d)
{
	if (!init_cub3d(cub3d))
		return (FAIL);
	if (!read_records(cub3d))
		return (free_all(cub3d, 16));
	if (!init_leaderboard(cub3d, &cub3d->leaderboard))
		return (free_all(cub3d, 17));
	if (!init_enemy_frames(cub3d))
		return (free_all(cub3d, 18));
	if (!init_floor(cub3d))
		return (free_all(cub3d, 19));
	return (SUCCESS);
}

int	main(int ac, char **av)
{
	t_cub3d	cub3d;

	if (ac != 2)
		return (!err("Wrong number of arguments\nUsage: ./cub3D <map.cub>"));
	if (!check_ext(av[1]))
		return (!err("Invalid extension"));
	nullify_everything(&cub3d);
	cub3d.levels = malloc(sizeof(t_level) * (LEVELS + 1));
	if (!cub3d.levels)
		return (!err("Failed to malloc levels"));
	cub3d.level = &cub3d.levels[0];
	if (!read_cub_file(cub3d.level, av[1]))
		return (free(cub3d.levels), 1);
	if (!read_all_levels(&cub3d))
		return (1);
	if (!init_half(&cub3d))
		return (1);
	start_game(&cub3d);
	write_records(&cub3d, cub3d.levels);
	if (cub3d.state == STATE_GAME)
		free_level(&cub3d);
	free_cub3d(&cub3d);
	system("leaks cub3D");	// DEBUG
	return (0);
}
