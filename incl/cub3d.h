#ifndef CUB3D_H
# define CUB3D_H
# include "colors.h"
# include "terminal_colors.h"
# include "MLX42/MLX42.h"
# include "../lib/libft/get_next_line.h"
# include "../lib/libft/libft.h"
# include <stdio.h>
# include <math.h>

# define FAIL 0
# define SUCCESS 1
# define FALSE 0
# define TRUE 1

# define WIDTH 1280
# define HEIGHT 720

# define MAP_ALL_ELEMENTS "NSWE 01-| nesw"
# define MAP_DIRECTIONS "NSWE"
# define MAP_ELEMENTS "01"
# define ENEMIES "nesw"

# define NORTH 'N'
# define SOUTH 'S'
# define WEST 'W'
# define EAST 'E'

# define EMPTY '0'
# define WALL '1'

# define DE '|'
# define DN '-'

# define MOVEMENT_SPEED 0.1
# define ROTATION_SPEED 0.02

# define MINIMAP_SIZE_PERCENTAGE 20
# define MINIMAP_MAX_SIZE_PERCENTAGE 100
# define MINIMAP_MIN_SIZE_PERCENTAGE 10
# define MINIMAP_COLOR_PLAYER YELLOW
# define MINIMAP_COLOR_PLAYERDIR WHITE
# define MINIMAP_COLOR_FOV SADDLEBROWN
# define MINIMAP_COLOR_EMPTY GRAY
# define MINIMAP_COLOR_FLOOR BLACK
# define MINIMAP_COLOR_WALL GRAY
# define MINIMAP_COLOR_DOOR CYAN
# define MINIMAP_TRANSPARENCY 20

# define MINIMAP_ZOOM_INCREMENT 5

# define FOV 60
# define FOV_INCREMENT 5
# define FOV_MIN 1
# define FOV_MAX 360

# define X 0
# define Y 1

enum elements
{
	NO,
	SO,
	WE,
	EA,
	F,
	C
};

// prototypes
typedef struct map_node_s map_node_t;
typedef struct enemy_path_s enemy_path_t;

typedef struct texture_s
{
	char	*path;
	int		*img;
	int		width;
	int		height;
}			texture_t;

typedef struct vector_s
{
	int	x;
	int	y;
}		vector_t;

typedef struct dvector_t
{
	double	x;
	double	y;
}			dvector_t;

typedef struct player_s
{
	dvector_t	pos;
	dvector_t	new_pos;
	dvector_t	dir;
	double		angle;
	double		movement_angle;
	int			is_walking;
	int			is_strafing;
}				player_t;

typedef struct s_enemy
{
	dvector_t		pos;
	dvector_t		new_pos;
	dvector_t		dir;
	double			angle;
	double			dir_player;
	int				is_walking;
	int				is_spinning;
	enemy_path_t	*path;
}	t_enemy;

typedef struct map_node_s
{
	char		*line;
	map_node_t	*next;
}			map_node_t;

typedef struct enemy_path_s
{
	dvector_t		path;
	enemy_path_t	*next;
	enemy_path_t	*prev;
}		enemy_path_t;

typedef struct keypress_s
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	fisheye;
	int	left;
	int	right;
	int	up;
	int	down;
	int	mouse_left;
	int	mouse_right;
}			keypress_t;

typedef struct minimap_s
{
	mlx_image_t	*img;
	vector_t	pos;
	dvector_t	player_pos;
	int			width;
	int			height;
	int			size_percentage;
	int			tile_size;
	int			color;			// DON'T THINK WE NEED THIS...
	int			color_player;
	int			color_playerdir;
	int			color_fov;
	int			color_floor;
	int			color_door;
	int			color_wall;
	int			color_empty;
	int			transparency;
}			minimap_t;

typedef struct ray_s
{
	dvector_t	end;
	double		angle;
	double		length;
	char		target;
	int			wall;
}				ray_t;

typedef struct cub3d_s
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	vector_t	mouse;
	vector_t	mouse_set_pos;
	int			on_minimap;
	vector_t	orig_minimap_pos;
	keypress_t	keys;
	player_t	player;
	double		fov;
	vector_t	starting_pos;
	char		starting_dir;
	minimap_t	minimap;
	map_node_t	*map_list;
	int			nodes;
	char		**map;
	int			map_rows;
	int			map_columns;
	texture_t	texture[4];
	int			floor_color;
	int			ceiling_color;
	int			element_found[6];
	ray_t		*rays;
	int			fisheye;
	int			prev;
	int			num_enemies;
	t_enemy		*enemy;
}			cub3d_t;



