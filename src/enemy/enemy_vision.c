
#include "../incl/cub3d.h"

static ray_t	*init_ray(t_enemy *enemy, int i)
{
	ray_t	*ray;

	ray = malloc(sizeof(ray_t));
	if (!ray)
		return (NULL);
	ray->angle = enemy[i].dir_player;
	ray->length = 0;
	ray->target = 0;
	ray->wall = 0;
	ray->door_dir = 0;
	ray->end.x = 0;
	ray->end.y = 0;
	return (ray);
}

void	handle_movement(cub3d_t *cub3d, double at_target, int target, int i)
{
	if (target == 0)
	{
		enemy_advance(cub3d, i);
		if (dist_between_d_vectors(cub3d->player.pos, cub3d->enemy[i].pos) < ENEMY_CATCH_DISTANCE)
		{
			// printf("You were caught at time %f\n",cub3d->run_time);
			player_is_hit(cub3d, i);
		}
	}
	if (target == 1)
	{
		enemy_advance(cub3d, i);
		if (dist_between_d_vectors(cub3d->enemy[i].pos, cub3d->enemy[i].target) < at_target)
		{
			cub3d->enemy[i].is_walking = 0;
			if (cub3d->level->distraction_amount > 0 && cub3d->enemy[i].target.x == cub3d->level->distraction.x && cub3d->enemy[i].target.y == cub3d->level->distraction.y)
			{
				printf("Started eating at %f\n",cub3d->run_time);
				cub3d->enemy[i].is_eating = 1;
			}
		}
	}
}

void	enemy_vision(cub3d_t *cub3d)
{
	int		i;
	double	at_target;

	i = 0;
	at_target = ENEMY_SPEED * (1 + cub3d->settings.e_speed) * 2;
	while (i < cub3d->num_enemies)
	{
		cub3d->enemy[i].dir_player = within_360(atan2(cub3d->player.pos.y
					- cub3d->enemy[i].pos.y, cub3d->player.pos.x
					- cub3d->enemy[i].pos.x) * 180 / M_PI);
		cub3d->enemy[i].is_hunting = FALSE;
		if (cub3d->run_time > cub3d->enemy[i].freeze_start + ENEMY_FREEZE)
		{
			if (cub3d->enemy[i].is_eating)
				eat(cub3d, i);
			else if (check_if_player_is_seen(cub3d, i))
				handle_movement(cub3d, at_target, 0, i);
			else if (distraction(cub3d, i))
				handle_movement(cub3d, at_target, 1, i);
			else if (cub3d->enemy[i].is_walking)
				handle_movement(cub3d, at_target, 1, i);
			else
				spin(cub3d, i, at_target);
		}
		if (cub3d->enemy[i].is_hunting)
			cub3d->enemy[i].state = HUNTING;
		else if (cub3d->enemy[i].is_walking)
			cub3d->enemy[i].state = WALKING;
		else
			cub3d->enemy[i].state = IDLE;
		i++;
	}
}

int	enemy_ray(cub3d_t *cub3d, player_t player, t_enemy *enemy, int i)
{
	dvector_t		v_ray_step_size;
	dvector_t		v_ray_1d_length;
	vector_t		v_map_check;
	vector_t		v_step;
	ray_t			*ray;

	v_map_check.x = (int)enemy[i].pos.x;
	v_map_check.y = (int)enemy[i].pos.y;
	v_ray_step_size = init_step_size(to_radians(enemy[i].dir_player));
	v_step = init_v_step(enemy[i].dir_player);
	v_ray_1d_length = init_ray_1D_length(cub3d->enemy[i].pos, enemy[i].dir_player, v_map_check, v_ray_step_size);
	ray = init_ray(enemy, i);
	if (!ray)
		return (0);
	while (not_at_end(ray, player, enemy, i))
	{
		if (wall_or_door_found(cub3d, v_map_check))
			return (free(ray), 0);
		adjust(&v_map_check, ray, v_step, &v_ray_1d_length);
		adjust_no_flag(&v_ray_1d_length, v_ray_step_size);
	}
	enemy[i].angle = to_radians(ray->angle);
	enemy[i].target = cub3d->player.pos;
	free(ray);
	return (1);
}
