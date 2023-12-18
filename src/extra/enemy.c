/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 15:04:10 by slampine          #+#    #+#             */
/*   Updated: 2023/12/18 23:35:18 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static int	door_found(cub3d_t *cub3d, vector_t vMapCheck)
{
	if (vMapCheck.x >= 0 && vMapCheck.x < cub3d->level->map_columns && vMapCheck.y >= 0
		&& vMapCheck.y < cub3d->level->map_rows
		&& (cub3d->level->map[vMapCheck.y][vMapCheck.x] == 'A'
		|| cub3d->level->map[vMapCheck.y][vMapCheck.x] == 'B'
		|| cub3d->level->map[vMapCheck.y][vMapCheck.x] == 'C'
		|| cub3d->level->map[vMapCheck.y][vMapCheck.x] == 'D'))
	{
		if (dist_between(vMapCheck, cub3d->player.pos) > 3)
			return (1);
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
	while (cub3d->level->map[++i])
	{
		j = -1;
		while (cub3d->level->map[i][++j])
		{
			if (ft_strchr(ENEMIES, cub3d->level->map[i][j]))
			{
				cub3d->enemy[enemy_i].pos.x = j + 0.5;
				cub3d->enemy[enemy_i].pos.y = i + 0.5;
				init_enemy_dir(cub3d->enemy, enemy_i, cub3d->level->map[i][j]);
				cub3d->level->map[i][j] = '0';
				return (SUCCESS);
			}
		}
	}
	return (FAIL);
}

static void	update_end(cub3d_t *cub3d, dvector_t vRayDir, ray_t *ray, int i)
{
	ray->end.x = cub3d->enemy[i].pos.x + vRayDir.x * ray->length;
	ray->end.y = cub3d->enemy[i].pos.y + vRayDir.y * ray->length;
}

dvector_t	shorten_vector(dvector_t pos, dvector_t target)
{
	double		multi;
	dvector_t	len_target;
	dvector_t	result;

	multi = (rand() % 81 + 20) / 100.0;
	len_target.x = target.x - pos.x;
	len_target.y = target.y - pos.y;
	result.x = pos.x + (multi * len_target.x);
	result.y = pos.y + (multi * len_target.y);
	return (result);
}

static int	enemy_movement_ray(cub3d_t *cub3d, t_enemy *enemy, int i)
{
	dvector_t		vRayUnitStepSize;
	dvector_t		vRayLength1D;
	dvector_t		vRayDir;
	vector_t		vMapCheck;
	vector_t		vStep;
	ray_t			*ray;
	double			max_dist;

	vRayDir.x = cos((enemy[i].angle));
	vRayDir.y = sin((enemy[i].angle));
	max_dist = sqrt(cub3d->img->width * cub3d->img->width + cub3d->img->height * cub3d->img->height);
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
			update_end(cub3d, vRayDir, ray, i);
			enemy[i].target = ray->end;
			enemy[i].target = shorten_vector(enemy[i].pos, enemy[i].target);
			free(ray);
			return (0);
		}
		if (door_found(cub3d, vMapCheck) && ray->length < max_dist)
		{
			update_end(cub3d, vRayDir, ray, i);
			enemy[i].target = ray->end;
			enemy[i].target = shorten_vector(enemy[i].pos, enemy[i].target);
			free(ray);
			return (0);
		}
	}
	free(ray);
	return (1);
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
	enemy[i].angle = to_radians(ray->angle);
	enemy[i].target = cub3d->player.pos;
	free(ray);
	return (1);
}

static void	enemy_advance(cub3d_t *cub3d, int i)
{
	cub3d->enemy[i].pos.x += cos(cub3d->enemy[i].angle) * ENEMY_SPEED * (1 + cub3d->settings.e_speed);
	cub3d->enemy[i].pos.y += sin(cub3d->enemy[i].angle) * ENEMY_SPEED * (1 + cub3d->settings.e_speed);
}

int	check_if_player_is_seen(cub3d_t *cub3d, int i)
{
	double	angle_min;
	double	angle_max;
	double	at_target;

	at_target = ENEMY_SPEED * (1 + cub3d->settings.e_speed) * 2;
	cub3d->enemy[i].dir_player = within_360(atan2(cub3d->player.pos.y - cub3d->enemy[i].pos.y, cub3d->player.pos.x - cub3d->enemy[i].pos.x) * 180 / M_PI);
	angle_min = within_360(cub3d->enemy[i].angle * 180 / M_PI - 30);
	angle_max = within_360(cub3d->enemy[i].angle * 180 / M_PI + 30);
	if (angle_max < angle_min)
	{
		if (cub3d->enemy[i].dir_player > angle_max && cub3d->enemy[i].dir_player < angle_min)
			return (0);
		else if (enemy_ray(cub3d, cub3d->player, cub3d->enemy, i) && (sqrt(pow(cub3d->player.pos.x - cub3d->enemy[i].pos.x, 2) + pow(cub3d->player.pos.y - cub3d->enemy[i].pos.y, 2)) > at_target))
			return (1);
		else
			return (0);
	}
	else
	{
		if (cub3d->enemy[i].dir_player < angle_min || cub3d->enemy[i].dir_player > angle_max)
			return (0);
		else if (enemy_ray(cub3d, cub3d->player, cub3d->enemy, i) && (sqrt(pow(cub3d->player.pos.x - cub3d->enemy[i].pos.x, 2) + pow(cub3d->player.pos.y - cub3d->enemy[i].pos.y, 2)) > at_target))
			return (1);
		else
			return (0);
	}
}

static int	enemy_ray_to_distraction(cub3d_t *cub3d, dvector_t distraction, double dir_to_distraction, int i)
{
	dvector_t		vRayUnitStepSize;
	dvector_t		vRayLength1D;
	dvector_t		vRayDir;
	vector_t		vMapCheck;
	vector_t		vStep;
	ray_t			*ray;
	double			max_dist;

	vRayDir.x = cos(to_radians(dir_to_distraction));
	vRayDir.y = sin(to_radians(dir_to_distraction));
	max_dist = sqrt(pow(distraction.x - cub3d->enemy[i].pos.x, 2) + pow(distraction.y - cub3d->enemy[i].pos.y, 2));
	vMapCheck.x = (int)cub3d->enemy[i].pos.x;
	vMapCheck.y = (int)cub3d->enemy[i].pos.y;
	vRayUnitStepSize.x = sqrt(1 + (vRayDir.y / vRayDir.x) * (vRayDir.y / vRayDir.x));
	vRayUnitStepSize.y = sqrt(1 + (vRayDir.x / vRayDir.y) * (vRayDir.x / vRayDir.y));
	if (vRayDir.x < 0)
	{
		vStep.x = -1;
		vRayLength1D.x = (cub3d->enemy[i].pos.x - vMapCheck.x) * vRayUnitStepSize.x;
	}
	else
	{
		vStep.x = 1;
		vRayLength1D.x = (vMapCheck.x + 1.0 - cub3d->enemy[i].pos.x) * vRayUnitStepSize.x;
	}
	if (vRayDir.y < 0)
	{
		vStep.y = -1;
		vRayLength1D.y = (cub3d->enemy[i].pos.y - vMapCheck.y) * vRayUnitStepSize.y;
	}
	else
	{
		vStep.y = 1;
		vRayLength1D.y = (vMapCheck.y + 1.0 - cub3d->enemy[i].pos.y) * vRayUnitStepSize.y;
	}
	ray = init_ray(cub3d->enemy, i);
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
	cub3d->enemy[i].angle = to_radians(ray->angle);
	cub3d->enemy[i].target = cub3d->player.pos;
	free(ray);
	return (1);
}

int	distraction(cub3d_t *cub3d, int i)
{
	dvector_t	distraction;
	double		dir_to_distraction;
	double		angle_min;
	double		angle_max;
	double		at_target;

	// distraction = cub3d->level->distraction;
	distraction = cub3d->player.pos;
	dir_to_distraction = within_360(atan2(distraction.y - cub3d->enemy[i].pos.y, distraction.x - cub3d->enemy[i].pos.x) * 180 / M_PI);
	angle_min = within_360(cub3d->enemy[i].angle * 180 / M_PI - 30);
	angle_max = within_360(cub3d->enemy[i].angle * 180 / M_PI + 30);
	at_target = ENEMY_SPEED * (1 + cub3d->settings.e_speed) * 2;
	if (angle_max < angle_min)
	{
		if (dir_to_distraction > angle_max && dir_to_distraction < angle_min)
			return (0);
		else if (enemy_ray_to_distraction(cub3d, distraction, dir_to_distraction, i) && (sqrt(pow(distraction.x - cub3d->enemy[i].pos.x, 2) + pow(distraction.y - cub3d->enemy[i].pos.y, 2)) > at_target))
			return (1);
		else
			return (0);
	}
	else
	{
		if (dir_to_distraction < angle_min || dir_to_distraction > angle_max)
			return (0);
		else if (enemy_ray_to_distraction(cub3d, distraction, dir_to_distraction, i) && (sqrt(pow(distraction.x - cub3d->enemy[i].pos.x, 2) + pow(distraction.y - cub3d->enemy[i].pos.y, 2)) > at_target))
			return (1);
		else
			return (0);
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
		if (cub3d->run_time > cub3d->enemy[i].freeze_start + ENEMY_FREEZE)
		{
			if (check_if_player_is_seen(cub3d, i))
			{
				enemy_advance(cub3d, i);
				cub3d->enemy[i].is_walking = 1;
				if (sqrt(pow(cub3d->player.pos.x - cub3d->enemy[i].pos.x, 2) + pow(cub3d->player.pos.y - cub3d->enemy[i].pos.y, 2)) < 1)
				{
					cub3d->enemy[i].freeze_start = cub3d->run_time;
					printf("You were caught at time %f\n",cub3d->run_time);
					player_is_hit(cub3d);
				}
			}
			else if (distraction(cub3d, i))
			{
				enemy_advance(cub3d, i);
				cub3d->enemy[i].is_walking = 1;
				if (sqrt(pow(cub3d->enemy[i].target.x - cub3d->enemy[i].pos.x, 2) + pow(cub3d->enemy[i].target.y - cub3d->enemy[i].pos.y, 2)) < at_target)
					cub3d->enemy[i].is_walking = 0;
			}
			else if (cub3d->enemy[i].is_walking)
			{
				enemy_advance(cub3d, i);
				cub3d->enemy[i].is_walking = 1;
				if (sqrt(pow(cub3d->enemy[i].target.x - cub3d->enemy[i].pos.x, 2) + pow(cub3d->enemy[i].target.y - cub3d->enemy[i].pos.y, 2)) < at_target)
					cub3d->enemy[i].is_walking = 0;
			}
			else
			{
				if (cub3d->enemy[i].is_spinning == 0 && cub3d->settings.e_behaviour < 2)
				{
					cub3d->enemy[i].angle_start = within_two_pi(cub3d->enemy[i].angle - ENEMY_ROT_SPEED * M_PI / 180);
					cub3d->enemy[i].is_spinning = 1;
				}
				cub3d->enemy[i].angle = within_two_pi(cub3d->enemy[i].angle + ENEMY_ROT_SPEED * M_PI / 180);
				if ((fabs(cub3d->enemy[i].angle - cub3d->enemy[i].angle_start) < M_PI / 180 * ENEMY_ROT_SPEED && cub3d->settings.e_behaviour == 1) || cub3d->settings.e_behaviour == 2)
				{
					cub3d->enemy[i].angle = to_radians(rand() % 360);
					enemy_movement_ray(cub3d, cub3d->enemy, i);
					while (sqrt(pow(cub3d->enemy[i].target.x - cub3d->enemy[i].pos.x, 2) + pow(cub3d->enemy[i].target.y - cub3d->enemy[i].pos.y, 2)) < at_target)
					{
						cub3d->enemy[i].angle = to_radians(rand() % 360);
						enemy_movement_ray(cub3d, cub3d->enemy, i);
					}
					enemy_advance(cub3d, i);
					cub3d->enemy[i].is_walking = 1;
					cub3d->enemy[i].is_spinning = 0;
				}
			}
		}
		if (cub3d->enemy[i].is_walking)
			cub3d->enemy[i].state = WALKING;
		else
			cub3d->enemy[i].state = IDLE;
		i++;
	}
}

int	init_enemy_frames(cub3d_t *cub3d)
{
	int 	i;
	char	*file_path;
	char	*file_name;
	char	*file_name_extension;
	
	// TODO: protect mallocs
	i = 0;
	while (i < NUM_FRAMES_ENEMY_IDLE)
	{
		//TODO: protect mallocs
		file_name = ft_itoa(i + 1);
		file_name_extension = ft_strjoin(file_name, ".png");
		file_path = ft_strjoin(FRAME_PATH_ENEMY_BLUE_IDLE, file_name_extension);
		printf("full file path: %s\n", file_path);
		cub3d->frames_blue_idle[i] = mlx_load_png(file_path);
		free(file_name);
		free(file_name_extension);
		free(file_path);
		i++;
	}
	i = 0;
	while (i < NUM_FRAMES_ENEMY_WALKING)
	{
		//TODO: protect mallocs
		file_name = ft_itoa(i + 1);
		file_name_extension = ft_strjoin(file_name, ".png");
		file_path = ft_strjoin(FRAME_PATH_ENEMY_GREEN_WALKING, file_name_extension);
		printf("full file path: %s\n", file_path);
		cub3d->frames_green_walking[i] = mlx_load_png(file_path);
		free(file_name);
		free(file_name_extension);
		free(file_path);
		i++;
	}
	return(1);
}

int init_enemy(cub3d_t *cub3d)
{
	int	i;

	i = 0;
	cub3d->enemy = malloc(sizeof(t_enemy) * cub3d->num_enemies);
	if (!cub3d->enemy)
		return (0);
	cub3d->curr_frame_index_idle = 0;
	cub3d->prev_frame_index_idle = 0;
	while (i < cub3d->num_enemies)
	{
		enemy_starting_point(cub3d, i);
		cub3d->enemy[i].dir_player = 0;
		cub3d->enemy[i].is_spinning = 0;
		cub3d->enemy[i].is_walking = 0;
		cub3d->enemy[i].dir.x = 0;
		cub3d->enemy[i].dir.y = 0;
		cub3d->enemy[i].freeze_start = 0;
		cub3d->enemy[i].path = NULL;
		cub3d->enemy[i].pos_screen.x = -WIDTH;
		cub3d->enemy[i].pos_screen.y = -HEIGHT;
		cub3d->enemy[i].state = IDLE;
		cub3d->enemy[i].visible = FALSE;
		cub3d->enemy[i].dist_to_player = 100;
		cub3d->enemy[i].img_curr_frame = mlx_new_image(cub3d->mlx, WIDTH, HEIGHT);
		mlx_image_to_window(cub3d->mlx, cub3d->enemy[i].img_curr_frame, 0, 0);
		i++;
	}
	init_enemy_frames(cub3d);
	return (1);
}
