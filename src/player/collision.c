/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbagger <jbagger@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:43:02 by slampine          #+#    #+#             */
/*   Updated: 2024/01/16 12:45:39 by jbagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

int	is_locked_door(cub3d_t *cub3d, int y, int x)
{
	int	index;

	index = get_door_index(cub3d->level->map[y][x]);
	if (index == -1)
	{
		return (FALSE);
	}
	return (cub3d->level->door_groups[index].num_keys_left > 0);
}

int	deactivate_key(cub3d_t *cub3d, key_node_t *head, double y, double x)
{
	while (head)
	{
		if ((pow(head->pos.x - x, 2) + pow(head->pos.y - y, 2) < 1)
			&& head->collected == FALSE)
		{
			head->collected = TRUE;
			head->img_curr_frame->instances[0].enabled = FALSE;
			cub3d->level->map[(int)y][(int)x] = '0';
			return (TRUE);
		}
		head = head->next;
	}
	return (FALSE);
}

void	collect_key(cub3d_t *cub3d, double y, double x)
{
	int	index;

	index = get_key_index(cub3d->level->map[(int)y][(int)x]);
	if (index == -1 || deactivate_key(cub3d,
			cub3d->level->key_groups[index].keys, y, x) == FALSE)
		return ;
	cub3d->level->door_groups[index].num_keys_left--;
	draw_key_counts(cub3d);
	activate_halo(&cub3d->halo, GREEN);
}

void	collect_shroom(cub3d_t *cub3d, double y, double x)
{
	int	i;

	if (cub3d->level->map[(int)y][(int)x] == 'm'
		|| cub3d->level->map[(int)y][(int)x] == 'r')
	{
		cub3d->level->map[(int)y][(int)x] = '0';
		cub3d->player.mushroom_count++;
		draw_shroom_count(cub3d);
		enable_shroom(cub3d);
		activate_halo(&cub3d->halo, TURQUOISE);
		i = 0;
		while (i < cub3d->level->num_distractions)
		{
			if (cub3d->level->distractions[i].pos.x == (int)x + 0.5
				&& cub3d->level->distractions[i].pos.y == (int)y + 0.5)
			{
				cub3d->level->distractions[i].collected = TRUE;
				cub3d->level->distractions[i].img_distraction->instances[0]
					.enabled = FALSE;
				cub3d->level->distractions[i].visible = FALSE;
			}
			i++;
		}
	}
}

void	item_collected_checker(cub3d_t *cub3d)
{
	double	new_y;
	double	new_x;

	new_y = cub3d->player.new_pos.y;
	new_x = cub3d->player.new_pos.x;
	collect_key(cub3d, new_y, new_x);
	collect_shroom(cub3d, new_y, new_x);
}
