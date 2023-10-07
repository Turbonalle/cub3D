# Output executable name
TARGET = cub3D

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Werror -Wextra

# Directories
SRC_PATH = ../src
INC_PATH = ../incl
LIB_PATH = ../lib
MLX42DIR = $(LIB_PATH)/MLX42
LIBFTDIR = $(LIB_PATH)/libft
OBJ_PATH = ../obj

# Source files and object files
SRC_FILES = $(wildcard $(SRC_PATH)/*/*.c)
OBJ_FILES = $(patsubst $(SRC_PATH)/%.c, $(OBJ_PATH)/%.o, $(SRC_FILES))

# Include directories
INC = -I$(INC_PATH) -I$(MLX42DIR)/include -I"/Users/$(USER)/.brew/opt/glfw/include"

# Libraries
LIBS = -L$(LIBFTDIR) -lft $(MLX42DIR)/build/libmlx42.a -ldl -lglfw -pthread -lm
# -framework OpenGL -framework AppKit

all: libmlx $(TARGET)

libmlx:
	@cmake $(MLX42DIR) -B $(MLX42DIR)/build && make -C $(MLX42DIR)/build -j4

$(TARGET): $(OBJ_FILES) libft
	$(CC) $(CFLAGS) $(OBJ_FILES) $(LIBS) -o $@

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

# Build the libft library using the libft Makefile
libft:
	@make -C $(LIBFTDIR)

clean:
	@rm -f $(OBJ_FILES)
	@rm -rf $(OBJ_PATH)
	@rm -rf $(MLX42DIR)/build
	@make -C $(LIBFTDIR) clean

fclean: clean
	@rm -f $(TARGET)
	@make -C $(LIBFTDIR) fclean

re: fclean all

.PHONY: all clean fclean re libft libmlx