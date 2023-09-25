#include "../incl/raycaster.h"

//------------------------------------------------------------------------------

void player_rotation(player_t *player, double angle)
{
	player->angle += angle;
	if (player->angle < 0)
		player->angle += (2 * M_PI);
	else if (player->angle > (2 * M_PI))
		player->angle -= (2 * M_PI);
	player->dir.x = cos(player->angle);
	player->dir.y = sin(player->angle);
}

//------------------------------------------------------------------------------

int diagonal_movement(player_t player)
{
	return ((player.left == TRUE || player.right == TRUE) &&
		(player.up == TRUE || player.down == TRUE) &&
		!(player.left == TRUE && player.right == TRUE) &&
		!(player.up == TRUE && player.down == TRUE));
}

//------------------------------------------------------------------------------

void player_strafe(player_t *player, double angle, double speed)
{
	if (angle < 0)
		angle += (2 * M_PI);
	else if (angle > (2 * M_PI))
		angle -= (2 * M_PI);
	player->pos.x += cos(angle) * speed;
	player->pos.y += sin(angle) * speed;
}

int is_wall(map_t *map, double_vector_t *pos)
{
	vector_t box;

	box.x = pos->x * map->columns / WIDTH;
	box.y = pos->y * map->rows / HEIGHT;
	if (map->grid_relative[box.y][box.x].value == WALL)
		return (TRUE);
	return (FALSE);
}

void hook_player_movement(void *param)
{
	cub3d_t *cub3d;
	double	movement_direction;
	double	speed;
	int movement;

	cub3d = param;

	movement = FALSE;
	movement_direction = 0;
	if (diagonal_movement(cub3d->player))
		speed = MOVEMENT_SPEED * 0.70710678118;									// 1 / sqrt(2)
	else
		speed = MOVEMENT_SPEED;
	if (cub3d->player.rotate_left == TRUE && cub3d->player.rotate_right == FALSE)
		player_rotation(&cub3d->player, -ROTATION_SPEED);
	else if (cub3d->player.rotate_right == TRUE && cub3d->player.rotate_left == FALSE)
		player_rotation(&cub3d->player, ROTATION_SPEED);
	if (cub3d->player.up == TRUE)
	{
		movement_direction = cub3d->player.angle;
		movement = TRUE;
	}
	if (cub3d->player.down == TRUE)
	{
		movement_direction = (cub3d->player.angle + M_PI);
		if (movement_direction > 2 * M_PI)
			movement_direction -= 2 * M_PI;
		movement = TRUE;
	}
	if (cub3d->player.left == TRUE)
	{
		movement_direction = (cub3d->player.angle - M_PI / 2);
		if (movement_direction < 0)
			movement_direction += 2 * M_PI;
		movement = TRUE;
	}
	if (cub3d->player.right == TRUE)
	{
		movement_direction = (cub3d->player.angle + M_PI / 2);
		if (movement_direction > 2 * M_PI)
			movement_direction -= 2 * M_PI;
		movement = TRUE;
	}
	if (movement == TRUE)
	{
		double_vector_t new_pos;
		// vector_t current_box;
		// vector_t next_box;
		
		new_pos.x = cub3d->player.pos.x + cos(movement_direction) * speed;
		new_pos.y = cub3d->player.pos.y + sin(movement_direction) * speed;
		if (!is_wall(cub3d->map, &new_pos))
		{
			cub3d->player.pos.x = new_pos.x;
			cub3d->player.pos.y = new_pos.y;
		}
		else
		{
			int wall = find_end_point(cub3d->map, &cub3d->player, cub3d->player.angle, &new_pos);
			if (wall == WEST || wall == EAST)
				cub3d->player.pos.y = new_pos.y;
			else if (wall == NORTH || wall == SOUTH)
				cub3d->player.pos.x = new_pos.x;
			// char *s[4] = { "WEST", "SOUTH", "EAST", "NORTH" };
			// printf("Crashed into %s side of the wall\n", s[wall - 1]);
		}
	}
	draw_map(cub3d->img, cub3d->map);
	if (cub3d->rays == TRUE)
		draw_rays(cub3d);
	draw_player(cub3d);
	draw_direction_ray(cub3d);
	if (cub3d->q_pressed == TRUE)
		connect_player_to_mouse(cub3d);

}
