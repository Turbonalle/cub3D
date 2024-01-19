/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_utils_extra.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 13:29:59 by slampine          #+#    #+#             */
/*   Updated: 2024/01/19 16:45:01 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cub3d.h"

static void	delete_textures_additional(t_cub3d *cub3d)
{
	free_start_menu(&cub3d->start_menu);
	free_name_menu(&cub3d->name_menu);
	free_gameover_menu(&cub3d->gameover_menu);
	free_level_menu(&cub3d->level_menu);
	mlx_delete_texture(cub3d->leaderboard.title.texture);
	mlx_delete_texture(cub3d->leaderboard.back.texture);
	mlx_delete_texture(cub3d->leaderboard.back_hover.texture);
	mlx_delete_texture(cub3d->pause_menu.title.texture);
}

static void	delete_enemy_frames(t_cub3d *cub3d)
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
		while (i < NUM_FRAMES_WALKING)
			mlx_delete_texture(cub3d->frames_walking[j][i++]);
		i = 0;
		while (i < NUM_FRAMES_HUNTING)
			mlx_delete_texture(cub3d->frames_hunting[j][i++]);
		j++;
	}
}

static void	delete_textures(t_cub3d *cub3d)
{
	int	i;

	delete_textures_additional(cub3d);
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

void	free_cub3d(t_cub3d *cub3d)
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
		free_backup(cub3d->levels[i]);
		i++;
	}
	delete_textures(cub3d);
	free(cub3d->levels);
	mlx_delete_texture(cub3d->floor.texture);
	free_shroom(cub3d);
	free_intro(cub3d);
	mlx_terminate(cub3d->mlx);
}

void	free_delete_textures(t_level *level)
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
