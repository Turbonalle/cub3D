
#include "../incl/cub3d.h"

static ray_t	*init_ray(double dir_to_enemy)
{
	ray_t	*ray;

	ray = malloc(sizeof(ray_t));
	if (!ray)
		return (NULL);
	ray->angle = to_radians(dir_to_enemy);
	ray->length = 0;
	ray->target = 0;
	ray->wall = 0;
	ray->end.x = 0;
	ray->end.y = 0;
	return (ray);
}

int	check_if_door_open(cub3d_t *cub3d, int xcoord, int ycoord)
{
	char	index;

	index = cub3d->level->map[ycoord][xcoord];
	if (all_keys_found(cub3d, index - 'A'))
		return (1);
	return (0);
}

static int	wall_or_door_found(cub3d_t *cub3d, vector_t vMapCheck)
{
	if (vMapCheck.x >= 0
		&& vMapCheck.x < cub3d->level->map_columns
		&& vMapCheck.y >= 0
		&& vMapCheck.y < cub3d->level->map_rows
		&& cub3d->level->map[vMapCheck.y][vMapCheck.x] == WALL)
		return (1);
	if (vMapCheck.x >= 0
		&& vMapCheck.x < cub3d->level->map_columns && vMapCheck.y >= 0
		&& vMapCheck.y < cub3d->level->map_rows
		&& (cub3d->level->map[vMapCheck.y][vMapCheck.x] == 'A'
		|| cub3d->level->map[vMapCheck.y][vMapCheck.x] == 'B'
		|| cub3d->level->map[vMapCheck.y][vMapCheck.x] == 'C'
		|| cub3d->level->map[vMapCheck.y][vMapCheck.x] == 'D'))
	{
		if (dist_between(vMapCheck, cub3d->player.pos) > 4)
			return (1);
		if (check_if_door_open(cub3d, vMapCheck.x, vMapCheck.y))
			return (0);
		else
			return (1);
	}
	return (0);
}

static int	ray_to_enemy(cub3d_t *cub3d, double dir_to_enemy, int i)
{
	dvector_t		vRayDir;
	dvector_t		vRayUnitStepSize;
	dvector_t		vRayLength1D;
	double			max_dist;
	vector_t		vMapCheck;
	vector_t		vStep;
	ray_t			*ray;

	vRayDir.x = cos(to_radians(dir_to_enemy));
	vRayDir.y = sin(to_radians(dir_to_enemy));
	max_dist = sqrt(pow(cub3d->player.pos.x - cub3d->enemy[i].pos.x, 2) + pow(cub3d->player.pos.y - cub3d->enemy[i].pos.y, 2));
	vMapCheck.x = (int)cub3d->player.pos.x;
	vMapCheck.y = (int)cub3d->player.pos.y;
	vRayUnitStepSize = init_step_size(to_radians(dir_to_enemy));
	vStep = init_v_step(dir_to_enemy);
	vRayLength1D = init_ray_1D_length(cub3d->player.pos, dir_to_enemy, vMapCheck, vRayUnitStepSize);
	ray = init_ray(dir_to_enemy);
	if (!ray)
		return (0);
	while (ray->length < max_dist)
	{
		 if (wall_or_door_found(cub3d, vMapCheck))
		{
			free(ray);
			return (0);
		}
		adjust(&vMapCheck, ray, vStep, &vRayLength1D);
		adjust_no_flag(&vRayLength1D, vRayUnitStepSize);
	}
	free(ray);
	return (1);
}

