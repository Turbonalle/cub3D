#include "../incl/cub3d.h"


// int find_end_point(cub3d_t *cub3d, player_t *player, double radians, dvector_t *end)
// {
// 	dvector_t vRayStartingCell;
// 	dvector_t vRayUnitStepSize;
// 	dvector_t vRayLength1D;
// 	dvector_t vRayDir;
// 	vector_t vMapCheck;
// 	vector_t vStep;
// 	int end_found = FALSE;

// 	vRayDir.x = cos(radians);
// 	vRayDir.y = sin(radians);
// 	if (vRayDir.x == 0 || vRayDir.y == 0)
// 		return (FAIL);

// 	vRayStartingCell.x = player->pos.x / map->cell_size;
// 	vRayStartingCell.y = player->pos.y / map->cell_size;

// 	vRayUnitStepSize.x = sqrt(1 + (vRayDir.y / vRayDir.x) * (vRayDir.y / vRayDir.x)) * map->cell_size;
// 	vRayUnitStepSize.y = sqrt(1 + (vRayDir.x / vRayDir.y) * (vRayDir.x / vRayDir.y)) * map->cell_size;


// 	vMapCheck.x = (int)vRayStartingCell.x;
// 	vMapCheck.y = (int)vRayStartingCell.y;


// 	if (vRayDir.x < 0)
// 	{
// 		vStep.x = -1;
// 		vRayLength1D.x = (vRayStartingCell.x - vMapCheck.x) * vRayUnitStepSize.x;
// 	}
// 	else
// 	{
// 		vStep.x = 1;
// 		vRayLength1D.x = (vMapCheck.x + 1.0 - vRayStartingCell.x) * vRayUnitStepSize.x;
// 	}
// 	if (vRayDir.y < 0)
// 	{
// 		vStep.y = -1;
// 		vRayLength1D.y = (vRayStartingCell.y - vMapCheck.y) * vRayUnitStepSize.y;
// 	}
// 	else
// 	{
// 		vStep.y = 1;
// 		vRayLength1D.y = (vMapCheck.y + 1.0 - vRayStartingCell.y) * vRayUnitStepSize.y;
// 	}

	
// 	double dist = 0;
// 	double max_dist = sqrt(WIDTH * WIDTH + HEIGHT * HEIGHT);
// 	int wall_flag = 0;
// 	while (!end_found && dist < max_dist)
// 	{
// 		if (vRayLength1D.x < vRayLength1D.y)
// 		{
// 			vMapCheck.x += vStep.x;
// 			dist = vRayLength1D.x;
// 			vRayLength1D.x += vRayUnitStepSize.x;
// 			wall_flag = 1;
// 		}
// 		else
// 		{
// 			vMapCheck.y += vStep.y;
// 			dist = vRayLength1D.y;
// 			vRayLength1D.y += vRayUnitStepSize.y;
// 			wall_flag = 0;
// 		}
// 		if (vMapCheck.x >= 0 && vMapCheck.x < cub3d->map_columns && vMapCheck.y >= 0 && vMapCheck.y < cub3d->map_rows && map->grid_relative[vMapCheck.y][vMapCheck.x].value == 1)
// 		{
			
// 			end->x = player->pos.x + vRayDir.x * dist;
// 			end->y = player->pos.y + vRayDir.y * dist;
// 			end_found = TRUE;
// 		}
// 	}
// 	if (wall_flag == 1 && player->pos.x < end->x)
// 		return (WEST);
// 	else if (wall_flag == 1 && end->x < player->pos.x)
// 		return (EAST);
// 	else if (wall_flag == 0 && player->pos.y < end->y)
// 		return (NORTH);
// 	else
// 		return (SOUTH);
// }

// void draw_rays(cub3d_t *cub3d)
// {
// 	dvector_t end;
// 	double radians;
// 	int rays;
// 	int i;

// 	rays = WIDTH;
// 	i = 0;
// 	while (++i <= rays)
// 	{
// 		radians = (2 * M_PI) * i / rays;
// 		find_end_point(cub3d->map, &cub3d->player, radians, &end);
// 		draw_line(cub3d->img, cub3d->player.pos, end, SADDLEBROWN);
// 	}
// }
