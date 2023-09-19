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

void find_end_point(map_t *map, player_t *player, double_vector_t *end)
{
	double_vector_t ray;
	double_vector_t unit;
	double_vector_t length;
	vector_t cell;
	vector_t step;
	int end_found = FALSE;

	if (player->dir.x == 0 || player->dir.y == 0)
		return ;
	ray.x = player->pos.x + player->dir.x;
	ray.y = player->pos.y + player->dir.y;
	unit.x = sqrt(1 + (player->dir.y * player->dir.y) / (player->dir.x * player->dir.x));
	unit.y = sqrt(1 + (player->dir.x * player->dir.x) / (player->dir.y * player->dir.y));
	cell.x = (int)ray.x;
	cell.y = (int)ray.y;

	if (player->dir.x < 0)
	{
		step.x = -1;
		length.x = (ray.x - (float)cell.x) * unit.x;
	}
	else
	{
		step.x = 1;
		length.x = ((float)(cell.x + 1.0) - ray.x) * unit.x;
	}
	if (player->dir.y < 0)
	{
		step.y = -1;
		length.y = (ray.y - cell.y) * unit.y;
	}
	else
	{
		step.y = 1;
		length.y = (cell.y + 1.0 - ray.y) * unit.y;
	} 
	double dist = 0;
	while (!end_found && dist < fmax(WIDTH, HEIGHT))
	{
		if (ray.x < ray.y)
		{
			cell.x += step.x;
			dist = length.x;
			length.x += unit.x;
		}
		else
		{
			cell.y += step.y;
			dist = length.y;
			length.y += unit.y; 
		}
		if (cell.x >= 0 && cell.x < map->columns && cell.y >= 0 && cell.y < map->rows && map->grid[cell.y][cell.x] == 1)
		{
			end->x = cell.x * map->cell_size;
			end->y = cell.y * map->cell_size;
			end_found = TRUE;
		}
	}
}

void draw_rays(cub3d_t *cub3d)
{
	double_vector_t end;
	double angle;
	int rays;
	int i;

	rays = 10;
	i = 0;
	while (++i <= rays)
	{
		angle = rays / i * (2 * M_PI);

		find_end_point(cub3d->map, &cub3d->player, &end);
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

	end.x = cub3d->player.pos.x + cub3d->player.dir.x * 20;
	end.y = cub3d->player.pos.y + cub3d->player.dir.y * 20;
	draw_line(cub3d->img, cub3d->player.pos, end, YELLOW);
}