#include "../incl/raycaster.h"

void draw_line(mlx_image_t *img, double_vector_t start, double_vector_t end, int color)
{
	double x;
	double y;
	double x_increment;
	double y_increment;
	int i;
	int iterations = 600;

	x = start.x;
	y = start.y;
	x_increment = (end.x - start.x) / iterations;
	y_increment = (end.y - start.y) / iterations;
	i = 0;
	while (i < iterations)
	{
		x += x_increment;
		y += y_increment;
		mlx_put_pixel(img, x, y, color);
		i++;
	}
}

void find_end_point(map_t *map, player_t *player, double radians, double_vector_t *end)
{
	double_vector_t vRayStartingCell;
	double_vector_t vRayUnitStepSize;
	double_vector_t vRayLength1D;
	double_vector_t vRayDir;
	vector_t vMapCheck;
	vector_t vStep;
	int end_found = FALSE;

	vRayDir.x = cos(radians);
	vRayDir.y = sin(radians);
	if (vRayDir.x == 0 || vRayDir.y == 0)
		return ;

	vRayStartingCell.x = player->pos.x / map->cell_size;
	vRayStartingCell.y = player->pos.y / map->cell_size;

	vRayUnitStepSize.x = sqrt(1 + (vRayDir.y / vRayDir.x) * (vRayDir.y / vRayDir.x)) * map->cell_size;
	vRayUnitStepSize.y = sqrt(1 + (vRayDir.x / vRayDir.y) * (vRayDir.x / vRayDir.y)) * map->cell_size;


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
	double max_dist = sqrt(WIDTH * WIDTH + HEIGHT * HEIGHT);
	while (!end_found && dist < max_dist)
	{
		if (vRayLength1D.x < vRayLength1D.y)
		{
			vMapCheck.x += vStep.x;
			dist = vRayLength1D.x;
			vRayLength1D.x += vRayUnitStepSize.x;
		}
		else
		{
			vMapCheck.y += vStep.y;
			dist = vRayLength1D.y;
			vRayLength1D.y += vRayUnitStepSize.y;
		}
		if (vMapCheck.x >= 0 && vMapCheck.x < map->columns && vMapCheck.y >= 0 && vMapCheck.y < map->rows && map->grid[vMapCheck.y][vMapCheck.x] == 1)
		{
			end->x = player->pos.x + vRayDir.x * dist;
			end->y = player->pos.y + vRayDir.y * dist;
			end_found = TRUE;
		}
	}
}

void draw_rays(cub3d_t *cub3d)
{
	double_vector_t end;
	double radians;
	int rays;
	int i;

	rays = WIDTH;
	i = 0;
	while (++i <= rays)
	{
		radians = (2 * M_PI) * i / rays;
		find_end_point(cub3d->map, &cub3d->player, radians, &end);
		draw_line(cub3d->img, cub3d->player.pos, end, SADDLEBROWN);
	}
}

void connect_player_to_mouse(cub3d_t *cub3d)
{
	double_vector_t mouse;
	int mouse_x;
	int mouse_y;

	mlx_get_mouse_pos(cub3d->mlx, &mouse_x, &mouse_y);
	if (mouse_x < 0 || mouse_x > WIDTH || mouse_y < 0 || mouse_y > HEIGHT)
		return ;
	mouse.x = mouse_x;
	mouse.y = mouse_y;
	draw_line(cub3d->img, cub3d->player.pos, mouse, YELLOW);
}

void draw_direction_ray(cub3d_t *cub3d)
{
	double_vector_t end;

	end.x = cub3d->player.pos.x + cub3d->player.dir.x * 10;
	end.y = cub3d->player.pos.y + cub3d->player.dir.y * 10;
	draw_line(cub3d->img, cub3d->player.pos, end, YELLOW);
}