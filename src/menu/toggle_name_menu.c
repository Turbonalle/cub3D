#include "../incl/cub3d.h"

void	disable_name_menu(mlx_t *mlx, name_menu_t *menu)
{
	int	letter;
	int	index;

	mlx_delete_image(mlx, menu->text_time);
	menu->img->instances[0].enabled = FALSE;
	menu->text_win_message->instances[0].enabled = FALSE;
	while (menu->current > 0)
	{
		menu->current--;
		letter = menu->name[menu->current] - 'a';
		index = menu->letter_index[menu->current];
		menu->letters_img[letter]->instances[index].enabled = FALSE;
		menu->name[menu->current] = '\0';
	}
}

void	reset_name_menu(name_menu_t *menu)
{
	int i;

	menu->current = 0;
	i = -1;
	while (++i < MAX_NAME_LENGTH)
		menu->box[i].letter[0] = '\0';
}

void	enable_name_menu(cub3d_t *cub3d, name_menu_t *menu)
{
	create_time_string(menu->time_str, cub3d->time_finished);
	menu->text_time = mlx_put_string(cub3d->mlx, menu->time_str,
		menu->timer.pos.x + menu->timer.img->width * 0.5,
		menu->timer.pos.y + menu->timer.img->height + 10);
	center_horizontally(menu->text_time);
	reset_name_menu(menu);
	menu->img->instances[0].enabled = TRUE;
	menu->text_win_message->instances[0].enabled = TRUE;
}
