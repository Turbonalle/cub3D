#include "../incl/cub3d.h"

void	disable_start_menu(start_menu_t *menu)
{
	menu->img->instances[0].enabled = FALSE;
	menu->title.img->instances[0].enabled = FALSE;
	printf("disabled start menu\n");
	menu->exit.img->instances[0].enabled = FALSE;
	menu->start.img->instances[0].enabled = FALSE;
	menu->level.img->instances[0].enabled = FALSE;
	menu->exit_hover.img->instances[0].enabled = FALSE;
	menu->start_hover.img->instances[0].enabled = FALSE;
	menu->level_hover.img->instances[0].enabled = FALSE;
	menu->arrow_exit.img->instances[0].enabled = FALSE;
	menu->arrow_start.img->instances[0].enabled = FALSE;
	menu->arrow_level.img->instances[0].enabled = FALSE;
}

void	enable_start_menu(start_menu_t *menu)
{
	printf("[Enable start menu]\n");
	menu->img->instances[0].enabled = TRUE;
	menu->title.img->instances[0].enabled = TRUE;
	printf("enabled start menu\n");
	printf("pixels 0: %d\n", menu->title.img->pixels[0]);
	printf("pixels 1: %d\n", menu->title.img->pixels[1]);
	printf("pixels 2: %d\n", menu->title.img->pixels[2]);
	printf("pixels 3: %d\n", menu->title.img->pixels[3]);
	menu->exit.img->instances[0].enabled = TRUE;
	menu->start.img->instances[0].enabled = TRUE;
	menu->level.img->instances[0].enabled = TRUE;
	menu->exit_hover.img->instances[0].enabled = FALSE;
	menu->start_hover.img->instances[0].enabled = FALSE;
	menu->level_hover.img->instances[0].enabled = FALSE;
	menu->arrow_exit.img->instances[0].enabled = FALSE;
	menu->arrow_start.img->instances[0].enabled = FALSE;
	menu->arrow_level.img->instances[0].enabled = FALSE;
	printf("[Enable start menu] : DONE!\n");
}
