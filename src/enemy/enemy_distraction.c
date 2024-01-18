/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_distraction.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 13:18:38 by slampine          #+#    #+#             */
/*   Updated: 2024/01/18 11:15:34 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	set_thrown_shroom(t_distraction *distractions, int i, t_ray *ray)
{
	distractions[i].pos.x = ray->end.x;
	distractions[i].pos.y = ray->end.y;
	distractions[i].collected = FALSE;
	distractions[i].thrown = TRUE;
	distractions[i].visible = FALSE;
	distractions[i].pos_screen.x = -WIDTH;
	distractions[i].pos_screen.y = -HEIGHT;
	distractions[i].dist_to_player = 100;
}

void	cause_distraction_rest(t_cub3d *cub3d, t_distraction *distractions,
	int num_distractions, t_ray *ray)
{
	if (cub3d->player.thrown)
		distractions[num_distractions].img_distraction->instances[0].enabled
			= FALSE;
	cub3d->player.thrown = TRUE;
	set_thrown_shroom(distractions, num_distractions, ray);
	distractions[num_distractions].img_distraction
		= mlx_new_image(cub3d->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(cub3d->mlx, distractions[num_distractions]
		.img_distraction, 0, 0);
	draw_shroom_count(cub3d);
}

void	cause_distraction(t_cub3d *cub3d)
{
	t_ray	*ray;

	ray = malloc(sizeof(t_ray));
	if (!ray)
		return ;
	ray->angle = cub3d->player.angle;
	ray->length = 0;
	ray->target = 0;
	ray->wall = 0;
	ray->door_dir = 0;
	ray->end.x = 0;
	ray->end.y = 0;
	cast_ray(cub3d, ray);
	cub3d->level->distraction = ray->end;
	cub3d->level->distraction_amount = ENEMY_FOOD_AMOUNT;
	cub3d->player.mushroom_count--;
	cause_distraction_rest(cub3d, cub3d->level->distractions,
		cub3d->level->num_distractions, ray);
	free(ray);
}

static int	check_angles(t_cub3d *cub3d, int i, double dir_to_distraction)
{
	double	angle_min;
	double	angle_max;

	angle_min = within_360(cub3d->enemy[i].angle * 180 / M_PI - 30);
	angle_max = within_360(cub3d->enemy[i].angle * 180 / M_PI + 30);
	if (angle_max < angle_min)
	{
		if (dir_to_distraction > angle_max
			&& dir_to_distraction < angle_min)
			return (SUCCESS);
	}
	else
	{
		if (dir_to_distraction < angle_min
			|| dir_to_distraction > angle_max)
			return (SUCCESS);
	}
	return (FAIL);
}

int	distraction(t_cub3d *cub3d, int i)
{
	t_dvector	distraction;
	double		dir_to_distraction;
	double		at_target;

	if (cub3d->level->distraction_amount <= 0)
		return (FAIL);
	distraction = cub3d->level->distraction;
	dir_to_distraction = within_360(atan2(distraction.y
				- cub3d->enemy[i].pos.y, distraction.x
				- cub3d->enemy[i].pos.x) * 180 / M_PI);
	at_target = ENEMY_SPEED * (1 + cub3d->settings.e_speed) * 2;
	if (check_angles(cub3d, i, dir_to_distraction))
		return (FAIL);
	else if (enemy_ray_to_distraction(cub3d, distraction, dir_to_distraction, i)
		&& (dist_between_d_vectors(distraction, cub3d->enemy[i].pos)
			> at_target))
		return (SUCCESS);
	else
		return (FAIL);
}
