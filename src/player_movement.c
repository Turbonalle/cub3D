#include "../incl/cub3d.h"

int is_walking(cub3d_t *cub3d)
{
	return ((cub3d->keys.w && !cub3d->keys.s)
			|| (!cub3d->keys.w && cub3d->keys.s));
}

int is_strafing(cub3d_t *cub3d)
{
	return ((cub3d->keys.a && !cub3d->keys.d)
			|| (!cub3d->keys.a && cub3d->keys.d));
}

void player_rotation(cub3d_t *cub3d)
{
	// printf("player_rotation\n");
	if (cub3d->keys.left && !cub3d->keys.right)
	{
		cub3d->player.angle -= ROTATION_SPEED;
		if (cub3d->player.angle < 0)
			cub3d->player.angle += (M_PI + M_PI);
	}
	else if (cub3d->keys.right && !cub3d->keys.left)
	{
		cub3d->player.angle += ROTATION_SPEED;
		if (cub3d->player.angle >= (2 * M_PI))
			cub3d->player.angle -= (M_PI + M_PI);
	}
}

void player_walking(cub3d_t *cub3d)
{
	// printf("player_walking\n");
	if (cub3d->keys.w && !cub3d->keys.s)
	{
		cub3d->player.new_pos.x = cos(cub3d->player.angle);
		cub3d->player.new_pos.y = sin(cub3d->player.angle);
	}
	else if (cub3d->keys.w && cub3d->keys.s)
	{
		cub3d->player.new_pos.x = cos(cub3d->player.angle);
		cub3d->player.new_pos.y = sin(cub3d->player.angle);
	}
}

void player_strafing(cub3d_t *cub3d)
{
	double angle;

	// printf("player_strafing\n");
	if (cub3d->keys.a && !cub3d->keys.d)
	{
		angle = cub3d->player.angle - (M_PI / 2);
		if (angle < 0)
			angle += (M_PI + M_PI);
		cub3d->player.new_pos.x = cos(angle);
		cub3d->player.new_pos.y = sin(angle);
	}
	else if (!cub3d->keys.a && cub3d->keys.d)
	{
		angle = cub3d->player.angle + (M_PI / 2);
		if (angle >= (M_PI + M_PI))
			angle -= (M_PI + M_PI);
		cub3d->player.new_pos.x = cos(angle);
		cub3d->player.new_pos.y = sin(angle);
	}
}

void player_both(cub3d_t *cub3d)
{
	// printf("player_both\n");
	if (cub3d->keys.w && cub3d->keys.a)
	{
		cub3d->player.movement_angle = cub3d->player.angle - (M_PI / 4);
		if (cub3d->player.movement_angle < 0)
			cub3d->player.movement_angle += (M_PI + M_PI);
		cub3d->player.new_pos.x = cos(cub3d->player.movement_angle);
		cub3d->player.new_pos.y = sin(cub3d->player.movement_angle);
	}
	else if (cub3d->keys.w && cub3d->keys.d)
	{
		cub3d->player.movement_angle = cub3d->player.angle + (M_PI / 4);
		if (cub3d->player.movement_angle >= (M_PI + M_PI))
			cub3d->player.movement_angle -= (M_PI + M_PI);
		cub3d->player.new_pos.x = cos(cub3d->player.movement_angle);
		cub3d->player.new_pos.y = sin(cub3d->player.movement_angle);
	}
	if (cub3d->keys.s && cub3d->keys.a)
	{
		cub3d->player.movement_angle = cub3d->player.angle + (M_PI / 4);
		if (cub3d->player.movement_angle >= (M_PI + M_PI))
			cub3d->player.movement_angle -= (M_PI + M_PI);
		cub3d->player.new_pos.x = cos(cub3d->player.movement_angle);
		cub3d->player.new_pos.y = sin(cub3d->player.movement_angle);
	}
	else if (cub3d->keys.s && cub3d->keys.d)
	{
		cub3d->player.movement_angle = cub3d->player.angle - (M_PI / 4);
		if (cub3d->player.movement_angle < 0)
			cub3d->player.movement_angle += (M_PI + M_PI);
		cub3d->player.new_pos.x = cos(cub3d->player.movement_angle);
		cub3d->player.new_pos.y = sin(cub3d->player.movement_angle);
	}
}

void player_movement(cub3d_t *cub3d)
{
	printf("ori_pos = [%.2f][%.2f]\n", cub3d->player.pos.x, cub3d->player.pos.y);
	player_rotation(cub3d);
	cub3d->player.is_walking = is_walking(cub3d);
	cub3d->player.is_strafing = is_strafing(cub3d);
	if (!cub3d->player.is_walking && !cub3d->player.is_strafing)
		return ;
	if (cub3d->player.is_walking && !cub3d->player.is_strafing)
		player_walking(cub3d);
	else if (!cub3d->player.is_walking && cub3d->player.is_strafing)
		player_strafing(cub3d);
	else
		player_both(cub3d);
	// if (!collision(new_pos))
	cub3d->player.pos = cub3d->player.new_pos;
	printf("new_pos = [%.2f][%.2f]\n", cub3d->player.pos.x, cub3d->player.pos.y);
}
