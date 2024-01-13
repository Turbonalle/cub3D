/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_utils_extra.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 13:29:59 by slampine          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/01/11 19:50:57 by vvagapov         ###   ########.fr       */
=======
/*   Updated: 2024/01/12 10:59:10 by slampine         ###   ########.fr       */
>>>>>>> main
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cub3d.h"

static void	delete_textures_additional(cub3d_t *cub3d)
{
	mlx_delete_texture(cub3d->start_menu.title.texture);
	mlx_delete_texture(cub3d->start_menu.exit.texture);
	mlx_delete_texture(cub3d->start_menu.start.texture);
	mlx_delete_texture(cub3d->start_menu.level.texture);
	mlx_delete_texture(cub3d->start_menu.exit_hover.texture);
	mlx_delete_texture(cub3d->start_menu.start_hover.texture);
	mlx_delete_texture(cub3d->start_menu.level_hover.texture);
	mlx_delete_texture(cub3d->start_menu.arrow_exit.texture);
	mlx_delete_texture(cub3d->start_menu.arrow_start.texture);
	mlx_delete_texture(cub3d->start_menu.arrow_level.texture);
	mlx_delete_texture(cub3d->level_menu.title.texture);
	mlx_delete_texture(cub3d->level_menu.back.texture);
	mlx_delete_texture(cub3d->level_menu.leaderboard.texture);
	mlx_delete_texture(cub3d->level_menu.back_hover.texture);
	mlx_delete_texture(cub3d->level_menu.leaderboard_hover.texture);
	mlx_delete_texture(cub3d->distraction_texture);
	mlx_delete_texture(cub3d->distraction_thrown_texture);
}

static void	delete_enemy_frames(cub3d_t *cub3d)
{
	int	j;
	int	i;

	j = 0;
	while (j < NUM_ENEMY_DIRECTIONS)
	{
		i = 0;
		while (i < NUM_FRAMES_ENEMY_IDLE)
			mlx_delete_texture(cub3d->frames_idle[j][i++]);
		i = 0;
		while (i < NUM_FRAMES_ENEMY_WALKING)
			mlx_delete_texture(cub3d->frames_walking[j][i++]);
		j++;
	}
}

static void	delete_textures(cub3d_t *cub3d)
{
	int	i;

	delete_textures_additional(cub3d);
	i = 0;
	while (i < LEVELS)
		mlx_delete_texture(cub3d->level_menu.minilevels[i++].number.texture);
	i = 0;
	while (i < HEARTS)
	{
		mlx_delete_texture(cub3d->hearts[i].full.texture);
		mlx_delete_texture(cub3d->hearts[i++].empty.texture);
	}
	delete_enemy_frames(cub3d);
	i = 0;
	while (i < 5)
		mlx_delete_texture(cub3d->door[i++].texture);
	i = 0;
	while (i < NUM_FRAMES_STARS)
	{
		free(cub3d->stars[i].path);
		mlx_delete_texture(cub3d->stars[i++].texture);
	}
}

void	free_cub3d(cub3d_t *cub3d)
{
	int	i;

	i = 0;
	while (i < LEVELS + 1)
	{
		free_list(cub3d->levels[i].map_list);
		i++;
	}
	free(cub3d->rays);
	i = 0;
	while (i < LEVELS + 1)
	{
		printf("Freeing backup for level %d\n", i);
		free_backup(cub3d->levels[i]);
		i++;
	}
	delete_textures(cub3d);
	free(cub3d->levels);
}

void	free_delete_textures(level_t *level)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (level->texture[i].path)
			free(level->texture[i].path);
		if (level->texture[i].texture)
			mlx_delete_texture(level->texture[i].texture);
		i++;
	}
}
