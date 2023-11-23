NAME = raycast
LIBNAME = 	libft.a
MLX = 		libmlx_Linux.a
#NAMEBONUS = minishell_bonus

SRC = 			raycaster_flat.c
#SRCBONUS = 	

OBJ = $(SRC:.c=.o)
#OBJBONUS = $(SRCBONUS:.c=.o)

#FLAGS = -Wall -Wextra -Werror -g3 -Ilibmlx -fsanitize=address
FLAGS = -Wall -Wextra -Werror
FLAGSLST = -Lmlx -lmlx -L/usr/lib -Imlx -lXext -lX11 -lm -lz
#MLXFLAGS = -framework OpenGL -framework AppKit
NONE='\033[0m'
GREEN='\033[32m'
GRAY='\033[2;37m'
CURSIVE='\033[3m'

all: $(NAME)

$(MLX):
	@echo $(CURSIVE)$(GRAY) "     - Compiling MIINILIB $(MLX)..." $(NONE)
	@make -C ../mlx-linux all
	@cp ../mlx-linux/$(MLX) $(MLX)
	@echo $(GREEN)"- Compiled -"$(NONE)

$(NAME): $(OBJ) $(LIBNAME) $(MLX)
	@echo $(CURSIVE)$(GRAY) "     - Compiling $(NAME)..." $(NONE)
	@gcc $(FLAGS) $(FLAGSLST) $(MLXFLAGS)  $(OBJ) $(LIBNAME) $(MLX) -o $(NAME)
	@echo $(GREEN)"- Compiled -"$(NONE)

bonus: $(OBJBONUS) $(LIBNAME)
	@echo $(CURSIVE)$(GRAY) "     - Compiling $(NAMEBONUS)..." $(NONE)
	@gcc $(FLAGS)   $(OBJBONUS) $(LIBNAME) -o $(NAMEBONUS)
	@echo $(GREEN)"- Compiled -"$(NONE)

$(LIBNAME):
	@echo $(CURSIVE)$(GRAY) "     - Compiling LIBFT $(LIBNAME)..." $(NONE)
	@$(MAKE) -C ../libft all
	@cp ../libft/libft.a $(LIBNAME)
	@echo $(GREEN)"- Compiled -"$(NONE)

%.o: %.c
	$(CC) -c $(FLAGS) $^ -o $@

clean:
	@echo $(CURSIVE)$(GRAY) "     - Removing object files..." $(NONE)
	@$(MAKE) -C ../libft clean
	@$(MAKE) -C ../mlx-linux clean
	@rm -rf $(OBJ) $(OBJBONUS)

fclean: clean
	@echo $(CURSIVE)$(GRAY) "     - Removing $(NAME), $(MLX) And $(LIBNAME)..." $(NONE)
	@$(MAKE) -C ../libft fclean
	@rm -rf $(NAME)  $(NAMEBONUS) $(LIBNAME) $(MLX)

re: fclean all

.PHONY: all bonus clean fclean re