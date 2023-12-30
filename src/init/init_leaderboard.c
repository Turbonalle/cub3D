#include "../incl/cub3d.h"

void	draw_times(mlx_t *mlx, record_t **records, leaderboard_t *board, int level)
{
	record_t 	*ptr;
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
	record_t 	*ptr;
	vector_t	pos;
	int			i;
	int			margin_x;
	int 		margin_y;

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

int	init_leaderboard(cub3d_t *cub3d, leaderboard_t *board)
{
	int	i;

	// allocate memory
	board->rect_level = malloc(sizeof(rectangle_t) * cub3d->n_levels);
	if (!board->rect_level)
		return (err("Failed to allocate memory for leaderboard rectangles"));
	board->text_level = malloc(sizeof(mlx_image_t *) * cub3d->n_levels);
	if (!board->text_level)
		err("Failed to allocate memory for leaderboard text");

	// set other variables
	board->background_color = BLACK;

	// set title
	board->rect_title.width = cub3d->mlx->width * 0.4;
	board->rect_title.height = cub3d->mlx->height * 0.15;
	board->rect_title.pos.x = (cub3d->mlx->width - board->rect_title.width) / 2;
	board->rect_title.pos.y = cub3d->mlx->height * 0.05;
	board->rect_title.color = GREEN;

	int rows = 2;
	int columns = (cub3d->n_levels % 2 == 0) ? cub3d->n_levels / rows : (cub3d->n_levels + 1) / rows;
	int title_space = board->rect_title.pos.y + board->rect_title.height + cub3d->mlx->height * 0.02;
	
	int size = cub3d->level_menu.minilevels[0].img->width;
	int gap = min(cub3d->mlx->width * 0.05, cub3d->mlx->height * 0.05);
	if (gap < MINILEVEL_BORDER_THICKNESS)
		gap = MINILEVEL_BORDER_THICKNESS;
	int width_margin = (cub3d->mlx->width - (columns * size + (columns - 1) * gap)) / 2;
	int height_margin = size * 0.32;

	// set rectangles
	i = -1;
	while (++i < cub3d->n_levels)
	{
		board->rect_level[i].width = size;
		board->rect_level[i].height = size;
		board->rect_level[i].pos.x = width_margin + (i % columns) * (size + gap);
		if (i < cub3d->n_levels / rows)
			board->rect_level[i].pos.y = title_space + height_margin;
		else
			board->rect_level[i].pos.y = title_space + height_margin + size + gap;
		board->rect_level[i].color = LEADERBOARD_LEVEL_BACKGROUND_COLOR;
	}

	// set back button
	board->button_back.width = cub3d->mlx->height * 0.15;
	board->button_back.height = cub3d->mlx->height * 0.15;
	board->button_back.pos.x = cub3d->mlx->width * 0.1;
	board->button_back.pos.y = cub3d->mlx->height * 0.05;
	board->button_back.background_color = BUTTON_COLOR;
	board->button_back.border_color = BUTTON_BORDER_COLOR;
	board->button_back.border_width = BUTTON_BORDER_THICKNESS;

	board->img = mlx_new_image(cub3d->mlx, cub3d->mlx->width, cub3d->mlx->height);
	if (!board->img)
		err("Failed to create leaderboard image");
	draw_menu_background(board->img, MENU_BACKGROUND_COLOR);
	draw_rectangle(board->img, &board->rect_title);
	draw_button(board->img, &board->button_back);

	i = -1;
	while (++i < cub3d->n_levels)
		draw_rectangle(board->img, &board->rect_level[i]);

	mlx_image_to_window(cub3d->mlx, board->img, 0, 0);
	board->text_title = mlx_put_string(cub3d->mlx, "Leaderboard", board->rect_title.pos.x + board->rect_title.width * 0.5, board->rect_title.pos.y + board->rect_title.height * 0.5);
	center(board->text_title);
	
	set_record_texts(cub3d, board);
	disable_leaderboard(cub3d, board);
	return (SUCCESS);
}