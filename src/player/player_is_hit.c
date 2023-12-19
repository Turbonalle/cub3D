#include "../incl/cub3d.h"

static int	player_is_invulnerable(cub3d_t *cub3d)
{
	return (mlx_get_time() - cub3d->player.hit_timestamp < INVULNERABILITY_TIME);
}

void	draw_health(cub3d_t *cub3d)
{
	char	*health;

	health = ft_itoa(cub3d->player.health);
	if (cub3d->level->health)
		mlx_delete_image(cub3d->mlx, cub3d->level->health);
	cub3d->level->health = mlx_put_string(cub3d->mlx, health, cub3d->mlx->width / 2, cub3d->mlx->height * 0.01);
}

void	player_is_hit(cub3d_t *cub3d)
{
	if (player_is_invulnerable(cub3d))
	{
		// printf("Player is invulnerable [%f]\n", mlx_get_time() - cub3d->player.hit_timestamp);
		return ;
	}
	cub3d->player.hit_timestamp = mlx_get_time();
	cub3d->player.health -= 1;
	activate_halo(&cub3d->halo, RED);
	if (cub3d->player.health > 0)
		draw_health(cub3d);
	printf("Player health: %i\n", cub3d->player.health);
}
