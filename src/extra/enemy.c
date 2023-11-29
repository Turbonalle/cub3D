
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

static int all_keys_found(cub3d_t *cub3d, int i)
{
	key_node_t *temp;
	temp = cub3d->key_groups[i].keys;
	while (temp != NULL)
	{
		if (temp->collected == 0)
			return (0);
		temp = temp->next;
	}
	return (1);
}

static int	door_found(cub3d_t *cub3d, vector_t vMapCheck)
{
	if (vMapCheck.x >= 0 && vMapCheck.x < cub3d->map_columns && vMapCheck.y >= 0
		&& vMapCheck.y < cub3d->map_rows
		&& (cub3d->map[vMapCheck.y][vMapCheck.x] == 'A'
		|| cub3d->map[vMapCheck.y][vMapCheck.x] == 'B'
		|| cub3d->map[vMapCheck.y][vMapCheck.x] == 'C'
		|| cub3d->map[vMapCheck.y][vMapCheck.x] == 'D'
		|| cub3d->map[vMapCheck.y][vMapCheck.x] == '-'
		|| cub3d->map[vMapCheck.y][vMapCheck.x] == '|'))
	{
		if (dist_between(vMapCheck, cub3d->player.pos) > 3)
			return (1);
		if (cub3d->map[vMapCheck.y][vMapCheck.x] == '-' || cub3d->map[vMapCheck.y][vMapCheck.x] == '|')
			return (0);
		if (cub3d->map[vMapCheck.y][vMapCheck.x] == 'A' && all_keys_found(cub3d, 0) == 1)
			return (0);
		if (cub3d->map[vMapCheck.y][vMapCheck.x] == 'B' && all_keys_found(cub3d, 1) == 1)
			return (0);
		if (cub3d->map[vMapCheck.y][vMapCheck.x] == 'C' && all_keys_found(cub3d, 2) == 1)
			return (0);
		if (cub3d->map[vMapCheck.y][vMapCheck.x] == 'D' && all_keys_found(cub3d, 3) == 1)
			return (0);
		else
			return (1);
	}
	return (0);
}

static int	wall_found(cub3d_t *cub3d, vector_t vMapCheck)
{
	return (vMapCheck.x >= 0
		&& vMapCheck.x < cub3d->map_columns
		&& vMapCheck.y >= 0
		&& vMapCheck.y < cub3d->map_rows
		&& cub3d->map[vMapCheck.y][vMapCheck.x] == WALL);
}

static void	init_enemy_dir(t_enemy *enemy, int i, char spec)
{
	if (spec == 'e')
		enemy[i].angle = to_radians(0);
	if (spec == 's')
		enemy[i].angle = to_radians(90);
	if (spec == 'w')
		enemy[i].angle = to_radians(180);
	if (spec == 'n')
		enemy[i].angle = to_radians(270);
}

static int	enemy_starting_point(cub3d_t *cub3d, int enemy_i)
{
	int	i;
	int	j;

	i = -1;
	while (cub3d->map[++i])
	{
		j = -1;
		while (cub3d->map[i][++j])
		{
			if (ft_strchr(ENEMIES, cub3d->map[i][j]))
			{
				cub3d->enemy[enemy_i].pos.x = j + 0.5;
				cub3d->enemy[enemy_i].pos.y = i + 0.5;
				init_enemy_dir(cub3d->enemy, enemy_i, cub3d->map[i][j]);
				cub3d->map[i][j] = '0';
				return (SUCCESS);
			}
		}
	}
	return (FAIL);
}


static int	enemy_ray(cub3d_t *cub3d, player_t player, t_enemy *enemy, int i)
{
	dvector_t		vRayUnitStepSize;
	dvector_t		vRayLength1D;
	dvector_t		vRayDir;
	vector_t		vMapCheck;
	vector_t		vStep;
	ray_t			*ray;
	double			max_dist;

	vRayDir.x = cos(to_radians(enemy[i].dir_player));
	vRayDir.y = sin(to_radians(enemy[i].dir_player));
	max_dist = sqrt(pow(player.pos.x - enemy[i].pos.x, 2) + pow(player.pos.y - enemy[i].pos.y, 2));
	vMapCheck.x = (int)enemy[i].pos.x;
	vMapCheck.y = (int)enemy[i].pos.y;
	vRayUnitStepSize.x = sqrt(1 + (vRayDir.y / vRayDir.x) * (vRayDir.y / vRayDir.x));
	vRayUnitStepSize.y = sqrt(1 + (vRayDir.x / vRayDir.y) * (vRayDir.x / vRayDir.y));
	if (vRayDir.x < 0)
	{
		vStep.x = -1;
		vRayLength1D.x = (enemy[i].pos.x - vMapCheck.x) * vRayUnitStepSize.x;
	}
	else
	{
		vStep.x = 1;
		vRayLength1D.x = (vMapCheck.x + 1.0 - enemy[i].pos.x) * vRayUnitStepSize.x;
	}
	if (vRayDir.y < 0)
	{
		vStep.y = -1;
		vRayLength1D.y = (enemy[i].pos.y - vMapCheck.y) * vRayUnitStepSize.y;
	}
	else
	{
		vStep.y = 1;
		vRayLength1D.y = (vMapCheck.y + 1.0 - enemy[i].pos.y) * vRayUnitStepSize.y;
	}
	ray = init_ray(enemy, i);
	if (!ray)
		return (0);
	while (ray->length < max_dist)
	{
		if (vRayLength1D.x < vRayLength1D.y)
		{
			vMapCheck.x += vStep.x;
			ray->length = vRayLength1D.x;
			vRayLength1D.x += vRayUnitStepSize.x;
		}
		else
		{
			vMapCheck.y += vStep.y;
			ray->length = vRayLength1D.y;
			vRayLength1D.y += vRayUnitStepSize.y;
		}
		if (wall_found(cub3d, vMapCheck) && ray->length < max_dist)
		{
			free(ray);
			return (0);
		}
		if (door_found(cub3d, vMapCheck) && ray->length < max_dist)
		{
			free(ray);
			return (0);
		}
	}
	enemy[i].angle = to_radians(ray->angle);
	enemy[i].target = cub3d->player.pos;
	free(ray);
	return (1);
}

