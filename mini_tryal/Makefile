NAME = raycaster
#LIBNAME = libft.a
MINILIB = libmlx.a
SRC = pixel_put.c ray_calc.c raycaster_flat.c texture.c
OBJ = $(SRC:.c=.o)

#FLAGS = -Wall -Wextra -Werror -g3
LINKS = -Lmlx -lmlx -L/usr/lib -Imlx -lXext -lX11 -lm -lz
#LINKS = -lmlx -framework OpenGL -framework AppKit
NONE='\033[0m'
GREEN='\033[32m'
GRAY='\033[2;37m'
CURSIVE='\033[3m'

all: $(NAME)

$(NAME): $(OBJ) $(LIBNAME) $(MINILIB)
	@echo $(CURSIVE)$(GRAY) "     - Compiling $(NAME)..." $(NONE)
	@gcc $(FLAGS) $(OBJ) $(LINKS) -o $(NAME) $(LIBNAME)
	@echo $(GREEN)"- Compiled -"$(NONE)
#@rm $(OBJ)
#@echo $(CURSIVE)$(GRAY) "     Deleted object files" $(NONE)

$(LIBNAME):
	@echo $(CURSIVE)$(GRAY) "     - Compiling LIBFT $(LIBNAME)..." $(NONE)
	@$(MAKE) -C ./libft all
	@cp ./libft/libft.a $(LIBNAME)
	@echo $(GREEN)"- Compiled -"$(NONE)

$(MINILIB):
	@echo $(CURSIVE)$(GRAY) "     - Compiling LIBFT $(MINILIB)..." $(NONE)
	@$(MAKE) -C ./minilibx-linux all
	@cp ./minilibx-linux/libmlx.a $(MINILIB)
	@echo $(GREEN)"- Compiled -"$(NONE)

$(OBJ): $(SRC)
	@echo $(CURSIVE)$(GRAY) "     - Making object files..." $(NONE)
	@gcc $(FLAGS) -c $(SRC)

clean:
	@echo $(CURSIVE)$(GRAY) "     - Removing object files..." $(NONE)
	@rm -rf $(OBJ)

fclean: clean
	@echo $(CURSIVE)$(GRAY) "     - Removing $(NAME) And $(LIBNAME)..." $(NONE)
	@rm -rf $(NAME) $(LIBNAME)

re: fclean all