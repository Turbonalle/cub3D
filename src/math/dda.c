#include "../incl/cub3d.h"

int wall_found(cub3d_t *cub3d, vector_t vMapCheck)
{
	return (vMapCheck.x >= 0
			&& vMapCheck.x < cub3d->map_columns
			&& vMapCheck.y >= 0
			&& vMapCheck.y < cub3d->map_rows
			&& cub3d->map[vMapCheck.y][vMapCheck.x] == WALL);
}

 //-----------------------------------------------------------------------------

void update_end(cub3d_t *cub3d, dvector_t *vRayDir, dvector_t *end, double *dist, int *end_found)
{
	end->x = cub3d->minimap.player_pos.x + (*vRayDir).x * *dist * cub3d->minimap.tile_size;
	end->y = cub3d->minimap.player_pos.y + (*vRayDir).y * *dist * cub3d->minimap.tile_size;
	*end_found = TRUE;
}

//------------------------------------------------------------------------------

int find_end_point(cub3d_t *cub3d, player_t *player, double radians, dvector_t *end)
{
	dvector_t vRayStartingCell;
	dvector_t vRayUnitStepSize;
	dvector_t vRayLength1D;
	dvector_t vRayDir;
	vector_t vMapCheck;
	vector_t vStep;
	int end_found = FALSE;

	vRayDir.x = cos(radians);
	vRayDir.y = sin(radians);
	if (vRayDir.x == 0 || vRayDir.y == 0)
		return (FAIL);

	vRayStartingCell.x = player->pos.x;
	vRayStartingCell.y = player->pos.y;
	vRayUnitStepSize.x = sqrt(1 + (vRayDir.y / vRayDir.x) * (vRayDir.y / vRayDir.x));
	vRayUnitStepSize.y = sqrt(1 + (vRayDir.x / vRayDir.y) * (vRayDir.x / vRayDir.y));

	vMapCheck.x = (int)vRayStartingCell.x;
	vMapCheck.y = (int)vRayStartingCell.y;

	if (vRayDir.x < 0)
	{
		vStep.x = -1;
		vRayLength1D.x = (vRayStartingCell.x - vMapCheck.x) * vRayUnitStepSize.x;
	}
	else
	{
		vStep.x = 1;
		vRayLength1D.x = (vMapCheck.x + 1.0 - vRayStartingCell.x) * vRayUnitStepSize.x;
	}
	if (vRayDir.y < 0)
	{
		vStep.y = -1;
		vRayLength1D.y = (vRayStartingCell.y - vMapCheck.y) * vRayUnitStepSize.y;
	}
	else
	{
		vStep.y = 1;
		vRayLength1D.y = (vMapCheck.y + 1.0 - vRayStartingCell.y) * vRayUnitStepSize.y;
	}

	double dist = 0;
	double max_dist = sqrt(cub3d->img->width * cub3d->img->width + cub3d->img->height * cub3d->img->height);
	int wall_flag = 0;
	while (!end_found && dist < max_dist)
	{
		if (vRayLength1D.x < vRayLength1D.y)
		{
			vMapCheck.x += vStep.x;
			dist = vRayLength1D.x;
			vRayLength1D.x += vRayUnitStepSize.x;
			wall_flag = 1;
		}
		else
		{
			vMapCheck.y += vStep.y;
			dist = vRayLength1D.y;
			vRayLength1D.y += vRayUnitStepSize.y;
			wall_flag = 0;
		}
		if (wall_found(cub3d, vMapCheck))
			update_end(cub3d, &vRayDir, end, &dist, &end_found);
	}
	if (wall_flag == 1 && player->pos.x < end->x)
		return (WE);
	else if (wall_flag == 1 && end->x < player->pos.x)
		return (EA);
	else if (wall_flag == 0 && player->pos.y < end->y)
		return (NO);
	else
		return (SO);
}
