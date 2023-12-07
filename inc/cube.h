/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imontero <imontero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 18:10:37 by imontero          #+#    #+#             */
/*   Updated: 2023/12/07 19:35:57 by imontero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>

# include "../libraries/libft/libft.h"
# include "../libraries/minilib/minilibx_opengl_20191021/mlx.h"

# define SCREENWIDTH 640
# define SCREENHEIGHT 640
# define MAPWIDTH 24
# define MAPHEIGHT 24
# define TEXWIDTH 128
# define TEXHEIGHT 128

# define MOV_SPEED 0.05
# define ROT_SPEED 0.03

//LINUX
/*#define UPKEY 65362
#define DOWNKEY 65364
#define RIGHTKEY 65363
#define LEFTKEY 65361*/
//MAC
# define UPKEY 126
# define DOWNKEY 125
# define RIGHTKEY 124
# define LEFTKEY 123

typedef struct s_pos_dir
{
	double	posx;
	double	posy;
	double	dirx;
	double	diry;
	double	planex;
	double	planey;
}			t_pos_dir;

typedef struct s_ray
{
	double	camerax;
	double	raydirx;
	double	raydiry;
	int		mapx;
	int		mapy;
	double	sidedistx;
	double	sidedisty;
	double	deltadistx;
	double	deltadisty;
	int		stepx;
	int		stepy;
	double	perpwalldist;
	int		hit;
	int		side;
}			t_ray;

typedef struct s_cube
{
	char		**map;
	int			**imap;
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	int			map_size[2];
	int			pl_pos[2];
	int			pl_dir[2];
	int			f;
	int			c;
	int			start_map;
}				t_cube;

typedef struct s_move
{
	int	mfor;
	int	mback;
	int	mright;
	int	mleft;
	int	rright;
	int	rleft;
}	t_move;

typedef struct s_img
{
	void	*img;
	int		*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		x;
	int		y;
}			t_img;

typedef struct s_data
{
	void		*mlx;
	void		*mlx_w;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	t_pos_dir	pos_dir;
	int			w;
	int			h;
	int			**textures;
	t_cube		info;
	t_img		img_pp;
	t_img		text[4];
	t_move		move;
}				t_data;

typedef struct s_draw
{
	int		drawstart;
	int		drawend;
	int		texnum;
	int		texx;
	double	wallx;
	int		lineheight;
}			t_draw;

typedef struct s_parse
{
	int	i;
	int	lastelem;
	int	firstmap;
	int	counttx;
	int	countfc;
}		t_parse;

void	ft_print_map(char **map);

/*
	parse
*/
char	*ft_get_cub(t_cube *cub, int fd);
void	ft_checks(t_cube *cub, int fd);
void	ft_fill_map(t_cube *cub, char **premap);
void	ft_check_map_perimeter(t_cube *cub);
void	ft_search_elems_aux(t_cube *cub, t_parse *p, char **spl);
int		ft_save_color(char **spl, t_parse *p, t_cube *cub, int count);
void	ft_save_path(t_cube *cub, char *path, t_parse *p, char **elem);
void	ft_get_elements(t_cube *cub, char *str);
void	ft_search_elems(t_cube *cub, char **spl, t_parse *p);
void	ft_get_vector(t_cube *cub, char c);
void	ft_get_pos(t_cube *cub);
void	ft_get_map_size(t_cube *cub);
void	ft_map_char_2_int(t_cube *cub);
void	ft_map_values(t_cube *cub);
void	ft_check_repeat_elems(t_cube *cub);

/* 
	utils
*/
int		transf_rgb(int r, int g, int b);
int		my_atoi(const char *str);
int		ft_longest_str(char **str);
size_t	ft_matlen(char **str);
char	**custom_split(char const *s);
void	init_cub(t_cube *cub);

/* 
	errors
*/
void	free_exit(char *str, t_cube *cub);
void	free_exit_mat(char *str, t_cube *cub);

//ray_calc
int		ft_update_img(void *param);
int		ft_do_move(t_data *dt);
void	ft_get_draw_info(t_data dt, t_ray ray, t_draw *draw);
void	ft_calc_ray(t_ray *ray, int **map);
t_ray	ft_init_ray(t_data dt, int x);
void	ft_init_side(t_data dt, t_ray *ray);

//pixel_put
int		ft_close(int key, void *param);
void	my_mlx_line_put(t_data *data, int x, t_draw draw);

//texture
int		**ft_gen_texture(void);
void	ft_free_textures(int **textures);
t_img	ft_read_texture(void *mlx, char *name);
void	ft_read_textures(t_data *dt);

//game
void	init_game(t_cube info);
//void	init_game(t_cube *info);
void	ft_rotate_right(t_data *dt, double rotspeed);
void	ft_rotate_left(t_data *dt, double rotspeed);
void	ft_move_forward(t_data *dt, double movespeed);
void	ft_move_backward(t_data *dt, double movespeed);
void	ft_move_left(t_data *dt, double movespeed);
void	ft_move_right(t_data *dt, double movespeed);

#endif
