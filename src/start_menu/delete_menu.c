#include "../incl/cub3d.h"

void	delete_start_menu(cub3d_t *cub3d, start_menu_t *menu)
{
	mlx_delete_image(cub3d->mlx, menu->img);
	mlx_delete_image(cub3d->mlx, menu->text_title);
	mlx_delete_image(cub3d->mlx, menu->text_start);
	mlx_delete_image(cub3d->mlx, menu->text_level);
	mlx_delete_image(cub3d->mlx, menu->text_settings);
	mlx_delete_image(cub3d->mlx, menu->text_exit);
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
	mlx_delete_image(cub3d->mlx, board->img);
	mlx_delete_image(cub3d->mlx, board->text_title);
	mlx_delete_image(cub3d->mlx, board->text_back);
	// free(board->rect_level);
	// free(board->text_level);
	// free(board->text_record_list);
}