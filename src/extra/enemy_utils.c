
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

static int	door_found(cub3d_t *cub3d, vector_t vMapCheck)
{
	if (vMapCheck.x >= 0 && vMapCheck.x < cub3d->level->map_columns && vMapCheck.y >= 0
		&& vMapCheck.y < cub3d->level->map_rows
		&& (cub3d->level->map[vMapCheck.y][vMapCheck.x] == 'A'
		|| cub3d->level->map[vMapCheck.y][vMapCheck.x] == 'B'
		|| cub3d->level->map[vMapCheck.y][vMapCheck.x] == 'C'
		|| cub3d->level->map[vMapCheck.y][vMapCheck.x] == 'D'
		|| cub3d->level->map[vMapCheck.y][vMapCheck.x] == '-'
		|| cub3d->level->map[vMapCheck.y][vMapCheck.x] == '|'))
	{
		if (dist_between(vMapCheck, cub3d->player.pos) > 3)
			return (1);
		if (cub3d->level->map[vMapCheck.y][vMapCheck.x] == '-' || cub3d->level->map[vMapCheck.y][vMapCheck.x] == '|')
			return (0);
		if (cub3d->level->map[vMapCheck.y][vMapCheck.x] == 'A' && all_keys_found(cub3d, 0) == 1)
			return (0);
		if (cub3d->level->map[vMapCheck.y][vMapCheck.x] == 'B' && all_keys_found(cub3d, 1) == 1)
			return (0);
		if (cub3d->level->map[vMapCheck.y][vMapCheck.x] == 'C' && all_keys_found(cub3d, 2) == 1)
			return (0);
		if (cub3d->level->map[vMapCheck.y][vMapCheck.x] == 'D' && all_keys_found(cub3d, 3) == 1)
			return (0);
		else
			return (1);
	}
	return (0);
}

static int	wall_found(cub3d_t *cub3d, vector_t vMapCheck)
{
	return (vMapCheck.x >= 0
		&& vMapCheck.x < cub3d->level->map_columns
		&& vMapCheck.y >= 0
		&& vMapCheck.y < cub3d->level->map_rows
		&& cub3d->level->map[vMapCheck.y][vMapCheck.x] == WALL);
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
	vRayUnitStepSize.x = sqrt(1 + (vRayDir.y / vRayDir.x) * (vRayDir.y / vRayDir.x));
	vRayUnitStepSize.y = sqrt(1 + (vRayDir.x / vRayDir.y) * (vRayDir.x / vRayDir.y));
	if (vRayDir.x < 0)
	{
		vStep.x = -1;
		vRayLength1D.x = (cub3d->player.pos.x - vMapCheck.x) * vRayUnitStepSize.x;
	}
	else
	{
		vStep.x = 1;
		vRayLength1D.x = (vMapCheck.x + 1.0 - cub3d->player.pos.x) * vRayUnitStepSize.x;
	}
	if (vRayDir.y < 0)
	{
		vStep.y = -1;
		vRayLength1D.y = (cub3d->player.pos.y - vMapCheck.y) * vRayUnitStepSize.y;
	}
	else
	{
		vStep.y = 1;
		vRayLength1D.y = (vMapCheck.y + 1.0 - cub3d->player.pos.y) * vRayUnitStepSize.y;
	}
	ray = init_ray(dir_to_enemy);
	if (!ray)
		return (0);
	while (ray->length < max_dist)
	{
		if (wall_found(cub3d, vMapCheck))
		{
			free(ray);
			return (0);
		}
		if (door_found(cub3d, vMapCheck))
		{
			free(ray);
			return (0);
		}
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
	}
	free(ray);
	return (1);
}

void	draw_enemy(cub3d_t *cub3d, double dir_to_enemy)
{
	dvector_t start;
	dvector_t end;
	double dir_as_rad;
	int	i;
	i = 1;
	dir_as_rad = to_radians(dir_to_enemy);

	while (i < (int)cub3d->img->width - 1)
	{
		if (dir_as_rad > cub3d->rays[i].angle && dir_as_rad < cub3d->rays[i + 1].angle)
			break ;
		i++;
	}
	int j = 0;
	while (j < 10)
	{
		start.x = i + j;
		start.y = cub3d->img->height / 2 - 5;
		end.x = start.x;
		end.y = cub3d->img->height / 2 + 5;
		draw_vertical_line(cub3d->img, start, end, MAGENTA);
		j++;
	}
}

