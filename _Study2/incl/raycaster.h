#ifndef RAYCASTER_H

#define RAYCASTER_H

# include "MLX42/MLX42.h"
# include "colors_terminal.h"
# include "colors.h"
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>

# define WIDTH 600
# define HEIGHT 600
# define BPP sizeof(int)
# define BORDER_THICKNESS 1
// # define GRID_COLOR WHITE
// # define BG_COLOR BLACK

typedef struct vector_s
{
	int32_t	x;
	int32_t	y;
}		vector_t;

typedef struct map_s
{
	int columns;
	int rows;
	int cell_size;
	int **grid;
}		map_t;

// color.c
int get_rgba(int r, int g, int b, int a);
int get_r(int rgba);
int get_g(int rgba);
int get_b(int rgba);
int get_a(int rgba);

// draw.c
void draw_background(mlx_image_t *img, int color);
void draw_grid_fixed_box_size(mlx_image_t *img, int color, int size);
void draw_grid_relative_size(mlx_image_t *img, int color, int columns, int rows);

// hooks.c
void my_keyhook(mlx_key_data_t keydata, void *param);
void my_scrollhook(double xdelta, double ydelta, void *param);
void my_hook(void *param);
void my_mousehook(mouse_key_t mouse_key, action_t action, modifier_key_t modifier_key, void *param);

// map.c
void init_map(map_t *map, int columns, int rows, int cell_size);
void print_map(map_t *map);
void free_map(map_t *map);

// raycaster.c
void ft_error(void);
void reset_map(map_t *map);

#endif