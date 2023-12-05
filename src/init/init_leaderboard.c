#include "../incl/cub3d.h"

int	init_leaderboard(cub3d_t *cub3d, leaderboard_t *board)
{
	int	i;

	board->background_color = BLACK;
	board->rect_title.width = cub3d->mlx->width * 0.4;
	board->rect_title.height = cub3d->mlx->height * 0.15;
	board->rect_title.pos.x = (cub3d->mlx->width - board->rect_title.width) / 2;
	board->rect_title.pos.y = cub3d->mlx->height * 0.05;
	board->rect_title.color = GREEN;
	board->rect_level = malloc(sizeof(rectangle_t) * cub3d->n_levels);
	if (!board->rect_level)
		return (err("Failed to allocate memory for leaderboard rectangles"));
	board->text_level = malloc(sizeof(mlx_image_t *) * cub3d->n_levels);
	if (!board->text_level)
		return (err("Failed to allocate memory for leaderboard text"));
	board->text_record_list = malloc(sizeof(mlx_image_t *) * cub3d->n_levels);
	if (!board->text_record_list)
		return (err("Failed to allocate memory for leaderboard text"));
	int columns = 2;
	int title_space = board->rect_title.pos.y + board->rect_title.height + cub3d->mlx->height * 0.02;
	int width_margin = cub3d->mlx->width * 0.02;
	int height_margin = cub3d->mlx->height * 0.02;
	int gap = cub3d->mlx->width * 0.005;
	int width = (cub3d->mlx->width - 2 * width_margin - (cub3d->n_levels - 1) * gap) / (cub3d->n_levels / columns);
	int height = (cub3d->mlx->height - title_space - width_margin * 2) / columns;

	printf("mlx_width: %d\n", cub3d->mlx->width);
	printf("mlx_height: %d\n", cub3d->mlx->height);
	printf("title_space: %d\n", title_space);
	printf("width: %d\n", width);
	printf("height: %d\n", height);
	i = -1;
	while (++i < cub3d->n_levels)
	{
		board->rect_level[i].width = width;
		board->rect_level[i].height = height;
		board->rect_level[i].pos.x = width_margin + i * (width + gap);
		board->rect_level[i].pos.y = title_space + height_margin + (i % (cub3d->n_levels / columns)) * (height + gap);
		board->rect_level[i].color = GREEN;
	}
	board->button_back.width = cub3d->mlx->height * 0.15;
	board->button_back.height = cub3d->mlx->height * 0.15;
	board->button_back.pos.x = cub3d->mlx->width * 0.1;
	board->button_back.pos.y = cub3d->mlx->height * 0.05;
	board->button_back.background_color = BUTTON_COLOR;
	board->button_back.border_color = BUTTON_BORDER_COLOR;
	board->button_back.border_width = BUTTON_BORDER_THICKNESS;
	return (SUCCESS);
}