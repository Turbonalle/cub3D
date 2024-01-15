/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_distractions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:02:46 by vvagapov          #+#    #+#             */
/*   Updated: 2024/01/15 12:08:50 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

static int	count_visible_distractions(cub3d_t *cub3d)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (i < cub3d->level->num_distractions + cub3d->player.thrown)
	{
		if (cub3d->level->distractions[i].visible == TRUE)
			count++;
		i++;
	}
	return (count);
}

static void	fill_visible_distractions_array(cub3d_t *cub3d,
	distraction_t **distractions)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < cub3d->level->num_distractions + cub3d->player.thrown)
	{
		if (cub3d->level->distractions[i].visible == TRUE)
		{
			distractions[j] = &cub3d->level->distractions[i];
			j++;
		}
		else
		{
			cub3d->level->distractions[i]
				.img_distraction->instances[0].enabled = FALSE;
		}
		i++;
	}
}

static void	sort_distractions_by_dist_to_player(distraction_t **distractions)
{
	int				i;
	int				j;
	distraction_t	*tmp;

	i = 0;
	while (distractions[i])
	{
		j = i + 1;
		while (distractions[j])
		{
			if (distractions[i]->dist_to_player
				< distractions[j]->dist_to_player)
			{
				tmp = distractions[i];
				distractions[i] = distractions[j];
				distractions[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

distraction_t	**create_array_of_distractions_ordered_by_dist(cub3d_t *cub3d)
{
	distraction_t	**distractions;
	int				count;

	count = count_visible_distractions(cub3d);
	distractions = malloc(sizeof(distraction_t *) * (count + 1));
	if (!distractions)
		return (NULL);
	distractions[count] = NULL;
	fill_visible_distractions_array(cub3d, distractions);
	sort_distractions_by_dist_to_player(distractions);
	return (distractions);
}
