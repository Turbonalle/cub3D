#ifndef STRUCTS_H
# define STRUCTS_H

# include "MLX42/MLX42.h"

// prototypes
typedef struct map_node_s map_node_t;
typedef struct key_node_s key_node_t;
typedef struct door_pos_s door_pos_t;

//---- TEXTURE -----------------------------------------------------------------

typedef struct texture_s
{
	char	*path;
	mlx_texture_t	*texture;
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
# define DISTRACTION_THROW_DISTANCE 5

typedef struct player_s
{
	dvector_t	pos;
	dvector_t	new_pos;
	dvector_t	dir;
	bool		thrown;
	double		angle;
	double		movement_angle;
	double		hit_timestamp;
	int			health;
	int			mushroom_count;
	int			is_walking;
	int			is_strafing;
}				player_t;

enum enemy_state
{
	IDLE,
	WALKING,
	DYING
};

typedef struct s_enemy
{
	dvector_t		pos;
	dvector_t		target;
	dvector_t		dir;
	dvector_t		minimap_pos;
	vector_t		pos_screen;
	double			freeze_start;
	double			angle;
	double			angle_start;
	double			dir_player;
	int				is_walking;
	int				is_spinning;
	int				is_eating;
	double			dist_to_player;
	int				state;
	int				visible;
	int				is_hunting;
	mlx_image_t		*img_curr_frame;
}	t_enemy;


typedef struct keypress_s
{
	int	q;
	int	w;
	int	e;
	int	r;
	int	t;
	int	y;
	int	u;
	int	i;
	int	o;
	int	p;
	int	a;
	int	s;
	int	d;
	int	f;
	int	g;
	int	h;
	int	j;
	int	k;
	int	l;
	int	z;
	int	x;
	int	c;
	int	v;
	int	b;
	int	n;
	int	m;
	int	space;
	int	backspace;
	int	shift;
	int	enter;
	int	escape;
	int	left;
	int	right;
	int	up;
	int	down;
	int	mouse_left;
	int	mouse_right;
}			keypress_t;

//---- DOORS  ------------------------------------------------------------------

# define NUM_DOORS_MAX 4

typedef struct key_node_s
{
	dvector_t	pos;
	vector_t	pos_screen;
	double		dist_to_player;
	int			visible;
	int			collected;
	mlx_image_t	*img_curr_frame;
	key_node_t	*next;
}				key_node_t;

typedef struct key_group_s
{
	int			index;
	int			num_keys_total;
	key_node_t	*keys;
	mlx_image_t	*img_key_icon;
	mlx_image_t	*img_text_key_count;
	mlx_texture_t	**textures_frames; // TODO: delete textures in the end
	mlx_texture_t	*texture_key_icon;
	char		*texture_dir;
	int			prev_frame_index;
	int			curr_frame_index;
	vector_t	key_icon_coords;
}				key_group_t;

typedef struct door_pos_s
{
	vector_t	pos;
	door_pos_t	*next;
}				door_pos_t;

typedef struct door_group_s
{
	int			index; // unnecessary?
	door_pos_t	*door_positions;

	int			num_keys_left; // is it needed?
}				door_group_t;

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
	int			color_shroom;
	int			color_enemy;
	int			color_key_1;
	int			color_key_2;
	int			color_key_3;
	int			color_key_4;
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

//---- TRIANGLE ----------------------------------------------------------------

# define MAX_TRIANGLE_HEIGHT 150

typedef struct triangle_s
{
	dvector_t	a;
	dvector_t	b;
	dvector_t	c;
}				triangle_t;

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
# define BOX_HOVER_ON_COLOR GREEN_LIGHT
# define BOX_HOVER_OFF_COLOR GRAY_DARK
# define BOX_BORDER_COLOR YELLOW_PALE

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

//---- BUTTON ------------------------------------------------------------------

# define BUTTON_CLICKED_COLOR GREEN
# define BUTTON_HOVER_COLOR GRAY_MED
# define BUTTON_COLOR GRAY_DARK
# define BUTTON_BORDER_COLOR YELLOW_PALE
# define BUTTON_BORDER_THICKNESS 2

typedef struct button_s
{
	mlx_image_t	*text;
	vector_t	pos;
	int			width;
	int			height;
	int			background_color;
	int			border_width;
	int			border_color;
	int			state;
}				button_t;

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

//---- START MENU --------------------------------------------------------------

# define MENU_BACKGROUND_COLOR GRAY_DARK
# define MENU_BORDER_TOP_COLOR GREEN
# define MENU_BORDER_BOTTOM_COLOR BURGUNDY_DARK
# define MENU_BORDER_LEFT_COLOR TURQUOISE_LIGHT
# define MENU_BORDER_RIGHT_COLOR RED_LIGHT
# define MENU_BORDER_THICKNESS 30
# define BACK_PNG "./assets/textures/menu/back_normal.png"
# define BACK_HOVER_PNG "./assets/textures/menu/back_hover.png"

# define START_TITLE_PNG "./assets/textures/logox2.png"
# define START_START_PNG "./assets/textures/menu/start_normal.png"
# define START_START_HOVER_PNG "./assets/textures/menu/start_hover.png"
# define START_LEVEL_PNG "./assets/textures/menu/levels_normal.png"
# define START_LEVEL_HOVER_PNG "./assets/textures/menu/levels_hover.png"
# define START_EXIT_PNG "./assets/textures/menu/exit_normal.png"
# define START_EXIT_HOVER_PNG "./assets/textures/menu/exit_hover.png"
# define START_ARROW_PNG "./assets/textures/menu/arrow_pick.png"

typedef struct png_s
{
	mlx_image_t		*img;
	mlx_texture_t	*texture;
	vector_t		pos;
	int				width;
	int				height;
}					png_t;

typedef struct start_menu_s
{
	mlx_image_t	*img;
	png_t		title;
	png_t		exit;
	png_t		start;
	png_t		level;
	png_t		exit_hover;
	png_t		start_hover;
	png_t		level_hover;
	png_t		arrow_exit;
	png_t		arrow_start;
	png_t		arrow_level;
}				start_menu_t;

//---- LEVEL MENU --------------------------------------------------------------

# define LEVEL_TITLE_PNG "./assets/textures/menu/level_title.png"
# define LEADERBOARD_PNG "./assets/textures/menu/leaderboard_normal.png"
# define LEADERBOARD_HOVER_PNG "./assets/textures/menu/leaderboard_hover.png"
# define NUMBER_PNGS { "./assets/textures/level_numbers/1.png", "./assets/textures/level_numbers/2.png", "./assets/textures/level_numbers/3.png", "./assets/textures/level_numbers/4.png", "./assets/textures/level_numbers/5.png", "./assets/textures/level_numbers/6.png", "./assets/textures/level_numbers/7.png", "./assets/textures/level_numbers/8.png" }
# define MINILEVEL_BORDER_COLOR YELLOW_PALE
# define MINILEVEL_BG_COLOR BLACK
# define MINILEVEL_RECT_COLOR RED_LIGHT
# define MINILEVEL_BORDER_THICKNESS 10
# define MINILEVEL_MARGIN 10
# define PREVIEW_WALL_COLOR GRAY_VERY_DARK
# define PREVIEW_FLOOR_COLOR GRAY_DARK

//---- LEADERBOARD MENU --------------------------------------------------------

# define LEADERBOARD_LEVEL_BACKGROUND_COLOR BLACK

typedef struct minilevel_s
{
	mlx_image_t	*img;
	vector_t	pos;
	png_t		number;
	rectangle_t	number_rect;
	int			size;
	mlx_image_t	*border;
	vector_t	preview_pos;
	int			preview_width;
	int			preview_height;
	int			preview_square_size;
}				minilevel_t;

typedef struct level_menu_s
{
	mlx_image_t	*img;
	png_t		title;
	png_t		back;
	png_t		leaderboard;
	png_t		back_hover;
	png_t		leaderboard_hover;
	minilevel_t	minilevels[LEVELS];
}				level_menu_t;

//---- LEADERBOARD -------------------------------------------------------------

# define N_ENTRIES 3

typedef struct leaderboard_s
{
	mlx_image_t	*img;
	int			background_color;
	int			n_entries;
	rectangle_t	rect_title;
	mlx_image_t	*text_title;
	mlx_image_t	*text_back;
	button_t	button_back;
	rectangle_t	*rect_level;
	mlx_image_t	**text_level;
}				leaderboard_t;


typedef struct settings_menu_s
{
	mlx_image_t	*img;
	mlx_image_t	*text_settings;
	mlx_image_t	*text_e_difficulty;
	mlx_image_t	*text_minimap_view;
	int			background_color;
}				settings_menu_t;

//---- NAME MENU ---------------------------------------------------------------

# define MAX_NAME_LENGTH 12
# define ALPHABET "abcdefghijklmnopqrstuvwxyz "
# define ALPHABET_LENGTH 26

enum letters
{
	a,
	b,
	c,
	d,
	e,
	f,
	g,
	h,
	i,
	j,
	k,
	l,
	m,
	n,
	o,
	p,
	q,
	r,
	s,
	t,
	u,
	v,
	w,
	x,
	y,
	z
};

typedef struct letter_box_s
{
	char		letter[2];
	vector_t	pos;
	int			width;
	int			height;
	int			background_color;
	int			border_width;
	int			border_color;
	int			value;
	int			state;
}				letter_box_t;

typedef struct name_menu_s
{
	mlx_image_t	*img;
	mlx_image_t	*text_win_message;
	mlx_image_t	*text_enter_name;
	mlx_image_t	*text_title;
	rectangle_t	rect_title;
	rectangle_t	rect_input;
	int			current;
	char		letter;
	mlx_image_t *letters_img[ALPHABET_LENGTH];
	char		letter_str[ALPHABET_LENGTH + 1][2];
	letter_box_t	box[MAX_NAME_LENGTH];
	char		name[MAX_NAME_LENGTH + 1];
	int			letter_index[MAX_NAME_LENGTH];
	int			changed;
	int			background_color;
}				name_menu_t;

//---- GAMEOVER MENU -----------------------------------------------------------

typedef struct gameover_menu_s
{
	mlx_image_t	*img;
	mlx_image_t	*text_gameover;
	int			background_color;
	button_t	button_restart;
	button_t	button_exit;
}				gameover_menu_t;

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
	int		e_speed;
	int		e_behaviour;
	int		minimap_view;
	int		fps;
	int		fisheye;
	int		mouse;
}			settings_t;

