#include "../incl/cub3d.h"

void collision_checker(cub3d_t *cub3d)
{
	if (cub3d->map[(int)cub3d->player.new_pos.y][(int)cub3d->player.new_pos.x] == WALL)
	{
		// cub3d->player.new_pos = cub3d->player.pos;
		// get the distance between the player and the wall
		// update new_pos

	}
	else
	{
		cub3d->player.pos = cub3d->player.new_pos;
	}
}