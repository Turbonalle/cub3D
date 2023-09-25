# Output executable name
TARGET = cub3D

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Werror -Wextra

# Directories
SRC_PATH = src
INC_PATH = incl
LIB_PATH = lib
MLX42DIR = $(LIB_PATH)/MLX42
LIBFTDIR = $(LIB_PATH)/libft
OBJ_PATH = obj

# Source files and object files
SRC_FILES = $(wildcard $(SRC_PATH)/*.c)
OBJ_FILES = $(SRC_FILES:$(SRC_PATH)/%.c=$(OBJ_PATH)/%.o)

# Include directories
INC = -I$(INC_PATH) -I$(MLX42DIR)/include -I$(LIBFTDIR)/include -I"/Users/$(USER)/.brew/opt/glfw/include"

# Libraries
LIBS = -L$(MLX42DIR)/build -lmlx42 -L$(LIBFTDIR) -lft -L"/Users/$(USER)/.brew/opt/glfw/lib" -lglfw -framework OpenGL -framework AppKit

all: $(TARGET)

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
	@make -C $(LIBFTDIR) clean

fclean: clean
	@rm -f $(TARGET)
	@make -C $(LIBFTDIR) fclean

re: fclean all

.PHONY: all clean fclean re libft