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

void player_strafe(player_t *player, double angle)
{
	if (angle < 0)
		angle += (2 * M_PI);
	else if (angle > (2 * M_PI))
		angle -= (2 * M_PI);
	player->pos.x += cos(angle) * MOVEMENT_SPEED;
	player->pos.y += sin(angle) * MOVEMENT_SPEED;
}

void hook_player_movement(void *param)
{
	cub3d_t *cub3d;
	double	speed;

	cub3d = param;

	if (diagonal_movement(cub3d->player))
		speed = MOVEMENT_SPEED * 0.70710678118;									// 1 / sqrt(2)
	else
		speed = MOVEMENT_SPEED;
	if (cub3d->player.rotate_left == TRUE && cub3d->player.rotate_right == FALSE)
		player_rotation(&cub3d->player, -ROTATION_SPEED);
	else if (cub3d->player.rotate_right == TRUE && cub3d->player.rotate_left == FALSE)
		player_rotation(&cub3d->player, ROTATION_SPEED);
	if (cub3d->player.up == TRUE && cub3d->player.down == FALSE)
	{
		cub3d->player.pos.x += cub3d->player.dir.x * speed;
		cub3d->player.pos.y += cub3d->player.dir.y * speed;
	}
	else if (cub3d->player.up == FALSE && cub3d->player.down == TRUE)
	{
		cub3d->player.pos.x -= cub3d->player.dir.x * speed;
		cub3d->player.pos.y -= cub3d->player.dir.y * speed;
	}
	if (cub3d->player.left == TRUE && cub3d->player.right == FALSE)
	{
		player_strafe(&cub3d->player, cub3d->player.angle - (M_PI / 2));
	}
	else if (cub3d->player.left == FALSE && cub3d->player.right == TRUE)
	{
		player_strafe(&cub3d->player, cub3d->player.angle + (M_PI / 2));
	}
	draw_map(cub3d->img, cub3d->map);
	draw_player(cub3d);
	draw_direction_ray(cub3d);
	if (cub3d->q_pressed == TRUE)
		connect_player_to_mouse(cub3d);
	// draw_rays(cub3d);
}
