/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 12:14:17 by slampine          #+#    #+#             */
/*   Updated: 2023/11/17 14:09:38 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

static int	wall_found(cub3d_t *cub3d, vector_t vMapCheck)
{
	return (vMapCheck.x >= 0
		&& vMapCheck.x < cub3d->map_columns
		&& vMapCheck.y >= 0
		&& vMapCheck.y < cub3d->map_rows
		&& cub3d->map[vMapCheck.y][vMapCheck.x] == WALL);
}

//-----------------------------------------------------------------------------

static void	update_end(cub3d_t *cub3d, dvector_t *vRayDir, ray_t *ray, int *end_found)
{
	ray->end.x = cub3d->player.pos.x + (*vRayDir).x * ray->length;
	ray->end.y = cub3d->player.pos.y + (*vRayDir).y * ray->length;
	*end_found = TRUE;
}

//------------------------------------------------------------------------------

static void	set_wall_direction(ray_t *ray, player_t *player, int wall_flag)
{
	if (wall_flag == X && player->pos.x < ray->end.x)
		ray->wall = WE;
	else if (wall_flag == X && ray->end.x < player->pos.x)
		ray->wall = EA;
	else if (wall_flag == Y && player->pos.y < ray->end.y)
		ray->wall = NO;
	else
		ray->wall = SO;
}

//------------------------------------------------------------------------------

// int	find_first_horizontal_wall(cub3d_t *cub3d, player_t *player, ray_t *ray)
// {
// 	dvector_t	vRayDir;
// 	dvector_t	deltaH;
// 	vector_t	vMapCheckH;
// 	double		max_dist;

// 	vRayDir.x = cos(ray->angle);
// 	vRayDir.y = sin(ray->angle);
// 	if (vRayDir.x == 0)
// 		return (FAIL);
// 	max_dist = sqrt(cub3d->img->width * cub3d->img->width + cub3d->img->height * cub3d->img->height);
// 	vMapCheckH.y = floor(player->pos.y);
// 	deltaH.y = 1;
// 	if (vRayDir.y > 0)
// 	{
// 		deltaH.y = -1;
// 		vMapCheckH.y++;
// 	}
// 	vMapCheckH.x = player->pos.x + (player->pos.y - vMapCheckH.y) / tan(ray->angle);
// }
// link to graph https://virtual-graph-paper.com/NjY5NTkyNWI5ZDE4
int	raycast(cub3d_t *cub3d, player_t *player, ray_t *ray)
{
	dvector_t	vRayDir;
	dvector_t	deltaH;
	dvector_t	deltaV;
	vector_t	vMapCheckH;
	vector_t	vMapCheckV;
	int			end_found;
	double		max_dist;
	int			wall_flag;

	end_found = FALSE;
	vRayDir.x = cos(ray->angle);
	vRayDir.y = sin(ray->angle);
	if (vRayDir.x == 0 || vRayDir.y == 0)
		return (FAIL);
	max_dist = sqrt(cub3d->img->width * cub3d->img->width + cub3d->img->height * cub3d->img->height);
	wall_flag = 0;
	vMapCheckH.y = ceil(player->pos.y);
	deltaH.y = 1;
	if (vRayDir.y > 0)
	{
		deltaH.y = -1;
		vMapCheckH.y--;
	}
	vMapCheckV.x = ceil(player->pos.x);
	deltaV.x = 1;
	if (vRayDir.x < 0)
	{
		deltaV.x = -1;
		vMapCheckV.x--;
	}
	printf("\nStarting:\nplayer.pos is %f,%f\n",player->pos.x, player->pos.y);
	printf("vRaydir are %f and %f\n",vRayDir.x,vRayDir.y);
	printf("player angle is %f, ray angle is %f\n", player->angle / M_PI * 180, ray->angle / M_PI * 180);
	vMapCheckH.x = player->pos.x + (player->pos.y - vMapCheckH.y) / tan(ray->angle);
	deltaH.x = 1 / tan(ray->angle);
	printf("First horizontal hit at pos %i,%i\n", vMapCheckH.x, vMapCheckH.y);
	printf("deltaHX is %f, deltaHY is %f\n", deltaH.x, deltaH.y);
	printf("Horizontal done\n--------------------\n");
	vMapCheckV.y = player->pos.y + (player->pos.x - vMapCheckV.x) / tan(ray->angle);
	printf("First vertical hit at pos %i,%i\n", vMapCheckV.x, vMapCheckV.y);
	deltaV.y = tan(ray->angle);
	printf("deltaVX is %f, deltaVY is %f\n", deltaV.x, deltaV.y);
	printf("Vertical done\n--------------------");
	while (!end_found && ray->length < max_dist)
	{
		if (wall_found(cub3d, vMapCheckH))
		{
			printf("\n\nFound horizontal wall\n\n");
			ray->target = cub3d->map[vMapCheckH.y][vMapCheckH.x];
			wall_flag = 0;
			update_end(cub3d, &vRayDir, ray, &end_found);
		}
		else if (wall_found(cub3d, vMapCheckV))
		{
			printf("\n\nFound vertical wall\n\n");
			ray->target = cub3d->map[vMapCheckV.y][vMapCheckV.x];
			wall_flag = 1;
			update_end(cub3d, &vRayDir, ray, &end_found);
		}
		vMapCheckH.x += deltaH.x;
		vMapCheckH.y += deltaH.y;
		vMapCheckV.x += deltaV.x;
		vMapCheckV.y += deltaV.y;
	}
	set_wall_direction(ray, player, wall_flag);
	ray->length = 1;
	return (SUCCESS);
}

void	raycasting(cub3d_t *cub3d)
{
	double			fov_start;
	unsigned int	i;

	fov_start = within_two_pi(cub3d->player.angle - to_radians((cub3d->fov / 2)));
	i = 0;
	while (i < cub3d->img->width)
	{
		cub3d->rays[i].angle = within_two_pi(fov_start + to_radians((cub3d->fov * i / cub3d->img->width)));
		raycast(cub3d, &cub3d->player, &cub3d->rays[i]);
		i++;
	}
}
