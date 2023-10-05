#include "../incl/cub3d.h"

void draw_minimap_player(cub3d_t *cub3d)
{
	double row;
	double column;
	int size;

	size = cub3d->minimap.tile_size / 4;
	if (size < 1)
		size = 1;
	row = cub3d->minimap.pos.y + (cub3d->player.pos.y * cub3d->minimap.tile_size) - (size / 2);
	column = cub3d->minimap.pos.x + (cub3d->player.pos.x * cub3d->minimap.tile_size) - (size / 2);
	draw_square(cub3d, (int)column, (int)row, size, YELLOW);
}

void draw_minimap_playerdir(cub3d_t *cub3d)
{
	dvector_t end;

	cub3d->player.dir.x = cos(cub3d->player.angle);
	cub3d->player.dir.y = sin(cub3d->player.angle);
	end.x = cub3d->minimap.player_pos.x + (cub3d->player.dir.x * cub3d->minimap.tile_size / 2);
	end.y = cub3d->minimap.player_pos.y + (cub3d->player.dir.y * cub3d->minimap.tile_size / 2);
	draw_line(cub3d->img, cub3d->minimap.player_pos, end, WHITE);
}

void draw_fov(cub3d_t *cub3d)
{
	dvector_t end;
	double fov_start;
	double ray_angle;
	int rays;
	int i;

	fov_start = within_two_pi(cub3d->player.angle - to_radians((cub3d->fov / 2)));
	rays = cub3d->img->width;
	i = -1;
	while (++i < rays)
	{
		ray_angle = within_two_pi(fov_start + to_radians((cub3d->fov * i / rays)));
		find_end_point(cub3d, &cub3d->player, ray_angle, &end);
		draw_line(cub3d->img, cub3d->minimap.player_pos, end, SADDLEBROWN);
	}
}