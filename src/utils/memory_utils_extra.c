#include "../../incl/cub3d.h"

static void	delete_textures(cub3d_t *cub3d, int i)
{
	free(cub3d->leaderboard.rect_level);
	free(cub3d->leaderboard.text_level);
	mlx_delete_texture(cub3d->start_menu.title.texture);
	mlx_delete_texture(cub3d->start_menu.exit.texture);
	mlx_delete_texture(cub3d->start_menu.start.texture);
	mlx_delete_texture(cub3d->start_menu.level.texture);
	mlx_delete_texture(cub3d->start_menu.exit_hover.texture);
	mlx_delete_texture(cub3d->start_menu.start_hover.texture);
	mlx_delete_texture(cub3d->start_menu.level_hover.texture);
	mlx_delete_texture(cub3d->start_menu.arrow_exit.texture);
	mlx_delete_texture(cub3d->start_menu.arrow_start.texture);
	mlx_delete_texture(cub3d->start_menu.arrow_level.texture);
	mlx_delete_texture(cub3d->level_menu.title.texture);
	mlx_delete_texture(cub3d->level_menu.back.texture);
	mlx_delete_texture(cub3d->level_menu.leaderboard.texture);
	mlx_delete_texture(cub3d->level_menu.back_hover.texture);
	mlx_delete_texture(cub3d->level_menu.leaderboard_hover.texture);
	while (i < 8)
	{
		mlx_delete_texture(cub3d->level_menu.minilevels[i].number.texture);
		i++;
	}
}

void	free_cub3d(cub3d_t *cub3d)
{
	int	i;

	i = 0;
	while (i <= 9)
	{
		free_list(cub3d->levels[i].map_list);
		i++;
	}
	free(cub3d->rays);
	i = 0;
	while (i <= 9)
	{
		free_backup(cub3d->levels[i]);
		i++;
	}
	i = 0;
	while (i < NUM_FRAMES_ENEMY_IDLE)
	{
		mlx_delete_texture(cub3d->frames_idle[i]);
		mlx_delete_texture(cub3d->frames_walking[i]);
		i++;
	}
	delete_textures(cub3d, 0);
	free(cub3d->levels);
}
