#include "../incl/cub3d.h"

static int	player_is_invulnerable(cub3d_t *cub3d)
{
	return (mlx_get_time() - cub3d->player.hit_timestamp < INVULNERABILITY_TIME);
}

void	draw_health(cub3d_t *cub3d)
{
	cub3d->level->heart_img->instances[0].enabled = FALSE;
	cub3d->level->heart_half_img->instances[0].enabled = FALSE;
	cub3d->level->heart_empty_img->instances[0].enabled = FALSE;
	if (cub3d->player.health == 2)
		cub3d->level->heart_half_img->instances[0].enabled = TRUE;
	if (cub3d->player.health == 1)
		cub3d->level->heart_empty_img->instances[0].enabled = TRUE;
}

void	player_is_hit(cub3d_t *cub3d, int i)
{
	if (player_is_invulnerable(cub3d) || cub3d->player.is_dirty_cheater == 2)
	{
		printf("Player is invulnerable!\n");
		return ;
	}
	cub3d->enemy[i].freeze_start = cub3d->run_time;
	cub3d->player.hit_timestamp = mlx_get_time();
	cub3d->player.health -= 1;
	activate_halo(&cub3d->halo, RED);
	adjust_hearts(cub3d);
}
