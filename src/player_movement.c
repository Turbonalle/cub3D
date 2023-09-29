#include "../incl/cub3d.h"

void player_movement(cub3d_t *cub3d)
{
	if (cub3d->keys.w)
		cub3d->player.pos.y += MOVEMENT_SPEED;
	if (cub3d->keys.s)
		cub3d->player.pos.y -= MOVEMENT_SPEED;
	if (cub3d->keys.a)
		cub3d->player.pos.x -= MOVEMENT_SPEED;
	if (cub3d->keys.d)
		cub3d->player.pos.x += MOVEMENT_SPEED;
	printf("pos = [%.2f][%.2f]\n", cub3d->player.pos.x, cub3d->player.pos.y);
}