# Output executable name
TARGET = cub3D

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Werror -Wextra

# Directories
SRCDIR = src
INCDIR = incl
LIBDIR = lib
MLX42DIR = $(LIBDIR)/MLX42
LIBFTDIR = $(LIBDIR)/libft
OBJDIR = obj

# Source files and object files
SRC_FILES = $(wildcard $(SRCDIR)/*.c)
OBJ_FILES = $(SRC_FILES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# Include directories
INC = -I$(INCDIR) -I$(MLX42DIR)/include -I$(LIBFTDIR)/include -I"/Users/$(USER)/.brew/opt/glfw/include"

# Libraries
LIBS = -L$(MLX42DIR)/build -lmlx42 -L$(LIBFTDIR) -lft -L"/Users/$(USER)/.brew/opt/glfw/lib" -lglfw -framework OpenGL -framework AppKit

all: $(TARGET)

$(TARGET): $(OBJ_FILES) libft
	$(CC) $(CFLAGS) $(OBJ_FILES) $(LIBS) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

# Build the libft library using the libft Makefile
libft:
	@make -C $(LIBFTDIR)

clean:
	@rm -f $(OBJ_FILES)
	@rm -rf $(OBJDIR)
	@make -C $(LIBFTDIR) clean

fclean: clean
	@rm -f $(TARGET)
	@make -C $(LIBFTDIR) fclean

re: fclean all

.PHONY: all clean fclean re libft