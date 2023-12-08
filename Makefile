# Coder Alias
USER_NAME = Josu&Iban
# Compiler and flags
CC        = gcc
CFLAGS    = -Wall -Wextra -Werror -I $(INC_DIR) -I $(MINILIBX_DIR) -I $(LIBFT_DIR)/include -O3 -g3 -fsanitize=address
# Platform to run project (Linux and Mac)
PLATFORM  := $(shell uname)
# Directories
SRC_DIR   = 	src/
SRC_DIR_BONUS =	src_bonus/
INC_DIR   = 	inc/
LIBFT_DIR = 	libraries/libft/
OBJ_DIR   = 	src/
OBJ_DIR_BONUS   = 	src_bonus/
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
SRC_FILE =	 	pixel_put.c \
				ray_calc.c \
				ray_calc_aux.c \
				raycaster_flat.c \
				texture.c \
				custom_split.c \
				elems_aux.c \
				elems.c \
				fillmap.c \
				parse_aux.c \
				errors.c \
				move.c \
				move_aux.c \
				checks.c \
				main.c
SRC_FILE_BONUS = pixel_put_bonus.c \
				ray_calc_bonus.c \
				ray_calc_aux_bonus.c \
				raycaster_flat_bonus.c \
				texture_bonus.c \
				custom_split_bonus.c \
				elems_aux_bonus.c \
				elems_bonus.c \
				fillmap_bonus.c \
				parse_aux_bonus.c \
				errors_bonus.c \
				move_bonus.c \
				move_aux_bonus.c \
				checks_bonus.c \
				main_bonus.c \
				collisions_bonus.c

SRC      =				$(addprefix $(SRC_DIR), $(SRC_FILE))
OBJ_FILE =				$(SRC_FILE:.c=.o)
OBJ      = 				$(addprefix $(OBJ_DIR), $(OBJ_FILE))

SRC_BONUS =				$(addprefix $(SRC_DIR_BONUS), $(SRC_FILE_BONUS))
OBJ_FILE_BONUS =		$(SRC_FILE_BONUS:.c=.o)
OBJ_BONUS     = 		$(addprefix $(OBJ_DIR_BONUS), $(OBJ_FILE_BONUS))

# Binary name for your program
CODE_BIN = $(BIN_DIR)cub3D
# Static library
LIBFT    = $(LIBFT_DIR)libft.a
MINILIBX = $(MINILIBX_DIR)libmlx.a
# Output executable
NAME     = cub3D
NAME_BONUS = cub3D_bonus
# Create the obj/ and bin/ directories if they don't exist
$(shell mkdir -p $(OBJ_DIR))
$(shell mkdir -p $(OBJ_DIR_BONUS))
# Variable to control if the library has been built
LIBFT_BUILT    = no
MINILIBX_BUILT = no

.SILENT:

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

$(OBJ_DIR_BONUS)%.o: $(SRC_DIR_BONUS)%.c
	$(CC) $(CFLAGS) -Imlx -c $< -o $@

bonus: $(LIBFT) $(MINILIBX) $(OBJ_BONUS)
	$(CC) $(CFLAGS) $(OBJ_BONUS) -L$(LIBFT_DIR) -lft -L/usr/lib -L$(MINILIBX_DIR) $(LINKING) -o $(NAME_BONUS)
	@echo "✔ $(USER_NAME)'s $(NAME_BONUS) compilation"

clean:
	$(RM) $(OBJ) $(OBJ_BONUS)
	@echo "✔ $(USER_NAME)'s $(NAME) .o files removal"
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(MINILIBX_DIR) clean

fclean: clean
	$(RM) $(NAME) $(NAME_BONUS)
	@echo "✔ $(USER_NAME)'s $(NAME) executable and .o files removal"
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
