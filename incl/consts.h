#ifndef CONSTS_H
# define CONSTS_H

# define FAIL 0
# define SUCCESS 1
# define FALSE 0
# define TRUE 1

# define WIDTH 1280
# define HEIGHT 720

# define MAP_ALL_ELEMENTS "NSWE 01 ABCD abcd nesw G"
# define MAP_DIRECTIONS "NSWE"
# define MAP_ELEMENTS "01"
# define ENEMIES "nesw"

# define NORTH 'N'
# define SOUTH 'S'
# define WEST 'W'
# define EAST 'E'

# define EMPTY '0'
# define WALL '1'

# define MOVEMENT_SPEED 6
# define ROTATION_SPEED 2

# define ENEMY_SPEED 0.05
# define ENEMY_ROT_SPEED 0.1
# define ENEMY_FREEZE	2.0

# define MINIMAP_SIZE_PERCENTAGE 20
# define MINIMAP_MAX_SIZE_PERCENTAGE 100
# define MINIMAP_MIN_SIZE_PERCENTAGE 5
# define MINIMAP_COLOR_PLAYER ORANGE
# define MINIMAP_COLOR_PLAYERDIR WHITE
# define MINIMAP_COLOR_FOV BURGUNDY_DARK
# define MINIMAP_COLOR_EMPTY BLACK
# define MINIMAP_COLOR_FLOOR GRAY_DARK
# define MINIMAP_COLOR_WALL BLACK
# define MINIMAP_COLOR_ENEMY TURQUOISE
# define MINIMAP_COLOR_KEY_1 RED
# define MINIMAP_COLOR_KEY_2 GREEN_BRIGHT
# define MINIMAP_COLOR_KEY_3 YELLOW_LIGHT
# define MINIMAP_COLOR_KEY_4 BLUE
# define MINIMAP_TRANSPARENCY 20

# define TEXTURE_KEY_1 "./assets/textures/key_red_static.png"
# define TEXTURE_KEY_2 "./assets/textures/key_green_static.png"
# define TEXTURE_KEY_3 "./assets/textures/key_yellow_static.png"
# define TEXTURE_KEY_4 "./assets/textures/key_blue_static.png"
# define FRAME_PATH_KEY_1 "./assets/textures/red/"
# define FRAME_PATH_KEY_2 "./assets/textures/green/"
# define FRAME_PATH_KEY_3 "./assets/textures/yellow/"
# define FRAME_PATH_KEY_4 "./assets/textures/blue/"
# define KEY_NORMAL_SCALE_DISTANCE 13
# define NUM_FRAMES_KEY 24

# define ANIMATION_INTERVAL_MS 66.6667

# define FRAME_PATH_ENEMY_BLUE_IDLE "./assets/textures/blue_idle/"
# define FRAME_PATH_ENEMY_GREEN_WALKING "./assets/textures/green_walking/"
# define ENEMY_NORMAL_SCALE_DISTANCE 20
# define NUM_FRAMES_ENEMY_IDLE 8
# define NUM_FRAMES_ENEMY_WALKING 8

# define MINIMAP_ZOOM_INCREMENT 5

# define PLAYER_HEALTH 3
# define INVULNERABILITY_TIME 1

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