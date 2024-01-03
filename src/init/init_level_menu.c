#include "../incl/cub3d.h"

void	set_preview_values(minilevel_t *minilevel, level_t *level)
{
	int	drawable_area_size;

	drawable_area_size = minilevel->size - MINILEVEL_MARGIN * 2;
	if (drawable_area_size < 0)
		drawable_area_size = 0;
	if (level->map_columns > level->map_rows)
	{
		minilevel->preview_square_size = drawable_area_size / level->map_columns;
		minilevel->preview_width = minilevel->preview_square_size * level->map_columns;
		minilevel->preview_height = minilevel->preview_square_size * level->map_rows;
		minilevel->preview_pos.x = (minilevel->size - minilevel->preview_width) / 2;
		minilevel->preview_pos.y = (minilevel->size - minilevel->preview_height) / 2;
	}
	else
	{
		minilevel->preview_square_size = drawable_area_size / level->map_rows;
		minilevel->preview_width = minilevel->preview_square_size * level->map_columns;
		minilevel->preview_height = minilevel->preview_square_size * level->map_rows;
		minilevel->preview_pos.x = (minilevel->size - minilevel->preview_width) / 2;
		minilevel->preview_pos.y = (minilevel->size - minilevel->preview_height) / 2;
	}
}

void	set_number_values(minilevel_t *minilevel)
{
	int	number_rect_size;

	number_rect_size = minilevel->size * 0.15;
	minilevel->number_rect.width = number_rect_size;
	minilevel->number_rect.height = number_rect_size;
	minilevel->number_rect.pos.x = 0;
	minilevel->number_rect.pos.y = 0;
	minilevel->number_rect.color = MINILEVEL_RECT_COLOR;
	minilevel->number.pos.x = minilevel->pos.x + number_rect_size / 2 - minilevel->number.img->width / 2;
	minilevel->number.pos.y = minilevel->pos.y + number_rect_size / 2 - minilevel->number.img->height / 2;
}

void	draw_preview_map(minilevel_t *minilevel, level_t *level)
{
	int			row;
	int			column;
	vector_t	coord;

	row = -1;
	while (++row < level->map_rows)
	{
		column = -1;
		while (++column < level->map_columns)
		{
			coord.x = minilevel->preview_pos.x + column * minilevel->preview_square_size;
			coord.y = minilevel->preview_pos.y + row * minilevel->preview_square_size;
			if (level->backup[row][column] == '1')
			{
				draw_square(minilevel->img,
					coord,
					minilevel->preview_square_size,
					PREVIEW_WALL_COLOR);
			}
			else
			{
				draw_square(minilevel->img,
					coord,
					minilevel->preview_square_size,
					PREVIEW_FLOOR_COLOR);
			}
		}
	}
}

static void	draw_minimap_preview(minilevel_t *minilevel, level_t *level)
{
	draw_menu_background(minilevel->img, MINILEVEL_BG_COLOR);
	set_preview_values(minilevel, level);
	set_number_values(minilevel);
	draw_preview_map(minilevel, level);
	draw_rectangle(minilevel->img, &minilevel->number_rect);
}

static void	draw_border_image(minilevel_t *minilevel)
{
	unsigned int	row;
	unsigned int	col;

	row = -1;
	while (++row < minilevel->border->height)
	{
		col = -1;
		while (++col < minilevel->border->width)
		{
			if (row < MINILEVEL_BORDER_THICKNESS
				|| row >= minilevel->border->height - MINILEVEL_BORDER_THICKNESS
				|| col < MINILEVEL_BORDER_THICKNESS
				|| col >= minilevel->border->width - MINILEVEL_BORDER_THICKNESS)
				mlx_put_pixel(minilevel->border, col, row, MINILEVEL_BORDER_COLOR);
		}
	}
}

static void load_png(level_menu_t *menu)
{
	const char	*number_png[LEVELS] = NUMBER_PNGS;		// Allowed or not?
	int			i;

	menu->title.texture = mlx_load_png(LEVEL_TITLE_PNG);
	menu->back.texture = mlx_load_png(BACK_PNG);
	menu->back_hover.texture = mlx_load_png(BACK_HOVER_PNG);
	menu->leaderboard.texture = mlx_load_png(LEADERBOARD_PNG);
	menu->leaderboard_hover.texture = mlx_load_png(LEADERBOARD_HOVER_PNG);
	i = -1;
	while (++i < LEVELS)
		menu->minilevels[i].number.texture = mlx_load_png(number_png[i]);
}

static int	init_images(mlx_t *mlx, level_menu_t *menu)
{
	int	size;
	int	i;

	menu->img = mlx_new_image(mlx, mlx->width, mlx->height);
	if (!menu->img)
		return (err("Failed to create level menu image"));
	menu->title.img = mlx_texture_to_image(mlx, menu->title.texture);
	if (!menu->title.img)
		return (err("Failed to create level menu title image"));
	menu->back.img = mlx_texture_to_image(mlx, menu->back.texture);
	if (!menu->back.img)
		return (err("Failed to create level menu back image"));
	menu->back_hover.img = mlx_texture_to_image(mlx, menu->back_hover.texture);
	if (!menu->back_hover.img)
		return (err("Failed to create level menu back hover image"));
	menu->leaderboard.img = mlx_texture_to_image(mlx, menu->leaderboard.texture);
	if (!menu->leaderboard.img)
		return (err("Failed to create level menu leaderboard image"));
	menu->leaderboard_hover.img = mlx_texture_to_image(mlx, menu->leaderboard_hover.texture);
	if (!menu->leaderboard_hover.img)
		return (err("Failed to create level menu leaderboard hover image"));
	i = -1;
	while (++i < LEVELS)
	{
		size = min(mlx->width * 0.15, mlx->height * 0.25);
		menu->minilevels[i].img = mlx_new_image(mlx, size, size);
		if (!menu->minilevels[i].img)
			return (err("Failed to create level menu minilevel image"));
		menu->minilevels[i].border = mlx_new_image(mlx, size + MINILEVEL_BORDER_THICKNESS * 2, size + MINILEVEL_BORDER_THICKNESS * 2);
		if (!menu->minilevels[i].border)
			return (err("Failed to create level menu minilevel border image"));
		menu->minilevels[i].number.img = mlx_texture_to_image(mlx, menu->minilevels[i].number.texture);
		if (!menu->minilevels[i].number.img)
			return (err("Failed to create level menu minilevel number image"));
	}
	return (SUCCESS);
}

