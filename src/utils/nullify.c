#include "../incl/cub3d.h"

void	nullify_cub3d(cub3d_t *cub3d)
{
	int	i;

	cub3d->mlx = NULL;
	cub3d->img = NULL;
	cub3d->rays = NULL;
	cub3d->levels = NULL;
	cub3d->level = NULL;
	cub3d->enemy = NULL;
	cub3d->distraction_texture = NULL;
	cub3d->distraction_thrown_texture = NULL;
	cub3d->shroom = NULL;
	nullify_texture(&cub3d->floor);
	i = -1;
	while (++i < NUM_FRAMES_STARS)
		nullify_texture(&cub3d->stars[i]);
	i = -1;
	while (++i < NUM_DOOR_TEXTURES)
		nullify_texture(&cub3d->door[i]);
}

void	nullify_minimap(minimap_t *minimap)
{
	minimap->img = NULL;
}

void	nullify_gametimer(gametimer_t *timer)
{
	timer->img_time = NULL;
	timer->text_time = NULL;
}

void	nullify_hearts(heart_t *hearts)
{
	int	i;

	i = -1;
	while (++i < HEARTS)
	{
		nullify_png(&hearts[i].full);
		nullify_png(&hearts[i].empty);
	}
}

void	nullify_everything(cub3d_t *cub3d)
{
	nullify_cub3d(cub3d);
	nullify_minimap(&cub3d->minimap);
	nullify_start_menu(&cub3d->start_menu);
	nullify_gameover_menu(&cub3d->gameover_menu);
	nullify_name_menu(&cub3d->name_menu);
	nullify_level_menu(&cub3d->level_menu);
	nullify_leaderboard(&cub3d->leaderboard);
	nullify_pause_menu(&cub3d->pause_menu);
	nullify_gametimer(&cub3d->timer);
	nullify_hearts(cub3d->hearts);
}