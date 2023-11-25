NAME = cube3D
LIBNAME = 	libft.a
MLX = 		libmlx.a
#NAMEBONUS = minishell_bonus

SRC = 			src/main.c \
				src/custom_split.c \
				src/elems_aux.c \
				src/elems.c \
				src/fillmap.c \
				src/parse_aux.c \
				src/errors.c

#SRCBONUS = 	

OBJ = $(SRC:.c=.o)
#OBJBONUS = $(SRCBONUS:.c=.o)

FLAGS = -Wall -Wextra -Werror -g3 -Ilibmlx -fsanitize=address
MLXFLAGS = -framework OpenGL -framework AppKit
NONE='\033[0m'
GREEN='\033[32m'
GRAY='\033[2;37m'
CURSIVE='\033[3m'

all: $(NAME)

mlx:
	make -C libmlx
	cp libmlx/$(MLX) $(MLX)

$(NAME): $(OBJ) $(LIBNAME)
	@echo $(CURSIVE)$(GRAY) "     - Compiling $(NAME)..." $(NONE)
	@gcc $(FLAGS)   $(OBJ) $(LIBNAME) -o $(NAME)
	@echo $(GREEN)"- Compiled -"$(NONE)

bonus: $(OBJBONUS) $(LIBNAME)
	@echo $(CURSIVE)$(GRAY) "     - Compiling $(NAMEBONUS)..." $(NONE)
	@gcc $(FLAGS)   $(OBJBONUS) $(LIBNAME) -o $(NAMEBONUS)
	@echo $(GREEN)"- Compiled -"$(NONE)

$(LIBNAME):
	@echo $(CURSIVE)$(GRAY) "     - Compiling LIBFT $(LIBNAME)..." $(NONE)
	@$(MAKE) -C ./libft all
	@cp ./libft/libft.a $(LIBNAME)
	@echo $(GREEN)"- Compiled -"$(NONE)

%.o: %.c
	$(CC) -c $(FLAGS) $^ -o $@

clean:
	@echo $(CURSIVE)$(GRAY) "     - Removing object files..." $(NONE)
	@$(MAKE) -C ./libft clean
	@rm -rf $(OBJ) $(OBJBONUS)

fclean: clean
	@echo $(CURSIVE)$(GRAY) "     - Removing $(NAME) And $(LIBNAME)..." $(NONE)
	@$(MAKE) -C ./libft fclean
	@rm -rf $(NAME)  $(NAMEBONUS) $(LIBNAME)

re: fclean all

.PHONY: all bonus clean fclean re