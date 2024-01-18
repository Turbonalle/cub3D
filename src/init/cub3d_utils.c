/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 12:14:00 by slampine          #+#    #+#             */
/*   Updated: 2024/01/18 09:53:43 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	count_enemies(t_cub3d *cub3d)
{
	int	i;
	int	j;

	i = 0;
	cub3d->num_enemies = 0;
	while (cub3d->level->map[i])
	{
		j = 0;
		while (cub3d->level->map[i][j])
		{
			if (ft_strchr(ENEMIES, cub3d->level->map[i][j]))
				cub3d->num_enemies++;
			j++;
		}
		i++;
	}
}

int	init_rays(t_cub3d *cub3d)
{
	int	i;

	cub3d->rays = malloc(sizeof(t_ray) * WIDTH);
	if (!cub3d->rays)
		return (FAIL);
	i = -1;
	while (++i < (int)cub3d->img->width)
	{
		cub3d->rays[i].end.x = 0;
		cub3d->rays[i].end.y = 0;
		cub3d->rays[i].angle = 0;
		cub3d->rays[i].length = 0;
		cub3d->rays[i].target = 0;
		cub3d->rays[i].wall = 0;
		cub3d->rays[i].door_dir = 0;
	}
	return (SUCCESS);
}

void	set_initial_direction(t_cub3d *cub3d)
{
	if (cub3d->level->starting_dir == 'E')
		cub3d->player.angle = to_radians(0);
	else if (cub3d->level->starting_dir == 'S')
		cub3d->player.angle = to_radians(90);
	else if (cub3d->level->starting_dir == 'W')
		cub3d->player.angle = to_radians(180);
	else if (cub3d->level->starting_dir == 'N')
		cub3d->player.angle = to_radians(270);
	cub3d->player.dir.x = cos(cub3d->player.angle);
	cub3d->player.dir.y = sin(cub3d->player.angle);
}

void	set_keys_rest(t_keypress *keys)
{
	keys->n = FALSE;
	keys->m = FALSE;
	keys->space = FALSE;
	keys->shift = FALSE;
	keys->enter = FALSE;
	keys->escape = FALSE;
	keys->backspace = FALSE;
	keys->up = FALSE;
	keys->down = FALSE;
	keys->left = FALSE;
	keys->right = FALSE;
	keys->mouse_left = FALSE;
	keys->mouse_right = FALSE;
}

void	set_keys(t_keypress *keys)
{
	keys->q = FALSE;
	keys->w = FALSE;
	keys->e = FALSE;
	keys->r = FALSE;
	keys->t = FALSE;
	keys->y = FALSE;
	keys->u = FALSE;
	keys->i = FALSE;
	keys->o = FALSE;
	keys->p = FALSE;
	keys->a = FALSE;
	keys->s = FALSE;
	keys->d = FALSE;
	keys->f = FALSE;
	keys->g = FALSE;
	keys->h = FALSE;
	keys->j = FALSE;
	keys->k = FALSE;
	keys->l = FALSE;
	keys->z = FALSE;
	keys->x = FALSE;
	keys->c = FALSE;
	keys->v = FALSE;
	keys->b = FALSE;
	set_keys_rest(keys);
}
