#ifndef CONSTS_H
# define CONSTS_H

# define FAIL 0
# define SUCCESS 1
# define FALSE 0
# define TRUE 1

# define WIDTH 1280
# define HEIGHT 720

# define MAP_ALL_ELEMENTS "NSWE 01 ABCD abcd nesw -|"
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

# define MOVEMENT_SPEED 6
# define ROTATION_SPEED 1.5

# define ENEMY_SPEED 0.05
# define ENEMY_ROT_SPEED 0.1

# define MINIMAP_SIZE_PERCENTAGE 20
# define MINIMAP_MAX_SIZE_PERCENTAGE 100
# define MINIMAP_MIN_SIZE_PERCENTAGE 10
# define MINIMAP_COLOR_PLAYER YELLOW
# define MINIMAP_COLOR_PLAYERDIR WHITE
# define MINIMAP_COLOR_FOV SADDLEBROWN
# define MINIMAP_COLOR_EMPTY DARK_GRAY
# define MINIMAP_COLOR_FLOOR BLACK
# define MINIMAP_COLOR_WALL GRAY
# define MINIMAP_COLOR_ENEMY OLIVE
# define MINIMAP_COLOR_KEY_1 ORANGE_RED
# define MINIMAP_COLOR_KEY_2 SPRING_GREEN
# define MINIMAP_COLOR_KEY_3 GOLD
# define MINIMAP_COLOR_KEY_4 TEAL
# define MINIMAP_TRANSPARENCY 20

# define MINIMAP_TEXTURE_KEY_1 "./assets/textures/key_red_static.png"
# define MINIMAP_TEXTURE_KEY_2 "./assets/textures/key_green_static.png"
# define MINIMAP_TEXTURE_KEY_3 "./assets/textures/key_yellow_static.png"
# define MINIMAP_TEXTURE_KEY_4 "./assets/textures/key_blue_static.png"

# define ANIMATION_INTERVAL_MS 66,6667

# define MINIMAP_ZOOM_INCREMENT 5

# define FOV 60
# define FOV_INCREMENT 5
# define FOV_MIN 1
# define FOV_MAX 360

# define X 0
# define Y 1

# define STAIONARY 0
# define NORMAL 1
# define WANDERING 2
enum elements
{
	NO,
	SO,
	WE,
	EA,
	F,
	C
};

#endif