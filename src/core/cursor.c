#include "../incl/cub3d.h"

void	handle_cursor(cub3d_t *cub3d)
{
	if (cub3d->settings.mouse == TRUE && cub3d->state == STATE_GAME)
		mlx_set_cursor_mode(cub3d->mlx, MLX_MOUSE_DISABLED);
	else
		mlx_set_cursor_mode(cub3d->mlx, MLX_MOUSE_NORMAL);
}