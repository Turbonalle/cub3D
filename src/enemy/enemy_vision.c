
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
	ray->end.x = 0;
	ray->end.y = 0;
	return (ray);
}

void	handle_movement(cub3d_t *cub3d, double at_target, int target, int i)
{
	if (target == 0)
	{
		enemy_advance(cub3d, i);
		cub3d->enemy[i].is_walking = 1;
		if (sqrt(pow(cub3d->player.pos.x - cub3d->enemy[i].pos.x, 2)
				+ pow(cub3d->player.pos.y - cub3d->enemy[i].pos.y, 2)) < 1)
		{
			cub3d->enemy[i].freeze_start = cub3d->run_time;
			printf("You were caught at time %f\n",cub3d->run_time);
			player_is_hit(cub3d);
		}
	}
	if (target == 1)
	{
		enemy_advance(cub3d, i);
		cub3d->enemy[i].is_walking = 1;
		if (sqrt(pow(cub3d->enemy[i].target.x - cub3d->enemy[i].pos.x, 2) + pow(cub3d->enemy[i].target.y - cub3d->enemy[i].pos.y, 2)) < at_target)
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
		cub3d->enemy[i].is_hunting = FALSE;
		if (cub3d->run_time > cub3d->enemy[i].freeze_start + ENEMY_FREEZE)
		{
			if (check_if_player_is_seen(cub3d, i))
				handle_movement(cub3d, at_target, 0, i);
			else if (distraction(cub3d, i))
				handle_movement(cub3d, at_target, 1, i);
			else if (cub3d->enemy[i].is_walking)
				handle_movement(cub3d, at_target, 1, i);
			else if (cub3d->enemy[i].is_eating)
				eat(cub3d, i);
			else
				spin(cub3d, i, at_target);
		}
		if (cub3d->enemy[i].is_walking)
			cub3d->enemy[i].state = WALKING;
		else
			cub3d->enemy[i].state = IDLE;
		i++;
	}
}

int	enemy_ray(cub3d_t *cub3d, player_t player, t_enemy *enemy, int i)
{
	dvector_t		vRayUnitStepSize;
	dvector_t		vRayLength1D;
	vector_t		vMapCheck;
	vector_t		vStep;
	ray_t			*ray;

	vMapCheck.x = (int)enemy[i].pos.x;
	vMapCheck.y = (int)enemy[i].pos.y;
	vRayUnitStepSize = init_step_size(to_radians(enemy[i].dir_player));
	vStep = init_v_step(enemy[i].dir_player);
	vRayLength1D = init_ray_1D_length(cub3d->enemy[i].pos, enemy[i].dir_player, vMapCheck, vRayUnitStepSize);
	ray = init_ray(enemy, i);
	if (!ray)
		return (0);
	while (not_at_end(ray, player, enemy, i))
	{
		if (wall_or_door_found(cub3d, vMapCheck))
			return (free(ray), 0);
		adjust(&vMapCheck, ray, vStep, &vRayLength1D);
		adjust_no_flag(&vRayLength1D, vRayUnitStepSize);
	}
	enemy[i].angle = to_radians(ray->angle);
	enemy[i].target = cub3d->player.pos;
	free(ray);
	return (1);
}