static int ray_to_distraction(cub3d_t *cub3d, double dir_to_distraction, int i)
{
	dvector_t		vRayDir;
	dvector_t		vRayUnitStepSize;
	dvector_t		vRayLength1D;
	double			max_dist;
	vector_t		vMapCheck;
	vector_t		vStep;
	ray_t			*ray;

	vRayDir.x = cos(to_radians(dir_to_distraction));
	vRayDir.y = sin(to_radians(dir_to_distraction));
	max_dist = sqrt(pow(cub3d->player.pos.x - cub3d->level->distractions[i].pos.x, 2) + pow(cub3d->player.pos.y - cub3d->level->distractions[i].pos.y, 2));
	vMapCheck.x = (int)cub3d->player.pos.x;
	vMapCheck.y = (int)cub3d->player.pos.y;
	vRayUnitStepSize = init_step_size(to_radians(dir_to_distraction));
	vStep = init_v_step(dir_to_distraction);
	vRayLength1D = init_ray_1D_length(cub3d->player.pos, dir_to_distraction, vMapCheck, vRayUnitStepSize);
	ray = init_ray(dir_to_distraction);
	if (!ray)
		return (0);
	while (ray->length < max_dist)
	{
		if (wall_or_door_found(cub3d, vMapCheck))
		{
			free(ray);
			return (0);
		}
		adjust(&vMapCheck, ray, vStep, &vRayLength1D);
		adjust_no_flag(&vRayLength1D, vRayUnitStepSize);
	}
	free(ray);
	return (1);
}

void	draw_enemy(cub3d_t *cub3d, double dir_to_enemy, int index)
{
	double	dir_as_rad;
	int		i;

	i = 1;
	dir_as_rad = to_radians(dir_to_enemy);

	while (i < (int)cub3d->img->width - 1)
	{
		if (dir_as_rad >= cub3d->rays[i].angle
			&& dir_as_rad < cub3d->rays[i + 1].angle)
			break ;
			// printf("dir as ray is %f, Rays are %f and %f\n",dir_as_rad, cub3d->rays[i].angle, cub3d->rays[i + 1].angle);
		i++;
	}
	if (dir_as_rad == 0)
	{
		i = 1;
		while (i < (int)cub3d->img->width - 1)
		{
			if (cub3d->rays[i].angle > cub3d->rays[i + 1].angle)
				break ;
			i++;
		}
	}
	// TODO: pass enemy to this function instead of index
	// cub3d->enemy[index].dist_to_player = sqrt(pow(cub3d->enemy[index].pos.x - cub3d->player.pos.x, 2) + pow(cub3d->enemy[index].pos.y - cub3d->player.pos.y, 2));
	cub3d->enemy[index].dist_to_player = dist_between_d_vectors(cub3d->enemy[index].pos, cub3d->player.pos);
	cub3d->enemy[index].pos_screen.x = i;
	cub3d->enemy[index].pos_screen.y = cub3d->img->height / 2 + (cub3d->img->height / 2) / cub3d->enemy[index].dist_to_player * 2;
}

void draw_distraction(cub3d_t *cub3d, double dir_to_distraction, int index)
{
	double	dir_as_rad;
	int		i;

	i = 1;
	dir_as_rad = to_radians(dir_to_distraction);

	while (i < (int)cub3d->img->width - 1)
	{
		if (dir_as_rad >= cub3d->rays[i].angle
			&& dir_as_rad < cub3d->rays[i + 1].angle)
			break ;
		i++;
	}
	if (dir_as_rad == 0)
	{
		i = 1;
		while (i < (int)cub3d->img->width - 1)
		{
			if (cub3d->rays[i].angle > cub3d->rays[i + 1].angle)
				break ;
			i++;
		}
	}
	cub3d->level->distractions[index].dist_to_player = dist_between_d_vectors(cub3d->level->distractions[index].pos, cub3d->player.pos);
	cub3d->level->distractions[index].pos_screen.x = i;
	cub3d->level->distractions[index].pos_screen.y = cub3d->img->height / 2 + (cub3d->img->height / 2) / cub3d->level->distractions[index].dist_to_player * 2;
}

