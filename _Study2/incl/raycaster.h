#ifndef RAYCASTER_H

#define RAYCASTER_H

# include "MLX42/MLX42.h"
# include "colors_terminal.h"
# include "colors.h"
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <math.h>

# define WIDTH 600
# define HEIGHT 600
# define BPP sizeof(int)
# define BORDER_THICKNESS 1
# define FAIL 0
# define SUCCESS 1
# define FALSE 0
# define TRUE 1
# define GRID_COLOR DARK_GRAY
# define BG_COLOR BLACK
# define WALL_COLOR GRAY

# define EMPTY 0
# define WALL 1
# define PLAYER 2

# define MOVEMENT_SPEED 0.5
# define ROTATION_SPEED 0.02

# define WEST 1
# define SOUTH 2
# define EAST 3
# define NORTH 4

typedef struct vector_s
{
	int32_t	x;
	int32_t	y;
}		vector_t;

typedef struct double_vector_s
{
	double	x;
	double	y;
}			double_vector_t;

typedef struct box_s
{
	int x;
	int y;
	int end_x;
	int end_y;
	int value;
}		box_t;

typedef struct map_s
{
	int columns;
	int rows;
	int cell_size;
	int **grid;
	box_t **grid_relative;
}		map_t;

typedef struct player_s
{
	double_vector_t pos;
	double_vector_t dir;
	double		angle;
	int			color;
	int			left;
	int			right;
	int			down;
	int			up;
	int			rotate_left;
	int			rotate_right;
}				player_t;

typedef struct cub3d_s
{
	mlx_t *mlx;
	mlx_image_t *img;
	map_t *map;
	player_t player;
	int lmb_pressed;
	int	rmb_pressed;
	int q_pressed;
	int rays;
}		cub3d_t;

// color.c
int get_rgba(int r, int g, int b, int a);
int get_r(int rgba);
int get_g(int rgba);
int get_b(int rgba);
int get_a(int rgba);

// draw_base.c
void draw_background(mlx_image_t *img, int color);
void draw_grid_fixed_size(mlx_image_t *img, int color, int size);
void draw_grid_relative_size(mlx_image_t *img, int color, int columns, int rows);

// draw_player.c
void draw_player(cub3d_t *cub3d);

// draw_rays.c
void draw_rays(cub3d_t *cub3d);
void draw_direction_ray(cub3d_t *cub3d);
void connect_player_to_mouse(cub3d_t *cub3d);
int find_end_point(map_t *map, player_t *player, double radians, double_vector_t *end);

// walls.c
void fill_box(mlx_image_t *img, map_t *map, int row, int column, int color);
void create_wall(mlx_image_t *img, map_t *map, int row, int column, int color);
void draw_wall_border(mlx_image_t *img, map_t *map, int color);

// hooks.c
void hook_keytest(mlx_key_data_t keydata, void *param);
void hook_mouse_scroll(double xdelta, double ydelta, void *param);
void hook_close(void *param);
void hook_mouse_buttons(enum mouse_key key, enum action action, enum modifier_key modifier, void *param);
void hook_other_functions(void *param);
void empty_chosen_box(mlx_t *mlx, mlx_image_t *img, map_t *map, int color);
void fill_chosen_box(mlx_t *mlx, mlx_image_t *img, map_t *map, int color);
void hook_player_movement(void *param);

// map.c
map_t* init_map(mlx_image_t *img, int columns, int rows);
void print_map(map_t *map);
void free_map(map_t *map);
void draw_map(mlx_image_t *img, map_t *map);

// math.c
double distance(double_vector_t a, double_vector_t b);
void switch_values(int *a, int *b);

// raycaster.c
void ft_error(void);
void reset_map(mlx_image_t *img, map_t *map);

#endif