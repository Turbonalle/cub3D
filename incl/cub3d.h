#ifndef CUB3D_H
# define CUB3D_H
# include "incl/colors.h"
# include "lib/libft/get_next_line.h"
# include "lib/libft/libft.h"
# include <stdio.h>

# define FAIL 0
# define SUCCESS 1

enum elements
{
	NO,
	SO,
	WE,
	EA,
	F,
	C
};

typedef struct texture_s
{
	char	*path;
	int		*img;
	int		width;
	int		height;
}			texture_t;

typedef struct cub3d_s
{
	char		**map;
	texture_t	texture[4];
	int			floor_color;
	int			ceiling_color;
	int			element_found[6];
}			cub3d_t;

#endif
