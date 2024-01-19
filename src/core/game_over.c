/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_over.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 23:16:17 by vvagapov          #+#    #+#             */
/*   Updated: 2024/01/19 16:10:51 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

int	is_top_score(t_level *level, int time)
{
	t_record	*ptr;
	int			i;

	i = -1;
	ptr = level->records;
	while (++i < N_ENTRIES)
	{
		if (ptr == NULL)
			return (TRUE);
		if (time < ptr->time)
			return (TRUE);
		ptr = ptr->next;
	}
	return (FALSE);
}

void	clean_level_data(t_cub3d *cub3d)
{
	cub3d->halo.img->instances[0].enabled = FALSE;
	mlx_delete_image(cub3d->mlx, cub3d->minimap.img);
	mlx_delete_image(cub3d->mlx, cub3d->timer.img_time);
	disable_shroom(cub3d);
	free_level(cub3d);
	cub3d->keys.w = FALSE;
	cub3d->keys.a = FALSE;
	cub3d->keys.s = FALSE;
	cub3d->keys.d = FALSE;
	cub3d->keys.left = FALSE;
	cub3d->keys.right = FALSE;
	cub3d->keys.up = FALSE;
	cub3d->keys.down = FALSE;
	cub3d->player.thrown = FALSE;
}

void	level_finished(t_cub3d *cub3d)
{
	cub3d->time_finished = (int)(elapsed_time(cub3d) * 1000);
	clean_level_data(cub3d);
	if (cub3d->level != &cub3d->levels[0]
		&& is_top_score(cub3d->level, cub3d->time_finished)
		&& !cub3d->player.is_dirty_cheater)
	{
		enable_name_menu(cub3d, &cub3d->name_menu);
		cub3d->state = STATE_ENTERNAME;
	}
	else
	{
		cub3d->player.num_completed++;
		enable_gameover_menu(cub3d, &cub3d->gameover_menu, WIN);
		cub3d->state = STATE_GAMEOVER;
	}
	handle_cursor(cub3d);
}

void	game_over(t_cub3d *cub3d)
{
	cub3d->time_finished = (int)(elapsed_time(cub3d) * 1000);
	if (cub3d->player.thrown)
		cub3d->level->distractions[cub3d->level->num_distractions]
			.img_distraction->instances[0].enabled = FALSE;
	clean_level_data(cub3d);
	enable_gameover_menu(cub3d, &cub3d->gameover_menu, LOSE);
	cub3d->state = STATE_GAMEOVER;
	handle_cursor(cub3d);
}
