# NAME = libft.a
# SRC =	ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
# 		ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c \
# 		ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
# 		ft_putstr_fd.c ft_split.c ft_strchr.c ft_strcmp.c ft_strdup.c ft_striteri.c ft_strjoin.c \
# 		ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c \
# 		ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c \
# 		get_next_line.c get_next_line_utils.c
# OBJECTS =	ft_atoi.o ft_bzero.o ft_calloc.o ft_isalnum.o ft_isalpha.o ft_isascii.o \
# 			ft_isdigit.o ft_isprint.o ft_itoa.o ft_memchr.o ft_memcmp.o ft_memcpy.o \
# 			ft_memmove.o ft_memset.o ft_putchar_fd.o ft_putendl_fd.o ft_putnbr_fd.o \
# 			ft_putstr_fd.o ft_split.o ft_strchr.o ft_strcmp.o ft_strdup.o ft_striteri.o ft_strjoin.o \
# 			ft_strlcat.o ft_strlcpy.o ft_strlen.o ft_strmapi.o ft_strncmp.o ft_strnstr.o \
# 			ft_strrchr.o ft_strtrim.o ft_substr.o ft_tolower.o ft_toupper.o \
# 			get_next_line.o get_next_line_utils.o

# all: $(NAME)

# $(NAME):
# 	@cc -Wall -Wextra -Werror -I -c $(SRC)
# 	@ar rc $(NAME) $(OBJECTS)
# 	@ranlib $(NAME)
# 	@echo "Libft:		Compiled!"

# clean:
# 	@rm -f $(OBJECTS)
# 	@echo "Libft:		Object files removed!"

# fclean: clean
# 	@rm -f $(NAME)
# 	@echo "Libft:		Library removed!"

# re: fclean all

NAME = libft.a
SRC =	ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
		ft_isdigit.c ft_isprint.c ft_itoa.c ft_lstadd_back.c ft_lstadd_front.c \
		ft_lstclear.c ft_lstdelone.c ft_lstiter.c ft_lstlast.c ft_lstmap.c \
		ft_lstnew.c ft_lstsize.c ft_memchr.c ft_memcmp.c ft_memcpy.c \
		ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
		ft_putstr_fd.c ft_split.c ft_strchr.c ft_strcmp.c ft_strdup.c ft_striteri.c ft_strjoin.c \
		ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c \
		ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c \
		get_next_line.c get_next_line_utils.c
OBJECTS = $(SRC:%.c=%.o)
HEADERS = libft.h

all: $(NAME)

$(NAME): $(OBJECTS)
	@ar rc $(NAME) $(OBJECTS)
	@ranlib $(NAME)
	@echo "Libft:		Compiled!"

%.o: %.c
	@cc -Wall -Wextra -Werror -I . -c $< -o $@

clean:
	@rm -f $(OBJECTS)
	@echo "Libft:		Object files removed!"

fclean: clean
	@rm -f $(NAME)
	@echo "Libft:		Library removed!"

re: fclean all