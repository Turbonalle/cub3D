#include "../incl/cub3d.h"

void	update_level_menu(cub3d_t *cub3d, level_menu_t *menu)
{
	int	i;

	if (hover_image(cub3d, menu->back.img))
	{
		menu->back_hover.img->instances[0].enabled = TRUE;
		menu->back.img->instances[0].enabled = FALSE;
	}
	else
	{
		menu->back_hover.img->instances[0].enabled = FALSE;
		menu->back.img->instances[0].enabled = TRUE;
	}
	if (hover_image(cub3d, menu->leaderboard.img))
	{
		menu->leaderboard_hover.img->instances[0].enabled = TRUE;
		menu->leaderboard.img->instances[0].enabled = FALSE;
	}
	else
	{
		menu->leaderboard_hover.img->instances[0].enabled = FALSE;
		menu->leaderboard.img->instances[0].enabled = TRUE;
	}
	i = -1;
	while (++i < LEVELS)
	{
		if (hover_image(cub3d, menu->minilevels[i].img))
		{
			menu->minilevels[i].border->instances[0].enabled = TRUE;
		}
		else
		{
			menu->minilevels[i].border->instances[0].enabled = FALSE;
		}
	}
}
