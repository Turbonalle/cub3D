#include "../incl/cub3d.h"

void	reset_name_menu(name_menu_t *menu)
{
	int i;

	menu->current = 0;
	i = -1;
	while (++i < MAX_NAME_LENGTH)
		menu->box[i].letter[0] = '\0';
}

int	draw_name_menu(cub3d_t *cub3d, name_menu_t *menu)
{
	(void)cub3d;
	reset_name_menu(menu);
	menu->img->instances[0].enabled = TRUE;
	menu->text_win_message->instances[0].enabled = TRUE;
	return (SUCCESS);
}