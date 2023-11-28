
#include "../incl/cub3d.h"

void	move_minimap(cub3d_t *cub3d)
{
	vector_t	mouse_moved;

	mouse_moved.x = cub3d->mouse.x - cub3d->mouse_set_pos.x;
	mouse_moved.y = cub3d->mouse.y - cub3d->mouse_set_pos.y;
	if (cub3d->orig_minimap_pos.x + mouse_moved.x < 0)
		cub3d->minimap.img->instances[0].x = 0;
	else if (cub3d->orig_minimap_pos.x + mouse_moved.x + cub3d->minimap.width > (int)cub3d->img->width)
		cub3d->minimap.img->instances[0].x = cub3d->img->width - cub3d->minimap.width;
	else
		cub3d->minimap.img->instances[0].x = cub3d->orig_minimap_pos.x + mouse_moved.x;
	if (cub3d->orig_minimap_pos.y + mouse_moved.y < 0)
		cub3d->minimap.img->instances[0].y = 0;
	else if (cub3d->orig_minimap_pos.y + mouse_moved.y + cub3d->minimap.height > (int)cub3d->img->height)
		cub3d->minimap.img->instances[0].y = cub3d->img->height - cub3d->minimap.height;
	else
		cub3d->minimap.img->instances[0].y = cub3d->orig_minimap_pos.y + mouse_moved.y;
	cub3d->minimap.pos.x = cub3d->minimap.img->instances[0].x;
	cub3d->minimap.pos.y = cub3d->minimap.img->instances[0].y;
}

void	update_minimap(cub3d_t *cub3d)
{
	(void)cub3d;
	// compare img size with previous img size
	// calculate previous minimap position in relation to the previous img size
	// update minimap position in relation to the new img size
	// calculate previous minimap position in relation to the previous img size
	// update minimap position in relation to the new img size
}

void update_minimap_fov(cub3d_t *cub3d)
{
	if (cub3d->settings.fisheye == 1)
	{
		if (cub3d->keys.up)
			decrease_fov(cub3d);
		if (cub3d->keys.down)
			increase_fov(cub3d);
	}
}

void update_minimap_player_pos(cub3d_t *cub3d)
{
	cub3d->minimap.player_pos.x = cub3d->player.pos.x * cub3d->minimap.tile_size;
	cub3d->minimap.player_pos.y = cub3d->player.pos.y * cub3d->minimap.tile_size;
}

void update_minimap_enemy_pos(cub3d_t *cub3d)
{
	int	i;

	i = 0;
	while (i < cub3d->num_enemies)
	{
		cub3d->enemy[i].minimap_pos.x = cub3d->enemy[i].pos.x * cub3d->minimap.tile_size;
		cub3d->enemy[i].minimap_pos.y = cub3d->enemy[i].pos.y * cub3d->minimap.tile_size;
		i++;
	}
}

void minimap(cub3d_t *cub3d)
{
	update_minimap_fov(cub3d);
	update_minimap_player_pos(cub3d);
	draw_minimap(cub3d);
	draw_minimap_border(cub3d);
	draw_fov(cub3d);
	draw_minimap_player(cub3d);
	update_minimap_enemy_pos(cub3d);
	draw_minimap_playerdir(cub3d);
}
