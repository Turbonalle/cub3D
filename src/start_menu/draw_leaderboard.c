#include "../incl/cub3d.h"
#include <unistd.h>

void	draw_times(mlx_t *mlx, record_t **records, leaderboard_t *board, mlx_image_t **times_list, int level)
{
	record_t 	*ptr;
	vector_t	pos;
	char		time_str[9];
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
		if (ptr->time <= 0 || ptr->time >= 6000000)
		{
			time_str[0] = '0';
			time_str[1] = '0';
			time_str[2] = ':';
			time_str[3] = '0';
			time_str[4] = '0';
			time_str[5] = '.';
			time_str[6] = '0';
			time_str[7] = '0';
		}
		else
		{
			time_str[0] = '0' + ptr->time / 600000;
			time_str[1] = '0' + ptr->time / 60000 % 10;
			time_str[2] = ':';
			time_str[3] = '0' + ptr->time / 10000 % 6;
			time_str[4] = '0' + ptr->time / 1000 % 10;
			time_str[5] = '.';
			time_str[6] = '0' + ptr->time / 100 % 10;
			time_str[7] = '0' + ptr->time / 10 % 10;
		}
		time_str[8] = '\0';
		times_list[i] = mlx_put_string(mlx, time_str, pos.x, pos.y);
		ptr = ptr->next;
	}
}

void	draw_names(mlx_t *mlx, record_t **records, leaderboard_t *board, mlx_image_t **times_list, int level)
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
		times_list[i] = mlx_put_string(mlx, ptr->name, pos.x, pos.y);
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

	board->text_level = malloc(sizeof(mlx_image_t *) * cub3d->n_levels);
	if (!board->text_level)
		err("Failed to allocate memory for leaderboard text");
	board->text_record_list = malloc(sizeof(mlx_image_t **) * cub3d->n_levels);
	if (!board->text_record_list)
		err("Failed to allocate memory for leaderboard text");
	i = -1;
	while (++i < cub3d->n_levels)
	{
		board->text_record_list[i] = malloc(sizeof(mlx_image_t *) * board->n_entries);
		if (!board->text_record_list[i])
			err("Failed to allocate memory for leaderboard text");
	}
	
	i = 0;
	while (++i <= 8)
	{
		draw_times(cub3d->mlx, &cub3d->levels[i].records, board, board->text_record_list[i], i);
		draw_names(cub3d->mlx, &cub3d->levels[i].records, board, board->text_record_list[i], i);
	}
	return (SUCCESS);
}