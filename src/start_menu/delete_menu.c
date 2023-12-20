#include "../incl/cub3d.h"

void	delete_start_menu(cub3d_t *cub3d, start_menu_t *menu)
{
	mlx_delete_image(cub3d->mlx, menu->img);
	mlx_delete_image(cub3d->mlx, menu->title.img);
	mlx_delete_image(cub3d->mlx, menu->start.img);
	mlx_delete_image(cub3d->mlx, menu->level.img);
	mlx_delete_image(cub3d->mlx, menu->exit.img);
}

void	delete_level_menu(cub3d_t *cub3d, level_menu_t *menu)
{
	mlx_delete_image(cub3d->mlx, menu->img);
	mlx_delete_image(cub3d->mlx, menu->text_title);
	mlx_delete_image(cub3d->mlx, menu->text_level_1);
	mlx_delete_image(cub3d->mlx, menu->text_level_2);
	mlx_delete_image(cub3d->mlx, menu->text_level_3);
	mlx_delete_image(cub3d->mlx, menu->text_level_4);
	mlx_delete_image(cub3d->mlx, menu->text_level_5);
	mlx_delete_image(cub3d->mlx, menu->text_level_6);
	mlx_delete_image(cub3d->mlx, menu->text_level_7);
	mlx_delete_image(cub3d->mlx, menu->text_level_8);
	mlx_delete_image(cub3d->mlx, menu->text_back);
	mlx_delete_image(cub3d->mlx, menu->text_leaderboard);
}

void	delete_leaderboard(cub3d_t *cub3d, leaderboard_t *board)
{
	record_t	*ptr;
	int			i;
	int			entry;

	i = 0;
	mlx_delete_image(cub3d->mlx, board->img);
	mlx_delete_image(cub3d->mlx, board->text_title);
	mlx_delete_image(cub3d->mlx, board->text_back);
	while (++i < cub3d->n_levels)
	{
		ptr = cub3d->levels[i].records;
		entry = -1;
		while (++entry < board->n_entries && ptr)
		{
			mlx_delete_image(cub3d->mlx, ptr->text_time);
			mlx_delete_image(cub3d->mlx, ptr->text_name);
			ptr = ptr->next;
		}
	}
}

void	delete_name_menu(cub3d_t *cub3d, name_menu_t *menu)
{
	int	i;

	mlx_delete_image(cub3d->mlx, menu->img);
	mlx_delete_image(cub3d->mlx, menu->text_win_message);
	i = -1;
	while (++i < ALPHABET_LENGTH)
		mlx_delete_image(cub3d->mlx, menu->letters_img[i]);
}

void	delete_menus(cub3d_t *cub3d)
{
	delete_start_menu(cub3d, &cub3d->start_menu);
	delete_level_menu(cub3d, &cub3d->level_menu);
	delete_leaderboard(cub3d, &cub3d->leaderboard);
	delete_name_menu(cub3d, &cub3d->name_menu);
}