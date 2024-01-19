/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cub3d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbagger <jbagger@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 12:10:36 by slampine          #+#    #+#             */
/*   Updated: 2024/01/19 11:21:34 by jbagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	count_distractions(t_cub3d *cub3d)
{
	int	i;
	int	j;

	i = 0;
	cub3d->level->num_distractions = 0;
	while (cub3d->level->map[i])
	{
		j = 0;
		while (cub3d->level->map[i][j])
		{
			if (cub3d->level->map[i][j] == 'm'
				|| cub3d->level->map[i][j] == 'r')
				cub3d->level->num_distractions++;
			j++;
		}
		i++;
	}
}

void	init_timer(t_cub3d *cub3d)
{
	cub3d->timer.pos.x = cub3d->img->width * 0.96;
	cub3d->timer.pos.y = cub3d->img->height * 0.05;
}

static void	set_init_stats(t_cub3d *cub3d)
{
	cub3d->state = STATE_START;
	cub3d->mouse_set_pos.x = 0;
	cub3d->mouse_set_pos.y = 0;
	cub3d->on_minimap = FALSE;
	cub3d->fov = FOV;
	cub3d->n_levels = LEVELS;
	cub3d->num_enemies = 0;
	cub3d->leaderboard.n_entries = N_ENTRIES;
	cub3d->speedrun = FALSE;
	cub3d->player.health = HEARTS;
	cub3d->player.mushroom_count = 0;
	cub3d->player.hit_timestamp = 0;
	cub3d->draw_floor = FALSE;
}

int	init_cub3d_rest(t_cub3d *cub3d)
{
	if (!init_intro(cub3d))
		return (free_all(cub3d, 7));
	if (!init_hearts(cub3d))
		return (free_all(cub3d, 8));
	if (!init_shroom(cub3d))
		return (free_all(cub3d, 9));
	if (!init_halo(cub3d))
		return (free_all(cub3d, 10));
	init_timer(cub3d);
	cub3d->distraction_thrown_texture = mlx_load_png(TEXTURE_MUSHROOM_THROWN);
	if (!cub3d->distraction_thrown_texture)
		return (free_all(cub3d, 11));
	cub3d->distraction_texture = mlx_load_png(TEXTURE_MUSHROOM);
	if (!cub3d->distraction_texture)
		return (free_all(cub3d, 12));
	if (!init_door_textures(cub3d))
		return (free_all(cub3d, 13));
	if (!init_stars_textures(cub3d))
		return (free_all(cub3d, 14));
	if (!init_pause_menu(cub3d, &cub3d->pause_menu))
		return (free_all(cub3d, 15));
	cub3d->start_timestamp = mlx_get_time();
	cub3d->prev_frame_update_timestamp = 0;
	cub3d->player.num_completed = 0;
	return (SUCCESS);
}

int	init_cub3d(t_cub3d *cub3d)
{
	int	i;

	i = -1;
	while (++i < LEVELS + 1)
		cub3d->levels[i].records = NULL;
	cub3d->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", FALSE);
	if (!cub3d->mlx)
		return (free_all(cub3d, 0));
	cub3d->img = mlx_new_image(cub3d->mlx, WIDTH, HEIGHT);
	if (!cub3d->img || (mlx_image_to_window(cub3d->mlx, cub3d->img, 0, 0) < 0))
		return (free_all(cub3d, 1));
	if (!init_rays(cub3d))
		return (free_all(cub3d, 2));
	set_keys(&cub3d->keys);
	set_init_stats(cub3d);
	if (!init_start_menu(cub3d, &cub3d->start_menu))
		return (free_all(cub3d, 3));
	if (!init_level_menu(cub3d, &cub3d->level_menu))
		return (free_all(cub3d, 4));
	if (!init_name_menu(cub3d, &cub3d->name_menu))
		return (free_all(cub3d, 5));
	if (!init_gameover_menu(cub3d, &cub3d->gameover_menu))
		return (free_all(cub3d, 6));
	return (init_cub3d_rest(cub3d));
}
