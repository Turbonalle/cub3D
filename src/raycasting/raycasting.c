#include "../incl/cub3d.h"

static int wall_found(cub3d_t *cub3d, vector_t vMapCheck)
{
	return (vMapCheck.x >= 0
			&& vMapCheck.x < cub3d->map_columns
			&& vMapCheck.y >= 0
			&& vMapCheck.y < cub3d->map_rows
			&& cub3d->map[vMapCheck.y][vMapCheck.x] == WALL);
}

 //-----------------------------------------------------------------------------

static void update_end(cub3d_t *cub3d, dvector_t *vRayDir, ray_t *ray, int *end_found)
{
	ray->end.x = cub3d->minimap.player_pos.x + (*vRayDir).x * ray->length;
	ray->end.y = cub3d->minimap.player_pos.y + (*vRayDir).y * ray->length;
	*end_found = TRUE;
}

//------------------------------------------------------------------------------

static void set_wall_direction(ray_t *ray, player_t *player, int wall_flag)
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

int raycast(cub3d_t *cub3d, player_t *player, ray_t *ray)
{
	dvector_t vRayUnitStepSize;
	dvector_t vRayLength1D;
	dvector_t vRayDir;
	vector_t vMapCheck;
	vector_t vStep;
	int end_found = FALSE;

	vRayDir.x = cos(ray->angle);
	vRayDir.y = sin(ray->angle);
	if (vRayDir.x == 0 || vRayDir.y == 0)
		return (FAIL);

	vRayUnitStepSize.x = sqrt(1 + (vRayDir.y / vRayDir.x) * (vRayDir.y / vRayDir.x));
	vRayUnitStepSize.y = sqrt(1 + (vRayDir.x / vRayDir.y) * (vRayDir.x / vRayDir.y));

	vMapCheck.x = (int)player->pos.x;
	vMapCheck.y = (int)player->pos.y;

	if (vRayDir.x < 0)
	{
		vStep.x = -1;
		vRayLength1D.x = (player->pos.x - vMapCheck.x) * vRayUnitStepSize.x;
	}
	else
	{
		vStep.x = 1;
		vRayLength1D.x = (vMapCheck.x + 1.0 - player->pos.x) * vRayUnitStepSize.x;
	}
	if (vRayDir.y < 0)
	{
		vStep.y = -1;
		vRayLength1D.y = (player->pos.y - vMapCheck.y) * vRayUnitStepSize.y;
	}
	else
	{
		vStep.y = 1;
		vRayLength1D.y = (vMapCheck.y + 1.0 - player->pos.y) * vRayUnitStepSize.y;
	}

	double max_dist = sqrt(cub3d->img->width * cub3d->img->width + cub3d->img->height * cub3d->img->height);
	int wall_flag = 0;
	while (!end_found && ray->length < max_dist)
	{
		if (vRayLength1D.x < vRayLength1D.y)
		{
			vMapCheck.x += vStep.x;
			ray->length = vRayLength1D.x;
			vRayLength1D.x += vRayUnitStepSize.x;
			wall_flag = X;
		}
		else
		{
			vMapCheck.y += vStep.y;
			ray->length = vRayLength1D.y;
			vRayLength1D.y += vRayUnitStepSize.y;
			wall_flag = Y;
		}
		if (wall_found(cub3d, vMapCheck))
		{
			ray->target = cub3d->map[vMapCheck.y][vMapCheck.x];
			update_end(cub3d, &vRayDir, ray, &end_found);
		}
	}
	set_wall_direction(ray, player, wall_flag);
	return (SUCCESS);
}

void raycasting(cub3d_t *cub3d)
{
	double fov_start;
	unsigned int i;

	fov_start = within_two_pi(cub3d->player.angle - to_radians((cub3d->fov / 2)));
	i = 0;
	while (i < cub3d->img->width)
	{
		cub3d->rays[i].angle = within_two_pi(fov_start + to_radians((cub3d->fov * i / cub3d->img->width)));
		raycast(cub3d, &cub3d->player, &cub3d->rays[i]);
		i++;
	}
}