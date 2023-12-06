#include "../incl/cub3d.h"

int	init_leaderboard(cub3d_t *cub3d, leaderboard_t *board)
{
	int	i;

	// allocate memory
	board->rect_level = malloc(sizeof(rectangle_t) * cub3d->n_levels);
	if (!board->rect_level)
		return (err("Failed to allocate memory for leaderboard rectangles"));
	board->text_level = malloc(sizeof(mlx_image_t *) * cub3d->n_levels);
	if (!board->text_level)
		return (err("Failed to allocate memory for leaderboard text"));
	board->text_record_list = malloc(sizeof(mlx_image_t *) * cub3d->n_levels);
	if (!board->text_record_list)
		return (err("Failed to allocate memory for leaderboard text"));

	// set other variables
	board->background_color = BLACK;
	board->n_entries = 3;

	// set title
	board->rect_title.width = cub3d->mlx->width * 0.4;
	board->rect_title.height = cub3d->mlx->height * 0.15;
	board->rect_title.pos.x = (cub3d->mlx->width - board->rect_title.width) / 2;
	board->rect_title.pos.y = cub3d->mlx->height * 0.05;
	board->rect_title.color = GREEN;

	int rows = 2;
	int columns = ((cub3d->n_levels - 1) % 2 == 0) ? (cub3d->n_levels - 1) / rows : ((cub3d->n_levels - 1) + 1) / rows;
	int title_space = board->rect_title.pos.y + board->rect_title.height + cub3d->mlx->height * 0.02;
	int width_margin = cub3d->mlx->width * 0.02;
	int height_margin = cub3d->mlx->height * 0.05;
	int width_gap = cub3d->mlx->width * 0.01;
	int height_gap = width_gap;
	int width = (cub3d->mlx->width - 2 * width_margin - (columns - 1) * width_gap) / ((cub3d->n_levels - 1) / rows);
	int height = (cub3d->mlx->height - title_space - height_margin * 2) / rows;

	// set rectangles
	i = -1;
	while (++i < cub3d->n_levels - 1)
	{
		board->rect_level[i].width = width;
		board->rect_level[i].height = height;
		board->rect_level[i].pos.x = width_margin + (i % columns) * (width + width_gap);
		if (i < cub3d->n_levels / rows)
			board->rect_level[i].pos.y = title_space + height_margin;
		else
			board->rect_level[i].pos.y = title_space + height_margin + height + height_gap;
		board->rect_level[i].color = GREEN;
	}

	// set back button
	board->button_back.width = cub3d->mlx->height * 0.15;
	board->button_back.height = cub3d->mlx->height * 0.15;
	board->button_back.pos.x = cub3d->mlx->width * 0.1;
	board->button_back.pos.y = cub3d->mlx->height * 0.05;
	board->button_back.background_color = BUTTON_COLOR;
	board->button_back.border_color = BUTTON_BORDER_COLOR;
	board->button_back.border_width = BUTTON_BORDER_THICKNESS;
	return (SUCCESS);
}