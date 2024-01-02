#include "../incl/cub3d.h"

void	draw_times(mlx_t *mlx, record_t **records, leaderboard_t *board, int level)
{
	record_t	*ptr;
	vector_t	pos;
	int			i;
	int			margin_x;
	int			margin_y;

	ptr = *records;

	margin_x = board->rect_level[level - 1].width * 0.1;
	margin_y = board->rect_level[level - 1].height * 0.1;
	pos.x = board->rect_level[level - 1].pos.x + margin_x;
	i = -1;
	while (++i < board->n_entries && ptr)
	{
		pos.y = board->rect_level[level - 1].pos.y + margin_y + i * (board->rect_level[level - 1].height - 2 * margin_y) / board->n_entries;
		ptr->text_time = mlx_put_string(mlx, ptr->time_str, pos.x, pos.y);
		ptr = ptr->next;
	}
}

void	draw_names(mlx_t *mlx, record_t **records, leaderboard_t *board, int level)
{
	record_t	*ptr;
	vector_t	pos;
	int			i;
	int			margin_x;
	int			margin_y;

	ptr = *records;

	margin_x = board->rect_level[level - 1].width * 0.1;
	margin_y = board->rect_level[level - 1].height * 0.1;
	pos.x = board->rect_level[level - 1].pos.x + margin_x;
	i = -1;
	while (++i < board->n_entries && ptr)
	{
		pos.y = board->rect_level[level - 1].pos.y + margin_y + i * (board->rect_level[level - 1].height - 2 * margin_y) / board->n_entries + margin_y;
		ptr->text_name = mlx_put_string(mlx, ptr->name, pos.x, pos.y);
		ptr = ptr->next;
	}
}

void	set_record_texts(cub3d_t *cub3d, leaderboard_t *board)
{
	int	i;

	i = 0;
	while (++i <= cub3d->n_levels)
	{
		draw_names(cub3d->mlx, &cub3d->levels[i].records, board, i);
		draw_times(cub3d->mlx, &cub3d->levels[i].records, board, i);
	}
}

static void	load_png(leaderboard_t *board)
{
	board->title.texture = mlx_load_png(LEADERBOARD_TITLE_PNG);
	board->back.texture = mlx_load_png(BACK_PNG);
	board->back_hover.texture = mlx_load_png(BACK_HOVER_PNG);
}

static int	init_images(mlx_t *mlx, leaderboard_t *board)
{
	board->img = mlx_new_image(mlx, mlx->width, mlx->height);
	if (!board->img)
		return (err("Failed to create leaderboard image"));
	board->title.img = mlx_texture_to_image(mlx, board->title.texture);
	if (!board->title.img)
		return (err("Failed to create leaderboard title image"));
	board->back.img = mlx_texture_to_image(mlx, board->back.texture);
	if (!board->back.img)
		return (err("Failed to create leaderboard back image"));
	board->back_hover.img = mlx_texture_to_image(mlx, board->back_hover.texture);
	if (!board->back_hover.img)
		return (err("Failed to create leaderboard back hover image"));
	return (SUCCESS);
}

static void	set_positions(mlx_t *mlx, leaderboard_t *board)
{
	int i;
	int size;
	int gap;
	int rows;
	int columns;
	int margin_x;

	board->title.pos.x = (board->img->width - board->title.img->width) / 2;
	board->title.pos.y = board->img->height * 0.12;
	size = min(mlx->width * 0.15, mlx->height * 0.25);
	rows = 2;
	if (LEVELS % rows == 0)
		columns = LEVELS / rows;
	else
		columns = LEVELS / rows + 1;
	gap = min(board->img->width * 0.05, board->img->height * 0.05);
	if (gap < MINILEVEL_BORDER_THICKNESS)
		gap = MINILEVEL_BORDER_THICKNESS;
	margin_x = (board->img->width - (columns * size + (columns - 1) * gap)) / 2;
	board->back.pos.x = margin_x;
	board->back.pos.y = board->img->height * 0.12;
	board->back_hover.pos.x = margin_x;
	board->back_hover.pos.y = board->img->height * 0.12;

	i = -1;
	while (++i < LEVELS)
	{
		board->rect_level[i].color = LEADERBOARD_LEVEL_BACKGROUND_COLOR;
		board->rect_level[i].width = size;
		board->rect_level[i].height = size;
		board->rect_level[i].pos.x = margin_x + (i % columns) * (size + gap);
		board->rect_level[i].pos.y = board->img->height * 0.32 + (i / columns) * (size + gap);
	}
}

static int put_images_to_window(mlx_t *mlx, leaderboard_t *board)
{
	if (mlx_image_to_window(mlx, board->img, 0, 0) < 0)
		return (err("Failed to put leaderboard image to window"));
	if (mlx_image_to_window(mlx, board->title.img, board->title.pos.x, board->title.pos.y) < 0)
		return (err("Failed to put leaderboard title image to window"));
	if (mlx_image_to_window(mlx, board->back.img, board->back.pos.x, board->back.pos.y) < 0)
		return (err("Failed to put leaderboard back image to window"));
	if (mlx_image_to_window(mlx, board->back_hover.img, board->back_hover.pos.x, board->back_hover.pos.y) < 0)
		return (err("Failed to put leaderboard back hover image to window"));
	return (SUCCESS);
}

int	init_leaderboard(cub3d_t *cub3d, leaderboard_t *board)
{
	int	i;

	load_png(board);
	if (!init_images(cub3d->mlx, board))
		return (FAIL);
	set_positions(cub3d->mlx, board);
	draw_menu_background(board->img, MENU_BACKGROUND_COLOR);
	draw_menu_border(board->img);
	i = -1;
	while (++i < cub3d->n_levels)
		draw_rectangle(board->img, &board->rect_level[i]);
	if (!put_images_to_window(cub3d->mlx, board))
		return (FAIL);
	set_record_texts(cub3d, board);
	disable_leaderboard(cub3d, board);
	return (SUCCESS);
}
