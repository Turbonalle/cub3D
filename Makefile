# Output executable name
TARGET = cub3D

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Werror -Wextra -g
DEBUG_FLAGS = -fsanitize=address
ALLOWED_CHAR_MACRO_BONUS = -D MAP_ALL_ELEMENTS="MAP_ALL_ELEMENTS_BONUS"

# Directories
SRC_PATH = src
INC_PATH = incl
LIB_PATH = lib
MLX42DIR = $(LIB_PATH)/MLX42
LIBFTDIR = $(LIB_PATH)/libft
OBJ_PATH = obj

# Source files and object files
SRC_FILES =	src/animation/animation_utils.c \
			src/animation/assign_z_add_all.c \
			src/animation/assign_z_depth_cases.c \
			src/animation/assign_z_depth_utils.c \
			src/animation/assign_z_depth.c \
			src/animation/draw_distractions.c \
			src/animation/draw_enemies.c \
			src/animation/draw_game_entities.c \
			src/animation/draw_keys.c \
			src/animation/draw_utils.c \
			src/animation/frame_update_utils.c \
			src/animation/sort_distractions.c \
			src/animation/sort_enemies.c \
			src/animation/sort_keys.c \
			src/color/get_color.c \
			src/color/mix_color.c \
			src/color/set_color.c \
			src/color/transparency.c \
			src/core/cursor.c \
			src/core/game_over.c \
			src/core/halo_fade.c \
			src/core/halo_time.c \
			src/core/halo.c \
			src/core/load_level.c \
			src/core/main_utils.c \
			src/core/main.c \
			src/core/record_utils.c \
			src/core/records.c \
			src/core/set_z_of_all_images.c \
			src/core/start_game.c \
			src/core/time_utils.c \
			src/core/time.c \
			src/core/timer_utils.c \
			src/core/unsorted_utils.c \
			src/distractions/distractions.c \
			src/draw/bresenham.c \
			src/draw/draw_background.c \
			src/draw/draw_button.c \
			src/draw/draw_floor.c \
			src/draw/draw_line.c \
			src/draw/draw_menu_border.c \
			src/draw/draw_rectangle.c \
			src/draw/draw_slider.c \
			src/draw/draw_textured_line_utils.c \
			src/draw/draw_textured_line.c \
			src/draw/draw_triangle.c \
			src/draw/draw_world.c \
			src/enemy/collision_utils_additional.c \
			src/enemy/collision_utils_extra.c \
			src/enemy/collision_utils.c \
			src/enemy/distraction_utils.c \
			src/enemy/draw_utils_additional.c \
			src/enemy/enemy_cursor_position.c \
			src/enemy/enemy_cursor.c \
			src/enemy/enemy_distraction_utils.c \
			src/enemy/enemy_distraction.c \
			src/enemy/enemy_draw_utils.c \
			src/enemy/enemy_drawing.c \
			src/enemy/enemy_init_additional.c \
			src/enemy/enemy_init_utils.c \
			src/enemy/enemy_ray.c \
			src/enemy/enemy_utils_additional.c \
			src/enemy/enemy_utils_extra.c \
			src/enemy/enemy_utils.c \
			src/enemy/enemy_vision.c \
			src/enemy/enemy.c \
			src/enemy/unsorted_utils.c \
			src/hearts/delete_hearts.c \
			src/hearts/init_hearts_utils.c \
			src/hearts/init_hearts.c \
			src/hearts/toggle_hearts.c \
			src/init/cub3d_utils.c \
			src/init/door_key_utils.c \
			src/init/door_utils.c \
			src/init/enemy_frame_utils.c \
			src/init/free_utils_additional.c \
			src/init/free_utils_extra.c \
			src/init/gameover_utils.c \
			src/init/init_cub3d.c \
			src/init/init_door_textures.c \
			src/init/init_doors_and_keys.c \
			src/init/init_freeing_utils.c \
			src/init/init_gameover_menu.c \
			src/init/init_intro.c \
			src/init/init_leaderboard.c \
			src/init/init_level_menu.c \
			src/init/init_name_menu.c \
			src/init/init_pause_menu.c \
			src/init/init_shrooms.c \
			src/init/init_start_menu.c \
			src/init/init_textures.c \
			src/init/key_utils.c \
			src/init/leaderboard_utils.c \
			src/init/level_additional_utils.c \
			src/init/level_menu_utils.c \
			src/init/level_utils.c \
			src/init/name_utils.c \
			src/init/pause_checkbox_utils.c \
			src/init/pause_menu_utils.c \
			src/init/start_menu_utils.c \
			src/init/unsorted_utils.c \
			src/input/game_input_utils.c \
			src/input/handle_close.c \
			src/input/handle_keys.c \
			src/input/handle_mouse.c \
			src/input/key_utils.c \
			src/input/keyrelease_utils.c \
			src/input/mouse_game.c \
			src/input/mouse_menu.c \
			src/input/mouse_utils.c \
			src/key_count_info/key_count_string_utils.c \
			src/key_count_info/key_counts.c \
			src/math/dda_utils.c \
			src/math/dda.c \
			src/math/math_utils.c \
			src/math/math.c \
			src/menu/delete_menu.c \
			src/menu/menu_utils.c \
			src/menu/name_menu_utils.c \
			src/menu/name_utils.c \
			src/menu/toggle_gameover_menu.c \
			src/menu/toggle_intro.c \
			src/menu/toggle_leaderboard.c \
			src/menu/toggle_level_menu.c \
			src/menu/toggle_name_menu.c \
			src/menu/toggle_pause_menu.c \
			src/menu/toggle_start_menu.c \
			src/menu/update_gameover_menu.c \
			src/menu/update_leaderboard.c \
			src/menu/update_level_menu.c \
			src/menu/update_name_menu.c \
			src/menu/update_start_menu.c \
			src/minimap/hiding_utils.c \
			src/minimap/minimap_draw_grid.c \
			src/minimap/minimap_draw_player.c \
			src/minimap/minimap_hover.c \
			src/minimap/minimap_move.c \
			src/minimap/minimap_zoom_in.c \
			src/minimap/minimap_zoom_out.c \
			src/minimap/minimap.c \
			src/parse/get_level_color.c \
			src/parse/get_level_elements.c \
			src/parse/get_level_texture.c \
			src/parse/get_level_utils.c \
			src/parse/get_level.c \
			src/parse/map_validity.c \
			src/parse/read_utils.c \
			src/pause/center_image.c \
			src/pause/hover.c \
			src/pause/pause_text.c \
			src/pause/update_pause_menu.c \
			src/pause/update_utils.c \
			src/player/collision_utils.c \
			src/player/collision.c \
			src/player/fov.c \
			src/player/player_is_hit.c \
			src/player/player_movement_utils.c \
			src/player/player_movement.c \
			src/raycasting/raycast_additional_utils.c \
			src/raycasting/raycast_utils_extra.c \
			src/raycasting/raycast_utils.c \
			src/raycasting/raycasting.c \
			src/utils/check_utils.c \
			src/utils/drawing_utils.c \
			src/utils/error_utils.c \
			src/utils/free_utils.c \
			src/utils/memory_additional_utils.c \
			src/utils/memory_extra_plus.c \
			src/utils/memory_utils_extra.c \
			src/utils/memory_utils.c \
			src/utils/nullify_enemy_frames.c \
			src/utils/nullify_level_menu.c \
			src/utils/nullify_menus.c \
			src/utils/nullify_utils.c \
			src/utils/nullify.c \
			src/utils/shroom_utils.c