static void	enemy_advance(cub3d_t *cub3d, int i)
{
	cub3d->enemy[i].pos.x += cos(cub3d->enemy[i].angle) * ENEMY_SPEED * (1 + cub3d->settings.e_difficulty);
	cub3d->enemy[i].pos.y += sin(cub3d->enemy[i].angle) * ENEMY_SPEED * (1 + cub3d->settings.e_difficulty);
}

int	check_if_player_is_seen(cub3d_t *cub3d, int i)
{
	double	angle_min;
	double	angle_max;

	cub3d->enemy[i].dir_player = within_360(atan2(cub3d->player.pos.y - cub3d->enemy[i].pos.y, cub3d->player.pos.x - cub3d->enemy[i].pos.x) * 180 / M_PI);
	angle_min = within_360(cub3d->enemy[i].angle * 180 / M_PI - 30);
	angle_max = within_360(cub3d->enemy[i].angle * 180 / M_PI + 30);
	// printf("Enemy is at %f,%f, player is at %f,%f\n",cub3d->enemy[i].pos.x,cub3d->enemy[i].pos.y,cub3d->player.pos.x,cub3d->player.pos.y);
	// printf("Looking between angles %f,%f, player at dir %f\n",angle_min,angle_max,cub3d->enemy[i].dir_player);
	if (angle_max < angle_min)
	{
		if (cub3d->enemy[i].dir_player > angle_max && cub3d->enemy[i].dir_player < angle_min)
			return (0);
		else if (enemy_ray(cub3d, cub3d->player, cub3d->enemy, i))
			return (1);
		else
			return (0);
	}
	else
	{
		if (cub3d->enemy[i].dir_player < angle_min || cub3d->enemy[i].dir_player > angle_max)
			return (0);
		else if (enemy_ray(cub3d, cub3d->player, cub3d->enemy, i))
			return (1);
		else
			return (0);
	}
}

void	enemy_vision(cub3d_t *cub3d)
{
	int				i;

	i = 0;
	while (i < cub3d->num_enemies)
	{
		if (check_if_player_is_seen(cub3d, i))
		{
			enemy_advance(cub3d, i);
			cub3d->enemy[i].is_walking = 1;
			// if (sqrt(pow(cub3d->player.pos.x - cub3d->enemy[i].pos.x, 2) + pow(cub3d->player.pos.y - cub3d->enemy[i].pos.y, 2)) < 1)
			// 	printf("You were caught\n");
		}
		else if (cub3d->enemy[i].is_walking)
		{
			enemy_advance(cub3d, i);
			cub3d->enemy[i].is_walking = 1;
			if (sqrt(pow(cub3d->enemy[i].target.x - cub3d->enemy[i].pos.x, 2) + pow(cub3d->enemy[i].target.y - cub3d->enemy[i].pos.y, 2)) < 0.1)
				cub3d->enemy[i].is_walking = 0;
		}
		else
		{
			if (cub3d->enemy[i].is_spinning == 0)
			{
				cub3d->enemy[i].angle_start = within_two_pi(cub3d->enemy[i].angle - ENEMY_ROT_SPEED * M_PI / 180);
				cub3d->enemy[i].is_spinning = 1;
			}
			cub3d->enemy[i].angle = within_two_pi(cub3d->enemy[i].angle + ENEMY_ROT_SPEED * M_PI / 180);
			if (fabs(cub3d->enemy[i].angle - cub3d->enemy[i].angle_start) < 0.01)
			{
				printf("Moved\n");
				cub3d->enemy[i].angle = to_radians(rand() % 360);
				// update this to check walls, maybe move longer dist and not all at once
				int num = 0;
				while (num < 10)
				{
					enemy_advance(cub3d, i);
					num++;
				}
				cub3d->enemy[i].is_spinning = 0;
			}
		}
		i++;
	}
}

int init_enemy(cub3d_t *cub3d)
{
	int	i;

	i = 0;
	cub3d->enemy = malloc(sizeof(t_enemy) * cub3d->num_enemies);
	if (!cub3d->enemy)
		return (0);
	while (i < cub3d->num_enemies)
	{
		enemy_starting_point(cub3d, i);
		cub3d->enemy[i].dir_player = 0;
		cub3d->enemy[i].is_spinning = 0;
		cub3d->enemy[i].is_walking = 0;
		cub3d->enemy[i].dir.x = 0;
		cub3d->enemy[i].dir.y = 0;
		cub3d->enemy[i].path = NULL;
		i++;
	}
	return (1);
}