static void	see_enemy(cub3d_t *cub3d, int i)
{
	double	angle_min;
	double	angle_max;
	double	dir_to_enemy;

	angle_min = within_360(cub3d->player.angle * 180 / M_PI - cub3d->fov / 2);
	angle_max = within_360(cub3d->player.angle * 180 / M_PI + cub3d->fov / 2);
	dir_to_enemy = within_360((atan2(cub3d->enemy[i].pos.y - cub3d->player.pos.y, cub3d->enemy[i].pos.x - cub3d->player.pos.x) * 180 / M_PI));
	if (angle_max < angle_min)
	{
		if (dir_to_enemy > angle_max && dir_to_enemy < angle_min)
			return ;
		else if (ray_to_enemy(cub3d, dir_to_enemy, i))
			draw_enemy(cub3d, dir_to_enemy);
	}
	else
	{
		if (dir_to_enemy < angle_min || dir_to_enemy > angle_max)
			return ;
		else if (ray_to_enemy(cub3d, dir_to_enemy, i))
			draw_enemy(cub3d, dir_to_enemy);
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
	vRayUnitStepSize.x = sqrt(1 + (vRayDir.y / vRayDir.x) * (vRayDir.y / vRayDir.x));
	vRayUnitStepSize.y = sqrt(1 + (vRayDir.x / vRayDir.y) * (vRayDir.x / vRayDir.y));
	if (vRayDir.x < 0)
	{
		vStep.x = -1;
		vRayLength1D.x = (cub3d->player.pos.x - vMapCheck.x) * vRayUnitStepSize.x;
	}
	else
	{
		vStep.x = 1;
		vRayLength1D.x = (vMapCheck.x + 1.0 - cub3d->player.pos.x) * vRayUnitStepSize.x;
	}
	if (vRayDir.y < 0)
	{
		vStep.y = -1;
		vRayLength1D.y = (cub3d->player.pos.y - vMapCheck.y) * vRayUnitStepSize.y;
	}
	else
	{
		vStep.y = 1;
		vRayLength1D.y = (vMapCheck.y + 1.0 - cub3d->player.pos.y) * vRayUnitStepSize.y;
	}
	ray = init_ray(dir_to_key);
	if (!ray)
		return (0);
	while (ray->length < max_dist)
	{
		if (wall_found(cub3d, vMapCheck))
		{
			free(ray);
			return (0);
		}
		if (door_found(cub3d, vMapCheck))
		{
			free(ray);
			return (0);
		}
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
	}
	free(ray);
	return (1);
}

static void	draw_key(cub3d_t *cub3d, double dir_to_key, int index)
{
	dvector_t start;
	dvector_t end;
	double dir_as_rad;
	int	i;
	i = 1;
	dir_as_rad = to_radians(dir_to_key);

	while (i < (int)cub3d->img->width - 1)
	{
		if (dir_as_rad > cub3d->rays[i].angle && dir_as_rad < cub3d->rays[i + 1].angle)
			break ;
		i++;
	}

	
	int j = 0;
	while (j < 6)
	{
		start.x = i + j;
		start.y = cub3d->img->height / 2 - 3;
		end.x = start.x;
		end.y = cub3d->img->height / 2 + 3;
		draw_vertical_line(cub3d->img, start, end, ANTIQUE_WHITE);
		j++;
	}
	(void)index;
	//mlx_image_to_window(cub3d->mlx, cub3d->level->key_groups[index].img_key_icon, i, cub3d->img->height / 2);
}

static void	see_key(cub3d_t *cub3d, double dir_to_key, key_node_t *temp, int i)
{
	double	angle_min;
	double	angle_max;

	angle_min = within_360(cub3d->player.angle * 180 / M_PI - cub3d->fov / 2);
	angle_max = within_360(cub3d->player.angle * 180 / M_PI + cub3d->fov / 2);
	if (angle_max < angle_min)
	{
		if (dir_to_key > angle_max && dir_to_key < angle_min)
			return ;
		else if (ray_to_key(cub3d, dir_to_key, temp))
			draw_key(cub3d, dir_to_key, i);
	}
	else
	{
		if (dir_to_key < angle_min || dir_to_key > angle_max)
			return ;
		else if (ray_to_key(cub3d, dir_to_key, temp))
			draw_key(cub3d, dir_to_key, i);
	}
	return ;
}

static void see_keys(cub3d_t *cub3d, int i)
{
	double	dir_to_key;
	key_node_t	*temp;

	temp = cub3d->level->key_groups[i].keys;
	while (temp)
	{
		dir_to_key = within_360((atan2(temp->pos.y - cub3d->player.pos.y, temp->pos.x - cub3d->player.pos.x) * 180 / M_PI));
		if (temp->collected == 0)
			see_key(cub3d, dir_to_key, temp, i);
		temp = temp->next;
	}
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
}
