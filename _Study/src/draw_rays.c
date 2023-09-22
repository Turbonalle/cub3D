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
	double_vector_t dvMapCheck;
	vector_t vMapCheck;
	vector_t vStep;
	int end_found = FALSE;

	// get the ray direction
	vRayDir.x = cos(radians);
	vRayDir.y = sin(radians);
	if (vRayDir.x == 0 || vRayDir.y == 0)
		return ;

	// get the ray start
	vRayStartingCell.x = player->pos.x / map->cell_size;
	vRayStartingCell.y = player->pos.y / map->cell_size;

	// get the ray unit step size
	vRayUnitStepSize.x = sqrt(1 + (vRayDir.y / vRayDir.x) * (vRayDir.y / vRayDir.x)) * map->cell_size;
	vRayUnitStepSize.y = sqrt(1 + (vRayDir.x / vRayDir.y) * (vRayDir.x / vRayDir.y)) * map->cell_size;

	// printf("Degrees(%.2f) = %0.f, stepsize = [%f][%f]\n", radians, radians * 180 / M_PI, vRayUnitStepSize.x, vRayUnitStepSize.y);

	dvMapCheck.x = vRayStartingCell.x;
	dvMapCheck.y = vRayStartingCell.y;

	// printf("dvMapCheck = [%f][%f]\n", dvMapCheck.x, dvMapCheck.y);

	vMapCheck.x = (int)vRayStartingCell.x;
	vMapCheck.y = (int)vRayStartingCell.y;

	// printf("vMapCheck = [%d][%d]\n", vMapCheck.x, vMapCheck.y);

	if (vRayDir.x < 0)
	{
		// printf("-X: vRayStartingCell.x = %f\n", vRayStartingCell.x);
		// printf("    vMapCheck.x = %d\n", vMapCheck.x);
		vStep.x = -1;
		vRayLength1D.x = (vRayStartingCell.x - vMapCheck.x) * vRayUnitStepSize.x;
	}
	else
	{
		// printf("+X: vRayStartingCell.x = %f\n", vRayStartingCell.x);
		// printf("    vMapCheck.x = %d\n", vMapCheck.x);
		vStep.x = 1;
		vRayLength1D.x = (vMapCheck.x + 1.0 - vRayStartingCell.x) * vRayUnitStepSize.x;
	}
	if (vRayDir.y < 0)
	{
		// printf("-Y: vRayStartingCell.y = %f\n", vRayStartingCell.y);
		// printf("    vMapCheck.y = %d\n", vMapCheck.y);
		vStep.y = -1;
		vRayLength1D.y = (vRayStartingCell.y - vMapCheck.y) * vRayUnitStepSize.y;
	}
	else
	{
		// printf("+Y: vRayStartingCell.y = %f\n", vRayStartingCell.y);
		// printf("    vMapCheck.y = %d\n", vMapCheck.y);
		vStep.y = 1;
		vRayLength1D.y = (vMapCheck.y + 1.0 - vRayStartingCell.y) * vRayUnitStepSize.y;
	}

	// printf("vRayLength1D.x = %f\n", vRayLength1D.x);
	// printf("vRayLength1D.y = %f\n", vRayLength1D.y);
	
	double dist = 0;
	while (!end_found && dist < fmax(WIDTH, HEIGHT))
	{
		if (vRayLength1D.x < vRayLength1D.y)
		{
			vMapCheck.x += vStep.x;
			dist = vRayLength1D.x;
			vRayLength1D.x += vRayUnitStepSize.x;
			// printf(TERMINAL_GREEN"vRayLength1D.x = %f\n"TERMINAL_RESET, vRayLength1D.x);
		}
		else
		{
			vMapCheck.y += vStep.y;
			dist = vRayLength1D.y;
			vRayLength1D.y += vRayUnitStepSize.y;
			// printf(TERMINAL_RED"vRayLength1D.y = %f\n"TERMINAL_RESET, vRayLength1D.y);
		}
		// printf("vMapCheck = [%d][%d]\n", vMapCheck.x, vMapCheck.y);
		if (vMapCheck.x >= 0 && vMapCheck.x < map->columns && vMapCheck.y >= 0 && vMapCheck.y < map->rows && map->grid[vMapCheck.y][vMapCheck.x] == 1) // Still have to figure out why it works better with x and y swapped...
		{
			end->x = player->pos.x + vRayDir.x * dist;
			end->y = player->pos.y + vRayDir.y * dist;
			// printf(TERMINAL_RED"Wall at [%d][%d]\n"TERMINAL_RESET, vMapCheck.x, vMapCheck.y);
			// printf("end = [%f,%f]\n", end->x, end->y);
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
		// radians = cub3d->player.angle + (2 * M_PI) / 360;
		radians = (2 * M_PI) * i / rays;
		find_end_point(cub3d->map, &cub3d->player, radians, &end);
		draw_line(cub3d->img, cub3d->player.pos, end, WHITE);
	}
}

void connect_player_to_mouse(cub3d_t *cub3d)
{
	double_vector_t mouse;
	int mouse_x;
	int mouse_y;

	mlx_get_mouse_pos(cub3d->mlx, &mouse_x, &mouse_y);
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