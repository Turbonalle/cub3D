#include "../incl/cub3d.h"

int	get_color_mix(int color1, int color2)
{
	int	r;
	int	g;
	int	b;
	int	a;

	r = ((color1 >> 16 & 0xFF) + (color2 >> 16 & 0xFF)) * 0.5;
	g = ((color1 >> 8 & 0xFF) + (color2 >> 8 & 0xFF)) * 0.5;
	b = ((color1 & 0xFF) + (color2 & 0xFF)) * 0.5;
	a = ((color1 >> 24 & 0xFF) + (color2 >> 24 & 0xFF)) * 0.5;
	return (set_rgba(r, g, b, a));
}