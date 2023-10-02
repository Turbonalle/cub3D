#include "../incl/cub3d.h"

int count_minimap_tilesize(cub3d_t *cub3d)
{
	float tile_size;
	float minimap_width;
	float minimap_height;

	minimap_width = (float)WIDTH * (float)cub3d->minimap.size_percentage / 100;
	tile_size = minimap_width / (float)cub3d->map_columns;
	minimap_height = (float)HEIGHT * (float)cub3d->minimap.size_percentage / 100;
	if (tile_size * (float)cub3d->map_rows > minimap_height)
		tile_size = minimap_height / (float)cub3d->map_rows;
	return ((int)tile_size);
}

void init_minimap(cub3d_t *cub3d)
{
	cub3d->minimap.size_percentage = MINIMAP_SIZE_PERCENTAGE;
	cub3d->minimap.tile_size = count_minimap_tilesize(cub3d);
	cub3d->minimap.width = cub3d->minimap.tile_size * cub3d->map_columns;
	cub3d->minimap.height = cub3d->minimap.tile_size * cub3d->map_rows;
	cub3d->minimap.pos.x = 0;
	cub3d->minimap.pos.y = 0;
}

void set_initial_direction(cub3d_t *cub3d)
{
	if (cub3d->starting_dir == 'N')
		cub3d->player.angle = to_radians(0);
	else if (cub3d->starting_dir == 'E')
		cub3d->player.angle = to_radians(90);
	else if (cub3d->starting_dir == 'S')
		cub3d->player.angle = to_radians(180);
	else if (cub3d->starting_dir == 'W')
		cub3d->player.angle = to_radians(270);
	cub3d->player.dir.x = cos(cub3d->player.angle);
	cub3d->player.dir.y = sin(cub3d->player.angle);
}

void set_keys(keypress_t *keys)
{
	keys->w = FALSE;
	keys->a = FALSE;
	keys->s = FALSE;
	keys->d = FALSE;
	keys->left = FALSE;
	keys->right = FALSE;
}

int init_cub3d(cub3d_t *cub3d)
{
	cub3d->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", TRUE);
	if (!cub3d->mlx)
		return (!err("Failed to initialize mlx"));
	cub3d->img = mlx_new_image(cub3d->mlx, WIDTH, HEIGHT);
	if (!cub3d->img || (mlx_image_to_window(cub3d->mlx, cub3d->img, 0, 0) < 0))
		return (!err("Failed to create image"));
	cub3d->player.pos.x = cub3d->starting_pos.x + 0.5;
	cub3d->player.pos.y = cub3d->starting_pos.y + 0.5;
	set_initial_direction(cub3d);
	set_keys(&cub3d->keys);
	init_minimap(cub3d);
	return (SUCCESS);
}