static void	see_enemy(cub3d_t *cub3d, int i)
{
	double	angle_min;
	double	angle_max;
	double	dir_to_enemy;

	angle_min = within_360(cub3d->player.angle * 180 / M_PI - cub3d->fov / 2);
	angle_max = within_360(cub3d->player.angle * 180 / M_PI + cub3d->fov / 2);
	dir_to_enemy = within_360((atan2(cub3d->enemy[i].pos.y - cub3d->player.pos.y, cub3d->enemy[i].pos.x - cub3d->player.pos.x) * 180 / M_PI));
	cub3d->enemy[i].visible = FALSE;
	if (angle_max < angle_min)	// check if 0 radians is within the fov
	{
		if (cub3d->fov < 360 && dir_to_enemy > angle_max && dir_to_enemy < angle_min)	// check if enemy is outside the fov
		{
			if (cub3d->enemy[i].is_hunting)
			{
				enemy_cursor(cub3d, dir_to_enemy, dist_between_d_vectors(cub3d->enemy[i].pos, cub3d->player.pos));
			}
		}
		else if (ray_to_enemy(cub3d, dir_to_enemy, i))	// enemy is within the fov
		{
			cub3d->enemy[i].visible = TRUE;
			draw_enemy(cub3d, dir_to_enemy, i);
		}
	}
	else
	{
		if (cub3d->fov < 360 && (dir_to_enemy < angle_min || dir_to_enemy > angle_max))	// check if enemy is outside the fov
		{
			if (cub3d->enemy[i].is_hunting)
			{
				enemy_cursor(cub3d, dir_to_enemy, dist_between_d_vectors(cub3d->enemy[i].pos, cub3d->player.pos));
			}
		}
		else if (ray_to_enemy(cub3d, dir_to_enemy, i))	// enemy is within the fov
		{
			cub3d->enemy[i].visible = TRUE;
			draw_enemy(cub3d, dir_to_enemy, i);
		}
	}
	return ;
}

// TODO: remove camelKey
static int	ray_to_key(cub3d_t *cub3d, double dir_to_key, key_node_t *temp)
{
	dvector_t		vRayDir;
	dvector_t		vRayUnitStepSize;
	dvector_t		vRayLength1D;
	double			max_dist;
	vector_t		vMapCheck;
	vector_t		vStep;
	ray_t			*ray;

	vRayDir.x = cos(to_radians(dir_to_key));
	vRayDir.y = sin(to_radians(dir_to_key));
	max_dist = sqrt(pow(cub3d->player.pos.x - temp->pos.x, 2) + pow(cub3d->player.pos.y - temp->pos.y, 2));
	vMapCheck.x = (int)cub3d->player.pos.x;
	vMapCheck.y = (int)cub3d->player.pos.y;
	vRayUnitStepSize = init_step_size(to_radians(dir_to_key));
	vStep = init_v_step(dir_to_key);
	vRayLength1D = init_ray_1D_length(cub3d->player.pos, dir_to_key, vMapCheck, vRayUnitStepSize);
	ray = init_ray(dir_to_key);
	if (!ray)
		return (0);
	while (ray->length < max_dist)
	{
		if (wall_or_door_found(cub3d, vMapCheck))
		{
			free(ray);
			return (0);
		}
		adjust(&vMapCheck, ray, vStep, &vRayLength1D);
		adjust_no_flag(&vRayLength1D, vRayUnitStepSize);
	}
	free(ray);
	return (1);
}

static void	draw_key(cub3d_t *cub3d, double dir_to_key, key_node_t *key)
{
	double	dir_as_rad;
	int		i;

	i = 1;
	dir_as_rad = to_radians(dir_to_key);
	key->visible = TRUE;
	while (i < (int)cub3d->img->width - 1)
	{
		if (dir_as_rad == cub3d->rays[i].angle)
			break ;
		if (dir_as_rad > cub3d->rays[i].angle
			&& dir_as_rad < cub3d->rays[i + 1].angle)
			break ;
		i++;
	}

	key->dist_to_player = sqrt(pow(key->pos.x - cub3d->player.pos.x, 2)
			+ pow(key->pos.y - cub3d->player.pos.y, 2));
	key->pos_screen.x = i;
	key->pos_screen.y = cub3d->img->height / 2
		+ (cub3d->img->height / 2) / key->dist_to_player * 2;
}

