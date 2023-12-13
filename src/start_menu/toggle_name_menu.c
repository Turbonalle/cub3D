#include "../incl/cub3d.h"

void	disable_name_menu(name_menu_t *menu)
{
	int	letter;
	int	index;

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

void	enable_name_menu(name_menu_t *menu)
{
	reset_name_menu(menu);
	menu->img->instances[0].enabled = TRUE;
	menu->text_win_message->instances[0].enabled = TRUE;
}