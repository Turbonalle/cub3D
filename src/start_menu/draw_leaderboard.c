#include "../incl/cub3d.h"
#include <unistd.h>

void	draw_times(mlx_t *mlx, record_t **records, leaderboard_t *board, int level)
{
	record_t 	*ptr;
	vector_t	pos;
	int	i;
	int margin_x;
	int margin_y;

	ptr = *records;

	margin_x = board->rect_level[level - 1].width * 0.1;
	margin_y = board->rect_level[level - 1].height * 0.2;
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
	int	i;
	int margin_y;

	ptr = *records;

	margin_y = board->rect_level[level - 1].height * 0.2;
	pos.x = board->rect_level[level - 1].pos.x + board->rect_level[level - 1].width * 0.5;
	i = -1;
	while (++i < board->n_entries && ptr)
	{
		pos.y = board->rect_level[level - 1].pos.y + margin_y + i * (board->rect_level[level - 1].height - 2 * margin_y) / board->n_entries;
		ptr->text_name = mlx_put_string(mlx, ptr->name, pos.x, pos.y);
		ptr = ptr->next;
	}
}

int	draw_leaderboard(cub3d_t *cub3d, leaderboard_t *board)
{
	int i;

	board->img = mlx_new_image(cub3d->mlx, cub3d->mlx->width, cub3d->mlx->height);
	if (!board->img)
		err("Failed to create leaderboard image");
	draw_menu_background(board->img, board->background_color);
	draw_rectangle(board->img, &board->rect_title);
	draw_button(board->img, &board->button_back);

	i = -1;
	while (++i < cub3d->n_levels - 1)
		draw_rectangle(board->img, &board->rect_level[i]);

	mlx_image_to_window(cub3d->mlx, board->img, 0, 0);
	board->text_title = mlx_put_string(cub3d->mlx, "Leaderboard", board->rect_title.pos.x + board->rect_title.width * 0.5, board->rect_title.pos.y + board->rect_title.height * 0.5);
	center(board->text_title);
	
	i = 0;
	while (++i <= 8)
	{
		draw_names(cub3d->mlx, &cub3d->levels[i].records, board, i);
		draw_times(cub3d->mlx, &cub3d->levels[i].records, board, i);
	}
	return (SUCCESS);
}