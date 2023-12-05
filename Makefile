# Coder Alias
USER_NAME = Josu&Iban
# Compiler and flags
CC        = gcc
CFLAGS    = -Wall -Wextra -Werror -I $(INC_DIR) -I $(MINILIBX_DIR) -I $(LIBFT_DIR)/include -O3 -g3 #-fsanitize=address
# Platform to run project (Linux and Mac)
PLATFORM  := $(shell uname)
# Directories
SRC_DIR   = src/
INC_DIR   = inc/
LIBFT_DIR = libraries/libft/
OBJ_DIR   = src/
ifeq  ($(PLATFORM),Linux)
MINILIBX_DIR = libraries/minilib/minilibx-linux/
LINKING = -lmlx_Linux -lXext -lX11 -lm
BIN_DIR   = bin/linux/
else
MINILIBX_DIR = libraries/minilib/minilibx_opengl_20191021/
LINKING = -lmlx -framework OpenGL -framework AppKit
BIN_DIR   = bin/IOS/
endif
# Source files
SRC_FILE = 	pixel_put.c \
			ray_calc.c \
			raycaster_flat.c \
			texture.c \
			custom_split.c \
			elems_aux.c \
			elems.c \
			fillmap.c \
			parse_aux.c \
			errors.c \
			move.c \
			main.c

SRC      = $(addprefix $(SRC_DIR), $(SRC_FILE))
OBJ_FILE = $(SRC_FILE:.c=.o)
OBJ      = $(addprefix $(OBJ_DIR), $(OBJ_FILE))
# Binary name for your program
CODE_BIN = $(BIN_DIR)cub3D
# Static library
LIBFT    = $(LIBFT_DIR)libft.a
MINILIBX = $(MINILIBX_DIR)libmlx.a
# Output executable
NAME     = cub3D
# Create the obj/ and bin/ directories if they don't exist
$(shell mkdir -p $(OBJ_DIR))
# Variable to control if the library has been built
LIBFT_BUILT    = no
MINILIBX_BUILT = no

all: $(NAME)

$(NAME): $(LIBFT) $(MINILIBX) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -L$(LIBFT_DIR) -lft -L/usr/lib -L$(MINILIBX_DIR) $(LINKING) -o $@
	@echo "✔ $(USER_NAME)'s $(NAME) compilation"

$(LIBFT):
	@if [ "$(LIBFT_BUILT)" = "no" ]; then \
		$(MAKE) -C $(LIBFT_DIR); \
		LIBFT_BUILT=yes; \
	fi

$(MINILIBX):
	@if [ "$(MINILIBX_BUILT)" = "no" ]; then \
		$(MAKE) -C $(MINILIBX_DIR); \
		MINILIBX_BUILT=yes; \
	fi

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) -Imlx -c $< -o $@

clean:
	$(RM) $(OBJ)
	@echo "✔ $(USER_NAME)'s $(NAME) .o files removal"
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(MINILIBX_DIR) clean

fclean: clean
	$(RM) $(NAME)
	@echo "✔ $(USER_NAME)'s $(NAME) executable and .o files removal"
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