//---- TIMER -------------------------------------------------------------------

typedef struct gametimer_s
{
	mlx_image_t	*img_time;
	char		*text_time;
	vector_t	pos;
	double		start_timestamp;
	double		pause_timestamp;
	double		run_time;
	double		delta_time;
}				gametimer_t;

//---- MAPS --------------------------------------------------------------------

typedef struct map_node_s
{
	char		*line;
	map_node_t	*next;
}			map_node_t;

typedef struct record_s
{
	int				time;
	char			*name;
	char			time_str[9];
	mlx_image_t		*text_name;
	mlx_image_t		*text_time;
	struct record_s	*next;
}			record_t;

typedef struct distraction_s
{
	bool		collected;
	bool		visible;
	dvector_t	pos;
	vector_t	pos_screen;
	double		dist_to_player;
	mlx_image_t	*img_distraction;
}			distraction_t;

typedef struct level_s
{
	char			**map;
	char			**backup;
	vector_t		starting_pos;
	char			starting_dir;
	int				map_rows;
	int				map_columns;
	map_node_t		*map_list;
	int				nodes;
	texture_t		texture[4];
	texture_t		heart;
	texture_t		heart_half;
	texture_t		heart_empty;
	int				floor_color;
	int				ceiling_color;
	int				element_found[6];
	door_group_t	door_groups[NUM_DOORS_MAX];
	key_group_t		key_groups[NUM_DOORS_MAX];
	distraction_t	*distractions;
	int				num_distractions;
	dvector_t		distraction;
	double			distraction_amount;
	record_t		*records;
	mlx_image_t		*heart_img;
	mlx_image_t		*heart_half_img;
	mlx_image_t		*heart_empty_img;
}			level_t;

