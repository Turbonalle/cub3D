/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils_extra.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 11:58:16 by slampine          #+#    #+#             */
/*   Updated: 2024/01/17 11:58:35 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	free_level_menu(level_menu_t *menu)
{
	int	i;

	i = -1;
	if (menu->title.texture)
		mlx_delete_texture(menu->title.texture);
	if (menu->back.texture)
		mlx_delete_texture(menu->back.texture);
	if (menu->leaderboard.texture)
		mlx_delete_texture(menu->leaderboard.texture);
	if (menu->back_hover.texture)
		mlx_delete_texture(menu->back_hover.texture);
	if (menu->leaderboard_hover.texture)
		mlx_delete_texture(menu->leaderboard_hover.texture);
	while (++i < LEVELS)
	{
		if (menu->minilevels[i].number.texture)
			mlx_delete_texture(menu->minilevels[i].number.texture);
	}
}

void	free_name_menu(name_menu_t *menu)
{
	if (menu->title_win.texture)
		mlx_delete_texture(menu->title_win.texture);
	if (menu->title_top3.texture)
		mlx_delete_texture(menu->title_top3.texture);
	if (menu->back.texture)
		mlx_delete_texture(menu->back.texture);
	if (menu->back_hover.texture)
		mlx_delete_texture(menu->back_hover.texture);
	if (menu->timer.texture)
		mlx_delete_texture(menu->timer.texture);
}

void	free_gameover_menu(gameover_menu_t *menu)
{
	if (menu->title_win.texture)
		mlx_delete_texture(menu->title_win.texture);
	if (menu->title_gameover.texture)
		mlx_delete_texture(menu->title_gameover.texture);
	if (menu->back.texture)
		mlx_delete_texture(menu->back.texture);
	if (menu->back_hover.texture)
		mlx_delete_texture(menu->back_hover.texture);
	if (menu->restart.texture)
		mlx_delete_texture(menu->restart.texture);
	if (menu->restart_hover.texture)
		mlx_delete_texture(menu->restart_hover.texture);
	if (menu->arrow_back.texture)
		mlx_delete_texture(menu->arrow_back.texture);
	if (menu->arrow_restart.texture)
		mlx_delete_texture(menu->arrow_restart.texture);
	if (menu->timer.texture)
		mlx_delete_texture(menu->timer.texture);
}

void	free_intro(cub3d_t *cub3d)
{
	if (cub3d->intro.texture)
		mlx_delete_texture(cub3d->intro.texture);
}

void	free_hearts(cub3d_t *cub3d)
{
	int	i;

	i = -1;
	while (++i < HEARTS)
	{
		if (cub3d->hearts[i].full.texture)
			mlx_delete_texture(cub3d->hearts[i].full.texture);
		if (cub3d->hearts[i].empty.texture)
			mlx_delete_texture(cub3d->hearts[i].empty.texture);
	}
}