OBJ_FILES = $(patsubst $(SRC_PATH)/%.c, $(OBJ_PATH)/%.o, $(SRC_FILES))

# Include directories
INC = -I$(INC_PATH) -I$(MLX42DIR)/include -I$(LIBFTDIR)/include -I"/Users/$(USER)/.brew/opt/glfw/include"

# Libraries
LIBS = -L$(MLX42DIR)/build -lmlx42 -L$(LIBFTDIR) -lft -L"/Users/$(USER)/.brew/opt/glfw/lib" -lglfw -framework OpenGL -framework AppKit

all: $(TARGET)

$(TARGET): $(OBJ_FILES) libft mlx
	$(CC) $(CFLAGS) $(OBJ_FILES) $(LIBS) -o $@

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

bonus: CFLAGS += $(ALLOWED_CHAR_MACRO_BONUS)
bonus: all

debug: CFLAGS += $(DEBUG_FLAGS)
debug: all

# Build the libft library using the libft Makefile
libft:
	@make -C $(LIBFTDIR)

mlx:
	@cmake -S $(MLX42DIR) -B $(MLX42DIR)/build
	@cmake --build $(MLX42DIR)/build -j4

clean:
	@rm -f $(OBJ_FILES)
	@rm -rf $(OBJ_PATH)
	@make -C $(LIBFTDIR) clean
	rm -rf $(MLX42DIR)/build

fclean: clean
	@rm -f $(TARGET)
	@make -C $(LIBFTDIR) fclean

re: fclean all

.PHONY: all clean fclean re libft