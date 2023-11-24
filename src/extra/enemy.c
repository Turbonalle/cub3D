/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 15:04:10 by slampine          #+#    #+#             */
/*   Updated: 2023/11/24 14:22:22 by slampine         ###   ########.fr       */
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

static int	wall_found(cub3d_t *cub3d, vector_t vMapCheck)
{
	return (vMapCheck.x >= 0
		&& vMapCheck.x < cub3d->map_columns
		&& vMapCheck.y >= 0
		&& vMapCheck.y < cub3d->map_rows
		&& cub3d->map[vMapCheck.y][vMapCheck.x] == WALL);
}

void	init_enemy_dir(t_enemy *enemy, int i, char spec)
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

static int enemy_ray(cub3d_t *cub3d, player_t player, t_enemy *enemy, int i)
{
	//enemy_path_t	*path;
	dvector_t		vRayUnitStepSize;
	dvector_t		vRayLength1D;
	dvector_t		vRayDir;
	vector_t		vMapCheck;
	vector_t		vStep;
	ray_t			*ray;
	double			max_dist;
	int				end_found;

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
	end_found = 0;
	ray = init_ray(enemy, i);
	if (!ray)
		return (0);
	while (!end_found && ray->length < max_dist)
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
		if (wall_found(cub3d, vMapCheck))
		{
			free(ray);
			end_found = 1;
			return (0);
		}
	}
	free(ray);
	return (1);
}

void	check_if_player_is_seen(cub3d_t *cub3d)
{
	double	angle_min;
	double	angle_max;
	int		i;

	i = 0;
	while (i < cub3d->num_enemies)
	{
		cub3d->enemy[i].dir_player = within_360(atan2(cub3d->player.pos.y - cub3d->enemy[i].pos.y, cub3d->player.pos.x - cub3d->enemy[i].pos.x) * 180 / M_PI);
		angle_min = within_360(cub3d->enemy[i].angle * 180 / M_PI - 30);
		angle_max = within_360(cub3d->enemy[i].angle * 180 / M_PI + 30);
		printf("Looking between angles %f,%f, player at dir %f\n",angle_min,angle_max,cub3d->enemy[i].dir_player);
		if (cub3d->enemy[i].dir_player < angle_min || cub3d->enemy[i].dir_player > angle_max)
			printf("enemy %i Not looking at you\n", i);
		else if (enemy_ray(cub3d, cub3d->player, cub3d->enemy, i))
			printf("Enemy %i saw you\n", i);
		else
			printf("Remained hidden from enemy %i due to wall\n",i );
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
		i++;
	}
	return (1);
}
