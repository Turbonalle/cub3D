#include "../incl/cub3d.h"

static int	player_is_invulnerable(cub3d_t *cub3d)
{
	return (mlx_get_time() - cub3d->player.hit_timestamp < INVULNERABILITY_TIME);
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
	printf("Player health: %i\n", cub3d->player.health);
}