//---- HALO --------------------------------------------------------------------

typedef struct halo_s
{
	mlx_image_t	*img;
	int			active;
	int			color;
	double		timestamp;
}				halo_t;

//---- HEARTS ------------------------------------------------------------------

# define HEART_FULL_PNG "./assets/textures/heart/full.png"
# define HEART_EMPTY_PNG "./assets/textures/heart/empty.png"
# define HEARTS 3
# define HEART_GAP 10

typedef struct heart_s
{
	png_t		full;
	png_t		empty;
}				heart_t;

//---- CUB3D -------------------------------------------------------------------

enum state
{
	STATE_START,
	STATE_LEVEL,
	STATE_LEADERBOARD,
	STATE_SETTINGS,
	STATE_GAME,
	STATE_PAUSE,
	STATE_ENTERNAME,
	STATE_GAMEOVER
};

typedef struct cub3d_s
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	double			start_timestamp;
	double			frame_time;
	double			frame_start_timestamp;
	double			run_time;
	double			delta_time;
	double			pause_timestamp;
	int				time_finished;
	vector_t		mouse;
	vector_t		mouse_set_pos;
	int				on_minimap;
	vector_t		orig_minimap_pos;
	keypress_t		keys;
	player_t		player;
	double			fov;
	minimap_t		minimap;
	halo_t			halo;
	heart_t			hearts[HEARTS];
	ray_t			*rays;
	int				state;
	int				prev;
	int				num_enemies;
	start_menu_t	start_menu;
	level_menu_t	level_menu;
	leaderboard_t	leaderboard;
	settings_menu_t	settings_menu;
	pause_menu_t	pause_menu;
	name_menu_t		name_menu;
	gameover_menu_t	gameover_menu;
	settings_t		settings;
	gametimer_t		timer;
	int				n_levels;
	level_t			*levels;
	level_t			*level;
	t_enemy			*enemy;
	mlx_texture_t	*frames_idle[NUM_FRAMES_ENEMY_IDLE];
	mlx_texture_t	*frames_walking[NUM_FRAMES_ENEMY_WALKING];
	mlx_texture_t	*distraction_texture;
	int				curr_frame_index_walking;
	int				prev_frame_index_walking;
	int				curr_frame_index_idle;
	int				prev_frame_index_idle;
	int				speedrun;
	bool			active;
}					cub3d_t;

#endif