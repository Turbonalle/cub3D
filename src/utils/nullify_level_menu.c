#include "../incl/cub3d.h"

static void	nullify_minilevels(minilevel_t *minilevels)
{
	int	i;

	i = -1;
	while (++i < LEVELS)
	{
		minilevels[i].img = NULL;
		nullify_png(&minilevels[i].number);
		minilevels[i].border = NULL;
	}
}

void	nullify_level_menu(level_menu_t *menu)
{

	menu->img = NULL;
	nullify_png(&menu->title);
	nullify_png(&menu->back);
	nullify_png(&menu->back_hover);
	nullify_png(&menu->leaderboard);
	nullify_png(&menu->leaderboard_hover);
	nullify_minilevels(menu->minilevels);
}