static void	see_key(cub3d_t *cub3d, double dir_to_key, key_node_t *key)
{
	double	angle_min;
	double	angle_max;

	angle_min = within_360(cub3d->player.angle * 180 / M_PI - cub3d->fov / 2);
	angle_max = within_360(cub3d->player.angle * 180 / M_PI + cub3d->fov / 2);
	key->visible = FALSE;
	if (angle_max < angle_min)
	{
		if (cub3d->fov < 360 && dir_to_key > angle_max && dir_to_key < angle_min)
			return ;
		else if (ray_to_key(cub3d, dir_to_key, key))
			draw_key(cub3d, dir_to_key, key);
	}
	else
	{
		if (cub3d->fov < 360 && (dir_to_key < angle_min || dir_to_key > angle_max))
			return ;
		else if (ray_to_key(cub3d, dir_to_key, key))
			draw_key(cub3d, dir_to_key, key);
	}
	return ;
}

static void see_distraction(cub3d_t *cub3d, double dir_to_distraction, int i)
{
	double	angle_min;
	double	angle_max;

	angle_min = within_360(cub3d->player.angle * 180 / M_PI - cub3d->fov / 2);
	angle_max = within_360(cub3d->player.angle * 180 / M_PI + cub3d->fov / 2);
	cub3d->level->distractions[i].visible = FALSE;
	if (angle_max < angle_min)
	{
		if (cub3d->fov < 360 && dir_to_distraction > angle_max && dir_to_distraction < angle_min)
			return ;
		else if (ray_to_distraction(cub3d, dir_to_distraction, i))
		{
			cub3d->level->distractions[i].visible = TRUE;
			draw_distraction(cub3d, dir_to_distraction, i);
		}
			
	}
	else
	{
		if (cub3d->fov < 360 && (dir_to_distraction < angle_min || dir_to_distraction > angle_max))
			return ;
		else if (ray_to_distraction(cub3d, dir_to_distraction, i))
		{
			cub3d->level->distractions[i].visible = TRUE;
			draw_distraction(cub3d, dir_to_distraction, i);
		}
	}
	return ;
}

static void see_keys(cub3d_t *cub3d, int i)
{
	double		dir_to_key;
	key_node_t	*temp;

	temp = cub3d->level->key_groups[i].keys;
	while (temp)
	{
		dir_to_key = within_360((atan2(temp->pos.y - cub3d->player.pos.y,
						temp->pos.x - cub3d->player.pos.x) * 180 / M_PI));
		if (temp->collected == 0)
			see_key(cub3d, dir_to_key, temp);
		temp = temp->next;
	}
}

static void check_distraction(cub3d_t *cub3d, int i)
{
	double		dir_to_distraction;

	dir_to_distraction = within_360((atan2(cub3d->level->distractions[i].pos.y - cub3d->player.pos.y, cub3d->level->distractions[i].pos.x - cub3d->player.pos.x) * 180 / M_PI));
	if (cub3d->level->distractions[i].collected == FALSE)
		see_distraction(cub3d, dir_to_distraction, i);
}

void	draw_enemies(cub3d_t *cub3d)
{
	int	i;

	i = 0;
	while (i < cub3d->num_enemies)
	{
		see_enemy(cub3d, i);
		i++;
	}
	i = 0;
	while (i < NUM_DOORS_MAX)
	{
		if (cub3d->level->key_groups[i].num_keys_total)
		{
			see_keys(cub3d, i);
		}
		i++;
	}
	i = 0;
	while (i < cub3d->level->num_distractions + cub3d->player.thrown)
	{
		check_distraction(cub3d, i);
		i++;
	}
}
