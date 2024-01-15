/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_enemies.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:02:50 by vvagapov          #+#    #+#             */
/*   Updated: 2024/01/15 12:04:25 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

static int	count_visible_enemies(cub3d_t *cub3d)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (i < cub3d->num_enemies)
	{
		if (cub3d->enemy[i].visible == TRUE)
			count++;
		i++;
	}
	return (count);
}

static void	fill_visible_enemies_array(cub3d_t *cub3d, t_enemy **enemies)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < cub3d->num_enemies)
	{
		if (cub3d->enemy[i].visible == TRUE)
		{
			enemies[j] = &cub3d->enemy[i];
			j++;
		}
		else
		{
			cub3d->enemy[i].img_curr_frame->instances[0].enabled = FALSE;
		}
		i++;
	}
}

static void	sort_enemies_by_dist_to_player(t_enemy **enemies)
{
	int			i;
	int			j;
	t_enemy		*tmp;

	i = 0;
	while (enemies[i])
	{
		j = i + 1;
		while (enemies[j])
		{
			if (enemies[i]->dist_to_player < enemies[j]->dist_to_player)
			{
				tmp = enemies[i];
				enemies[i] = enemies[j];
				enemies[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

t_enemy	**create_array_of_enemies_ordered_by_dist(cub3d_t *cub3d)
{
	t_enemy		**enemies;
	int			count;

	count = count_visible_enemies(cub3d);
	enemies = malloc(sizeof(t_enemy *) * (count + 1));
	if (!enemies)
		return (NULL);
	enemies[count] = NULL;
	fill_visible_enemies_array(cub3d, enemies);
	sort_enemies_by_dist_to_player(enemies);
	return (enemies);
}