static void	set_positions(level_menu_t *menu, vector_t *back_button_pos)
{
	int	i;
	int	size;
	int	gap;
	int	rows;
	int	columns;
	int	number_square_size;

	menu->title.pos.x = (menu->img->width - menu->title.img->width) / 2;
	menu->title.pos.y = menu->img->height * 0.12;
	size = menu->minilevels[0].img->width;
	rows = 2;
	if (LEVELS % rows == 0)
		columns = LEVELS / rows;
	else
		columns = LEVELS / rows + 1;
	gap = min(menu->img->width * 0.05, menu->img->height * 0.05);
	if (gap < MINILEVEL_BORDER_THICKNESS)
		gap = MINILEVEL_BORDER_THICKNESS;
	back_button_pos->x = (menu->img->width - (columns * size + (columns - 1) * gap)) / 2;
	back_button_pos->y = menu->img->height * 0.12;
	number_square_size = size * 0.15;
	menu->back.pos.x = back_button_pos->x;
	menu->back.pos.y = back_button_pos->y;
	menu->leaderboard.pos.x = menu->img->width - back_button_pos->x - menu->leaderboard.img->width;
	menu->leaderboard.pos.y = menu->img->height * 0.12;
	i = -1;
	while (++i < LEVELS)
	{
		menu->minilevels[i].size = size;
		menu->minilevels[i].pos.x = back_button_pos->x + (i % columns) * (size + gap);
		menu->minilevels[i].pos.y = menu->img->height * 0.32 + (i / columns) * (size + gap);
		menu->minilevels[i].number.pos.x = menu->minilevels[i].pos.x + number_square_size / 2 - menu->minilevels[i].number.img->width / 2;
		menu->minilevels[i].number.pos.y = menu->minilevels[i].pos.y + number_square_size / 2 - menu->minilevels[i].number.img->height / 2;
	}
}

static int	put_images_to_window(mlx_t *mlx, level_menu_t *menu)
{
	int	i;

	if (mlx_image_to_window(mlx, menu->img, 0, 0) < 0)
		return (err("Failed to put level menu image to window"));
	if (mlx_image_to_window(mlx, menu->title.img, menu->title.pos.x, menu->title.pos.y) < 0)
		return (err("Failed to put level menu title image to window"));
	if (mlx_image_to_window(mlx, menu->back.img, menu->back.pos.x, menu->back.pos.y) < 0)
		return (err("Failed to put level menu back image to window"));
	if (mlx_image_to_window(mlx, menu->back_hover.img, menu->back.pos.x, menu->back.pos.y) < 0)
		return (err("Failed to put level menu back hover image to window"));
	if (mlx_image_to_window(mlx, menu->leaderboard.img, menu->leaderboard.pos.x, menu->leaderboard.pos.y) < 0)
		return (err("Failed to put level menu leaderboard image to window"));
	if (mlx_image_to_window(mlx, menu->leaderboard_hover.img, menu->leaderboard.pos.x, menu->leaderboard.pos.y) < 0)
		return (err("Failed to put level menu leaderboard hover image to window"));
	i = -1;
	while (++i < LEVELS)
	{
		if (mlx_image_to_window(mlx, menu->minilevels[i].img, menu->minilevels[i].pos.x, menu->minilevels[i].pos.y) < 0)
			return (err("Failed to put level menu minilevel image to window"));
		if (mlx_image_to_window(mlx, menu->minilevels[i].number.img, menu->minilevels[i].number.pos.x, menu->minilevels[i].number.pos.y) < 0)
			return (err("Failed to put level menu minilevel number image to window"));
		if (mlx_image_to_window(mlx, menu->minilevels[i].border, menu->minilevels[i].pos.x - MINILEVEL_BORDER_THICKNESS, menu->minilevels[i].pos.y - MINILEVEL_BORDER_THICKNESS) < 0)
			return (err("Failed to put level menu minilevel border image to window"));
	}
	return (SUCCESS);
}

int	init_level_menu(cub3d_t *cub3d, level_menu_t *menu)
{
	int	i;

	load_png(menu);
	if (!init_images(cub3d->mlx, menu))
		return (FAIL);
	set_positions(menu, &cub3d->back_button_pos);
	draw_menu_background(menu->img, MENU_BACKGROUND_COLOR);
	draw_menu_border(menu->img);
	i = -1;
	while (++i < LEVELS)
	{
		draw_minimap_preview(&menu->minilevels[i], &cub3d->levels[i + 1]);
		draw_border_image(&menu->minilevels[i]);
	}
	if (!put_images_to_window(cub3d->mlx, menu))
		return (FAIL);
	disable_level_menu(menu);
	return (SUCCESS);
}
