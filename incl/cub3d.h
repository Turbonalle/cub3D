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

//---- TEXTURE -----------------------------------------------------------------

typedef struct texture_s
{
	char	*path;
	int		*img;
	int		width;
	int		height;
}			texture_t;

//---- VECTORS -----------------------------------------------------------------

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

//---- PLAYER ------------------------------------------------------------------

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
	dvector_t		target;
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

//---- MINIMAP -----------------------------------------------------------------

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

//---- RAY ---------------------------------------------------------------------

typedef struct ray_s
{
	dvector_t	end;
	double		angle;
	double		length;
	char		target;
	int			wall;
}				ray_t;

//---- RECTANGLE ---------------------------------------------------------------

typedef struct rectangle_s
{
	vector_t	pos;
	int			width;
	int			height;
	int			color;
}				rectangle_t;

//---- SLIDER ------------------------------------------------------------------

typedef struct slider_s
{
	mlx_image_t	*img;
	vector_t	pos;
	int			width;
	int			height;
	int			color;
	int			background_color;
	int			value;
	int			max_value;
}				slider_t;

//---- BOX ---------------------------------------------------------------------

# define BOX_ON_COLOR GREEN
# define BOX_OFF_COLOR BLACK
# define BOX_HOVER_ON_COLOR LAWN_GREEN
# define BOX_HOVER_OFF_COLOR GRAY
# define BOX_BORDER_COLOR GOLD

# define OFF 0
# define ON 1

typedef struct box_s
{
	mlx_image_t	*text;
	vector_t	pos;
	int			size;
	int			background_color;
	int			border_width;
	int			border_color;
	int			value;
	int			state;
}				box_t;

//---- PAUSE MENU --------------------------------------------------------------

# define PAUSE_MENU_BACKGROUND_COLOR BLACK
# define PAUSE_MENU_TRANSPARENCY 1
# define PAUSE_MENU_SETTINGS_RECT_COLOR 0x2F1E45FF

typedef struct pause_menu_s
{
	mlx_image_t	*img;
	int			background_color;
	mlx_image_t	*text_title;
	mlx_image_t	*text_fps;
	mlx_image_t	*text_fisheye;
	mlx_image_t	*text_mouse;
	rectangle_t	rect_title;
	int			pos_x_rect_title;
	int			pos_y_rect_title;
	int			pos_col_text;
	int			pos_col_box_1;
	int			pos_col_box_2;
	int			pos_col_box_3;
	int			pos_col_box_4;
	int			pos_col_box_5;
	int			pos_text_row_1;
	int			pos_text_row_2;
	int			pos_text_row_3;
	int			pos_row_1;
	int			pos_row_2;
	int			pos_row_3;
	box_t		box_fps[4];
	box_t		box_fisheye[2];
	box_t		box_mouse[2];
}				pause_menu_t;

//---- SETTINGS MENU -----------------------------------------------------------

typedef struct settings_menu_s
{
	mlx_image_t	*img;
	mlx_image_t	*text_settings;
	mlx_image_t	*text_e_difficulty;
	mlx_image_t	*text_minimap_view;
	int			background_color;
}				settings_menu_t;


//---- SETTINGS ----------------------------------------------------------------

enum fps
{
	FPS_15,
	FPS_30,
	FPS_60,
	FPS_120
};

typedef struct settings_s
{
	int		e_difficulty;
	int		minimap_view;
	int 	fps;
	int		fisheye;
	int		mouse;
}			settings_t;


//---- CUB3D -------------------------------------------------------------------

enum state
{
	STATE_START,
	STATE_SETTINGS,
	STATE_GAME,
	STATE_PAUSE
};

typedef struct cub3d_s
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	vector_t		mouse;
	vector_t		mouse_set_pos;
	int				on_minimap;
	vector_t		orig_minimap_pos;
	keypress_t		keys;
	player_t		player;
	double			fov;
	vector_t		starting_pos;
	char			starting_dir;
	minimap_t		minimap;
	map_node_t		*map_list;
	int				nodes;
	char			**map;
	int				map_rows;
	int				map_columns;
	texture_t		texture[4];
	int				floor_color;
	int				ceiling_color;
	int				element_found[6];
	ray_t			*rays;
	int				state;
	pause_menu_t	pause_menu;
	int				prev;
	int				fisheye;
	int				num_enemies;
	settings_t		settings;
	t_enemy			*enemy;
}					cub3d_t;



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

void draw_world(cub3d_t *cub3d);
void draw_vertical_line(mlx_image_t *img, dvector_t start_d, dvector_t end_d, int color);
void	draw_line(mlx_image_t *img, dvector_t start_d, dvector_t end_d, int color);

//---- INIT --------------------------------------------------------------------

// init_cub3d.c
int		count_minimap_tilesize(cub3d_t *cub3d, int size_percentage);
int		init_rays(cub3d_t *cub3d);
int		init_cub3d(cub3d_t *cub3d);

// init_pause_menu.c
void	init_pause_menu(cub3d_t *cub3d, pause_menu_t *menu);


//---- PAUSE MENU --------------------------------------------------------------

void	delete_pause_menu(cub3d_t *cub3d);

// pause_text.c
void	add_title_text(cub3d_t *cub3d, pause_menu_t *menu);
void	add_category_text(cub3d_t *cub3d, pause_menu_t *menu);
void	add_checkbox_text(cub3d_t *cub3d, pause_menu_t *menu);

// pause_menu.c
void	update_pause_settings(cub3d_t *cub3d, pause_menu_t *menu);
void	update_pause_menu(cub3d_t *cub3d, pause_menu_t *menu);
void	draw_pause_menu(cub3d_t *cub3d, pause_menu_t *menu);


// center.c
void	center(mlx_image_t *img);
void	center_vertically(mlx_image_t *img);
void	center_horizontally(mlx_image_t *img);

// hover.c
int		hover_rectangle(cub3d_t *cub3d, rectangle_t *rect);
int		hover_box(cub3d_t *cub3d, box_t *box);
int		hover_any_box(cub3d_t *cub3d, pause_menu_t *menu);

//---- DRAW --------------------------------------------------------------------

void	draw_rectangle(cub3d_t *cub3d, rectangle_t *rect);
void	draw_checkbox(cub3d_t *cub3d, box_t *box);
void	draw_hovered_checkbox(cub3d_t *cub3d, box_t *box);


//---- MATH --------------------------------------------------------------------

// math.c
double	within_360(double degree);
double	within_two_pi(double radians);
double	to_radians(double degrees);

// dda.c
int		find_end_point(cub3d_t *cub3d, player_t *player, double radians, dvector_t *end);


//---- CORE --------------------------------------------------------------------

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
void	move_minimap(cub3d_t *cub3d);
void	update_minimap(cub3d_t *cub3d);
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
