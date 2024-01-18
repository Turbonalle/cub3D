/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_utils_extra.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 12:57:59 by slampine          #+#    #+#             */
/*   Updated: 2024/01/18 09:53:43 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	eat(t_cub3d *cub3d, int i)
{
	if (cub3d->enemy[i].target.x != cub3d->level->distraction.x
		|| cub3d->enemy[i].target.y != cub3d->level->distraction.y)
		cub3d->enemy[i].is_eating = 0;
	cub3d->level->distraction_amount -= ENEMY_EATING_SPEED;
	if (cub3d->level->distraction_amount <= 0)
	{
		cub3d->player.thrown = FALSE;
		cub3d->level->distractions[cub3d->level->num_distractions]
			.img_distraction->instances[0].enabled = FALSE;
		cub3d->enemy[i].is_eating = 0;
	}
}

void	begin_spin(t_cub3d *cub3d, int i)
{
	if (cub3d->enemy[i].is_spinning == 0 && cub3d->settings.e_behaviour < 2)
	{
		cub3d->enemy[i].angle_start = within_two_pi(cub3d->enemy[i].angle
				- to_radians(ENEMY_ROT_SPEED));
		cub3d->enemy[i].is_spinning = 1;
	}
	cub3d->enemy[i].angle = within_two_pi(cub3d->enemy[i].angle
			+ to_radians(ENEMY_ROT_SPEED));
}

int	start_wandering(t_cub3d *cub3d, int i)
{
	if (cub3d->settings.e_behaviour == 2 || (cub3d->settings.e_behaviour == 1
			&& fabs(cub3d->enemy[i].angle - cub3d->enemy[i].angle_start)
			< to_radians(ENEMY_ROT_SPEED)))
		return (1);
	return (0);
}

void	spin(t_cub3d *cub3d, int i, double at_target)
{
	double	max_dist;

	begin_spin(cub3d, i);
	if (start_wandering(cub3d, i))
	{
		cub3d->enemy[i].angle = to_radians(rand() % 360);
		max_dist = sqrt(cub3d->img->width * cub3d->img->width
				+ cub3d->img->height * cub3d->img->height);
		enemy_movement_ray(cub3d, cub3d->enemy, i, max_dist);
		cub3d->enemy[i].angle_start = cub3d->enemy[i].angle;
		while (dist_between_d_vectors(cub3d->enemy[i].pos,
				cub3d->enemy[i].target) < at_target)
		{
			cub3d->enemy[i].angle = within_two_pi(to_radians(2)
					+ cub3d->enemy[i].angle);
			if (fabs(cub3d->enemy[i].angle - cub3d->enemy[i].angle_start)
				< to_radians(1))
				return ;
			enemy_movement_ray(cub3d, cub3d->enemy, i, max_dist);
		}
		cub3d->enemy[i].is_walking = 1;
		enemy_advance(cub3d, i);
		cub3d->enemy[i].is_spinning = 0;
	}
}

int	not_at_end(t_ray *ray, t_player player, t_enemy *enemy, int i)
{
	double			max_dist;

	max_dist = sqrt(pow(player.pos.x - enemy[i].pos.x, 2)
			+ pow(player.pos.y - enemy[i].pos.y, 2));
	if (ray->length < max_dist)
		return (1);
	return (0);
}
