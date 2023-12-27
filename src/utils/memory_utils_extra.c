#include "../../incl/cub3d.h"

static void	delete_textures_additional(cub3d_t *cub3d)
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
	mlx_delete_texture(cub3d->distraction_texture);
}

static void	delete_textures(cub3d_t *cub3d)
{
	int	i;

	delete_textures_additional(cub3d);
	i = 0;
	while (i < LEVELS)
	{
		mlx_delete_texture(cub3d->level_menu.minilevels[i++].number.texture);
	}
	i = 0;
	while (i < HEARTS)
	{
		mlx_delete_texture(cub3d->hearts[i].full.texture);
		mlx_delete_texture(cub3d->hearts[i++].empty.texture);
	}
	i = 0;
	while (i < NUM_FRAMES_ENEMY_IDLE)
	{
		mlx_delete_texture(cub3d->frames_idle[i++]);
	}
	i = 0;
	while (i < NUM_FRAMES_ENEMY_WALKING)
	{
		mlx_delete_texture(cub3d->frames_walking[i++]);
	}
}

void	free_cub3d(cub3d_t *cub3d)
{
	int	i;

	i = 0;
	while (i < LEVELS + 1)
	{
		free_list(cub3d->levels[i].map_list);
		i++;
	}
	free(cub3d->rays);
	i = 0;
	while (i < LEVELS + 1)
	{
		free_backup(cub3d->levels[i]);
		i++;
	}
	//ft_putstr_fd("Freed all levels\n", 1);
	
	delete_textures(cub3d);
	//ft_putstr_fd("Deleted textures\n", 1);
	//TODO: figure out why commented lines segfault occasionally
	//delete_hearts(cub3d);
	//ft_putstr_fd("Deleted hearts\n", 1);
	//mlx_delete_image(cub3d->mlx, cub3d->halo.img);
	//ft_putstr_fd("Deleted halo\n", 1);
	free(cub3d->levels);
	//ft_putstr_fd("Freed levels\n", 1);
}
