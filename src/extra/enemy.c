/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 15:04:10 by slampine          #+#    #+#             */
/*   Updated: 2023/11/23 13:05:44 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

static ray_t	*init_ray(t_enemy *enemy)
{
	ray_t	*ray;

	ray = malloc(sizeof(ray_t));
	if (!ray)
		return (NULL);
	ray->angle = enemy->dir_player;
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

static int	enemy_starting_point(cub3d_t *cub3d)
{
	int	i;
	int	j;

	i = -1;
	while (cub3d->map[++i])
	{
		j = -1;
		while (cub3d->map[i][++j])
		{
			if (cub3d->map[i][j] == 'F')
			{
				cub3d->enemy->pos.x = j + 0.5;
				cub3d->enemy->pos.y = i + 0.5;
				cub3d->enemy->dir_player = 0;
				return (SUCCESS);
			}
		}
	}
	return (FAIL);
}

static int enemy_ray(cub3d_t *cub3d, player_t player, t_enemy *enemy)
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

	vRayDir.x = cos(enemy->dir_player);
	vRayDir.y = sin(enemy->dir_player);
	max_dist = sqrt(pow(player.pos.x - enemy->pos.x, 2) + pow(player.pos.y - enemy->pos.y, 2));
	vMapCheck.x = (int)enemy->pos.x;
	vMapCheck.y = (int)enemy->pos.y;
	vRayUnitStepSize.x = sqrt(1 + (vRayDir.y / vRayDir.x) * (vRayDir.y / vRayDir.x));
	vRayUnitStepSize.y = sqrt(1 + (vRayDir.x / vRayDir.y) * (vRayDir.x / vRayDir.y));

	if (vRayDir.x < 0)
	{
		vStep.x = -1;
		vRayLength1D.x = (enemy->pos.x - vMapCheck.x) * vRayUnitStepSize.x;
	}
	else
	{
		vStep.x = 1;
		vRayLength1D.x = (vMapCheck.x + 1.0 - enemy->pos.x) * vRayUnitStepSize.x;
	}
	if (vRayDir.y < 0)
	{
		vStep.y = -1;
		vRayLength1D.y = (enemy->pos.y - vMapCheck.y) * vRayUnitStepSize.y;
	}
	else
	{
		vStep.y = 1;
		vRayLength1D.y = (vMapCheck.y + 1.0 - enemy->pos.y) * vRayUnitStepSize.y;
	}
	end_found = 0;
	ray = init_ray(enemy);
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
	cub3d->enemy->dir_player = within_two_pi(atan2(cub3d->player.pos.y - cub3d->enemy->pos.y, cub3d->player.pos.x - cub3d->enemy->pos.x));
	printf("dir_player is %f\n",cub3d->enemy->dir_player * 180 / M_PI);
	if (within_two_pi(cub3d->enemy->angle) > cub3d->enemy->dir_player + M_PI / 6 || within_two_pi(cub3d->enemy->angle) < cub3d->enemy->dir_player - M_PI / 6)
		printf("Remained hidden due to enemy looking other way\n");
	else if (enemy_ray(cub3d, cub3d->player, cub3d->enemy))
		printf("Enemy saw you\n");
	else
		printf("Remained hidden due to wall\n");
}

int init_enemy(cub3d_t *cub3d)
{
	int	num_enemies;

	num_enemies = 1;
	cub3d->enemy = malloc(sizeof(t_enemy) * num_enemies);
	if (!cub3d->enemy)
		return (0);
	enemy_starting_point(cub3d);
	cub3d->enemy->dir_player = atan2(cub3d->player.pos.y - cub3d->enemy->pos.y, cub3d->player.pos.x - cub3d->enemy->pos.x);
	cub3d->enemy->angle = 0;
	cub3d->enemy->is_spinning = 0;
	cub3d->enemy->is_walking = 0;
	cub3d->enemy->dir.x = 0;
	cub3d->enemy->dir.y = 0;
	return (1);
}