//---- COLOR -------------------------------------------------------------------

// get_color.c
int		get_r(int rgba);
int		get_g(int rgba);
int		get_b(int rgba);
int		get_a(int rgba);

// set_color.c
int		set_rgba(int r, int g, int b, int a);
int		set_r(int rgba, int r);
int		set_g(int rgba, int g);
int		set_b(int rgba, int b);
int		set_a(int rgba, int a);

// transparency.c
int		set_transparency(int color, int transparency);



//---- PARSING -----------------------------------------------------------------

// get_color.c
int		get_color(cub3d_t *cub3d, int element, char **info);

// get_elements.c
int		all_elements_found(int *element_found);
void	remove_newline(char *line);
int		get_elements(cub3d_t *cub3d, int fd);

// get_map.c
int		read_cub_file(cub3d_t *cub3d, char *map_path);

// get_texture.c
int		get_texture(cub3d_t *cub3d, int element, char **info);

// flooding_algorithm.c
int		check_map_validity(char **map);

//---- DRAWING -----------------------------------------------------------------

// draw_line.c
void	draw_line(mlx_image_t *img, dvector_t start, dvector_t end, int color);
void	draw_vertical_line(mlx_image_t *img, dvector_t start_d, dvector_t end_d, int color);
void	draw_world(cub3d_t *cub3d);

//---- MATH --------------------------------------------------------------------

// math.c
double	within_360(double degree);
double	within_two_pi(double radians);
double	to_radians(double degrees);

// dda.c
int		find_end_point(cub3d_t *cub3d, player_t *player, double radians, dvector_t *end);


//---- MAIN PROGRAM ------------------------------------------------------------

// init_cub3d.c
int		count_minimap_tilesize(cub3d_t *cub3d, int size_percentage);
int		init_rays(cub3d_t *cub3d);
int		init_cub3d(cub3d_t *cub3d);

// start_game.c
void	start_game(cub3d_t *cub3d);



//---- PLAYER ------------------------------------------------------------------

// collision.c
void	collision_checker(cub3d_t *cub3d);

// player_movement.c
void	player_movement(cub3d_t *cub3d);

// fov.c
void	increase_fov(cub3d_t *cub3d);
void	decrease_fov(cub3d_t *cub3d);



//---- INPUT -------------------------------------------------------------------

// handle_close.c
void	handle_close_window(void *param);
void	handle_escape_key(mlx_key_data_t *keydata, mlx_t *mlx);

// handle_keys.c
void	get_input(mlx_key_data_t keydata, void *param);

// handle_mouse.c
void	hook_mouse_buttons(enum mouse_key key, enum action action, enum modifier_key modifier, void *param);
void	hook_mouse_scroll(double xdelta, double ydelta, void *param);



//---- MINIMAP -----------------------------------------------------------------

// minimap.c
void	update_minimap_player_pos(cub3d_t *cub3d);
void	minimap(cub3d_t *cub3d);

// minimap_draw_base.c
void	draw_square(cub3d_t *cub3d, int x, int y, int size, int color);
void	draw_minimap(cub3d_t *cub3d);
void	draw_minimap_border(cub3d_t *cub3d);

// minimap_draw_player.c
void	draw_minimap_player(cub3d_t *cub3d);
void	draw_minimap_playerdir(cub3d_t *cub3d);
void	draw_fov(cub3d_t *cub3d);

// minimap_zoom.c
int		hover_minimap(cub3d_t *cub3d);
void	zoom_in_minimap(cub3d_t *cub3d);
void	zoom_out_minimap(cub3d_t *cub3d);



//---- RAYCASTING --------------------------------------------------------------

// raycasting.c
void	raycasting(cub3d_t *cub3d);



//---- UTILS -------------------------------------------------------------------

// memory_utils.c
void	free_info(char **info);
void	free_cub3d(cub3d_t *cub3d);
void	free_list(map_node_t *node);

// error_utils.c
int		err(char *error_message);

//---- EXTRA (REMOVE THESE BEFORE EVALUATION) ----------------------------------

// extra.c
void	print_info(cub3d_t *cub3d);
void	print_array(char **array, char *name);
void	print_map(char **map);
void	test(void);


int		init_enemy(cub3d_t *cub3d);
void	check_if_player_is_seen(cub3d_t *cub3d);
#endif
