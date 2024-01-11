#ifndef CONSTS_H
# define CONSTS_H

# define FAIL 0
# define SUCCESS 1
# define FALSE 0
# define TRUE 1
# define WIN 1
# define LOSE 0

# define WIDTH 1280
# define HEIGHT 720

# define MAP_ALL_ELEMENTS "NSWE 01 ABCD abcd neswijkl Gm hro"
# define MAP_ALL_BUT_WALL "NSWE0ABCDabcdneswijklGmhro"
# define MAP_DIRECTIONS "NSWE"
# define MAP_ELEMENTS "01"
# define ENEMIES "neswijkl"

# define NORTH 'N'
# define SOUTH 'S'
# define WEST 'W'
# define EAST 'E'

# define EMPTY '0'
# define WALL '1'

# define MOVEMENT_SPEED 6
# define ROTATION_SPEED 2
# define MOUSE_SENSITIVITY 0.004
# define MOUSE_MAX_SENSITIVITY 0.005
# define MOUSE_MIN_SENSITIVITY 0.001

# define ENEMY_SPEED 0.03
# define ENEMY_ROT_SPEED 10
# define ENEMY_FREEZE	2.0
# define ENEMY_EATING_SPEED 0.1
# define ENEMY_RADIUS 0.40

# define INVULNERABILITY_TIME 2

# define HALO_THICKNESS 50
# define HALO_TIME 2

# define LEVELS 8

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
# define MINIMAP_COLOR_SHROOM GREEN_DARK
# define MINIMAP_COLOR_KEY_1 RED
# define MINIMAP_COLOR_KEY_2 GREEN_BRIGHT
# define MINIMAP_COLOR_KEY_3 YELLOW_LIGHT
# define MINIMAP_COLOR_KEY_4 BLUE
# define MINIMAP_TRANSPARENCY 20

# define RECORD_FILE "./assets/records.txt"
# define LEVEL_PREFIX "./assets/levels/level"

# define TEXTURE_MUSHROOM "./assets/textures/mushrooms/2.png"
# define TEXTURE_MUSHROOM_THROWN "./assets/textures/mushrooms/1.png"
# define TEXTURE_MUSHROOM_COUNTER "./assets/textures/mushrooms/2x2.png"
# define TEXTURE_HEART_FULL "./assets/textures/heart/full.png"
# define TEXTURE_HEART_HALF "./assets/textures/heart/half.png"
# define TEXTURE_HEART_EMPTY "./assets/textures/heart/empty.png"
# define TEXTURE_KEY_1 "./assets/textures/keys_static/red.png"
# define TEXTURE_KEY_2 "./assets/textures/keys_static/green.png"
# define TEXTURE_KEY_3 "./assets/textures/keys_static/yellow.png"
# define TEXTURE_KEY_4 "./assets/textures/keys_static/blue.png"

# define TEXTURE_DOOR_A "./assets/textures/doors/door_red.png"
# define TEXTURE_DOOR_B "./assets/textures/doors/door_green.png"
# define TEXTURE_DOOR_C "./assets/textures/doors/door_yellow.png"
# define TEXTURE_DOOR_D "./assets/textures/doors/door_blue.png"
# define TEXTURE_DOOR_OPEN "./assets/textures/doors/door_unlocked.png"

# define ANIMATION_INTERVAL_MS 66.6667

# define FRAME_PATH_KEY_1 "./assets/textures/red/"
# define FRAME_PATH_KEY_2 "./assets/textures/green/"
# define FRAME_PATH_KEY_3 "./assets/textures/yellow/"
# define FRAME_PATH_KEY_4 "./assets/textures/blue/"
# define NUM_FRAMES_KEY 24
# define KEY_NORMAL_SCALE_DISTANCE 13

# define FRAME_PATH_STARS "./assets/textures/stars_pink/"
# define NUM_FRAMES_STARS 4
# define FRAME_PATH_ENEMY_IDLE "./assets/textures/green_idle/"
# define FRAME_PATH_ENEMY_IDLE_RIGHT "./assets/textures/green_idle_right/"
# define FRAME_PATH_ENEMY_IDLE_RIGHT_45 "./assets/textures/green_idle_right45/"
# define FRAME_PATH_ENEMY_IDLE_STRAIGHT "./assets/textures/green_idle_straight/"
# define FRAME_PATH_ENEMY_IDLE_LEFT_45 "./assets/textures/green_idle_left45/"
# define FRAME_PATH_ENEMY_IDLE_LEFT "./assets/textures/green_idle_left/"
# define FRAME_PATH_ENEMY_WALKING "./assets/textures/red_walking/"
# define FRAME_PATH_ENEMY_WALKING_RIGHT "./assets/textures/red_walking_right/"
# define FRAME_PATH_ENEMY_WALKING_RIGHT_45 "./assets/textures/red_walking_right45/"
# define FRAME_PATH_ENEMY_WALKING_STRAIGHT "./assets/textures/red_walking_straight/"
# define FRAME_PATH_ENEMY_WALKING_LEFT_45 "./assets/textures/red_walking_left45/"
# define FRAME_PATH_ENEMY_WALKING_LEFT "./assets/textures/red_walking_left/"
# define NUM_FRAMES_ENEMY_IDLE 8
# define NUM_FRAMES_ENEMY_WALKING 8
# define ENEMY_NORMAL_SCALE_DISTANCE 20

# define DISTRACTION_NORMAL_SCALE_DISTANCE 13

# define MINIMAP_ZOOM_INCREMENT 5

# define FOV 60
# define FOV_INCREMENT 5
# define FOV_MIN 1
# define FOV_MAX 360

# define X 0
# define Y 1

# define STATIONARY 0
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