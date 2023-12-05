#include "../incl/cub3d.h"

void	try_add_to_string(int *error, char **base, char *add)
{
	char *tmp;

	if (*error)
		return ;
	tmp = ft_strdup(*base);
	if (!tmp)
	{
		*error = TRUE;
		return ;
	}
	free(*base);
	*base = ft_strjoin(tmp, add);
	if (!*base)
	{
		free(tmp);
		*error = TRUE;
		return ;
	}
	free(tmp);
}

void	fill_empty_fields(int *error, char **str, int i)
{
	while (i < 10 && !*error)
	{
		try_add_to_string(error, str, "........ ........\n");
		i++;
	}
}

int	compile_level_records(level_t *level, char **str)
{
	record_t	*node_ptr;
	int			error;
	int			i;

	*str = ft_strdup("");
	if (!*str)
		err("Failed to allocate memory for leaderboard text");
	error = FALSE;
	i = 0;
	if (!level->records)
	{
		fill_empty_fields(&error, str, i);
		if (error)
		{
			free(*str);
			*str = NULL;
			err("Failed to allocate memory for leaderboard text");
		}
		return (SUCCESS);
	}
	node_ptr = level->records;
	while (node_ptr && !error)
	{
		try_add_to_string(&error, str, node_ptr->name);
		try_add_to_string(&error, str, " ");
		try_add_to_string(&error, str, ft_itoa(node_ptr->time));
		try_add_to_string(&error, str, "\n");
		node_ptr = node_ptr->next;
		i++;
	}
	fill_empty_fields(&error, str, i);
	if (error)
	{
		free(*str);
		*str = NULL;
		err("Failed to allocate memory for leaderboard text");
	}
	return (SUCCESS);
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
	while (++i < cub3d->n_levels)
		draw_rectangle(board->img, &board->rect_level[i]);

	mlx_image_to_window(cub3d->mlx, board->img, 0, 0);
	board->text_title = mlx_put_string(cub3d->mlx, "Leaderboard\nTest", board->rect_title.pos.x + board->rect_title.width * 0.5, board->rect_title.pos.y + board->rect_title.height * 0.5);
	center(board->text_title);

	board->text_level = malloc(sizeof(mlx_image_t *) * cub3d->n_levels);
	if (!board->text_level)
		err("Failed to allocate memory for leaderboard text");
	
	char *str;
	i = -1;
	while (++i < cub3d->n_levels)
	{
		if (!compile_level_records(&cub3d->levels[i], &str))
			return (err("Failed to compile level records"));
		board->text_level[i] = mlx_put_string(cub3d->mlx, str, board->rect_level[i].pos.x + board->rect_level[i].width * 0.01, board->rect_level[i].pos.y + board->rect_level[i].height * 0.01);
		free(str);
		str = NULL;
	}
	return (SUCCESS);
}