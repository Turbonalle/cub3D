#include "../../incl/cub3d.h"

static void	delete_textures_additional(cub3d_t *cub3d)
{
	// free(cub3d->leaderboard.rect_level);
	// free(cub3d->leaderboard.text_level);
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
	mlx_delete_texture(cub3d->distraction_thrown_texture);
}

static void	delete_textures(cub3d_t *cub3d)
{
	int	i;

	delete_textures_additional(cub3d);
	printf("deleted additional textures\n");
	i = 0;
	while (i < LEVELS)
	{
		printf("deleting minilevel %d, texture pointer: %p\n", i, cub3d->level_menu.minilevels[i].number.texture);
		mlx_delete_texture(cub3d->level_menu.minilevels[i++].number.texture);
	}
	printf("deleted minilevels\n");
	i = 0;
	while (i < HEARTS)
	{
		mlx_delete_texture(cub3d->hearts[i].full.texture);
		mlx_delete_texture(cub3d->hearts[i++].empty.texture);
	}
	printf("deleted hearts\n");
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
	printf("deleted enemy frames\n");
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
		printf("Freeing backup for level %d\n", i);
		free_backup(cub3d->levels[i]);
		//TODO: refactor to take a level rather than a pointer
		
		//free_delete_textures(&cub3d->levels[i]);
		i++;
	}
	printf("Freed backups, i is now %d\n", i);
	//ft_putstr_fd("Freed all levels\n", 1);
	free_level_textures(cub3d);
	printf("Freed level textures\n");
	delete_textures(cub3d);
	printf("Deleted all textures in free_cub3d\n");
	printf("Deleted all textures in free_cub3d\n");
	//ft_putstr_fd("Deleted textures\n", 1);
	//TODO: figure out why commented lines segfault occasionally
	//delete_hearts(cub3d);
	//ft_putstr_fd("Deleted hearts\n", 1);
	//mlx_delete_image(cub3d->mlx, cub3d->halo.img);
	//ft_putstr_fd("Deleted halo\n", 1);
	free(cub3d->levels);
	printf("free_cub3d DONE\n");
	//ft_putstr_fd("Freed levels\n", 1);
}
