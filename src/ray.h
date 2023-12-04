/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzubizar <jzubizar@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 12:54:08 by jzubizar          #+#    #+#             */
/*   Updated: 2023/12/02 16:32:00 by jzubizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

#include "../libraries/minilib/minilibx_opengl_20191021/mlx.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct	s_pos_dir {
	double	posX;
	double	posY;
	double	dirX;
	double	dirY;
	double	planeX;
	double	planeY;
}				t_pos_dir;

typedef struct	s_ray {
	double	cameraX;
	double	rayDirX;
	double	rayDirY;
	int		mapX;
	int		mapY;
	double	sideDistX;
	double	sideDistY;
	double	deltaDistX;
	double	deltaDistY;
	int		stepX;
	int		stepY;
	double	perpWallDist;
	int		hit;
	int		side;
}				t_ray;

typedef struct s_img
{
	void	*img;
	int		*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		x;
	int		y;
} t_img;

typedef struct s_move
{
	int	mfor;
	int	mback;
	int	mright;
	int	mleft;
	int	rright;
	int	rleft;
}	t_move;

typedef struct	s_data {
	void	*mlx;
	void	*mlx_w;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	t_pos_dir	pos_dir;
	int		w;
	int		h;
	int	**textures;
	//CAMBIO
	t_img	text[4];
	t_move	move;
}				t_data;


typedef struct	s_draw {
	int		drawStart;
	int		drawEnd;
	int		texNum;
	int		texX;
	double	wallX;
	//CAMBIO
	int		lineHeight;
}				t_draw;
//ray_calc
//CAMBIO
int	ft_update_img(void *param);

//pixel_put
int	ft_close(int key, void *param);
//CAMBIO
void	my_mlx_line_put(t_data *data, int x, t_draw draw);

//texture
int		**ft_gen_texture(void);
void	ft_free_textures(int **textures);
//CAMBIO
void ft_read_textures(t_data *dt);

//NEW move
void	ft_rotate_right(t_data *dt, double rotSpeed);
void	ft_rotate_left(t_data *dt, double rotSpeed);
void	ft_move_forward(t_data *dt, double moveSpeed);
void	ft_move_backward(t_data *dt, double moveSpeed);
void	ft_move_right(t_data *dt, double moveSpeed);
void	ft_move_left(t_data *dt, double moveSpeed);


#define screenWidth 640
#define screenHeight 640
#define mapWidth 24
#define mapHeight 24
#define texWidth 128
#define texHeight 128
//LINUX
/* #define UPKEY 65362
#define DOWNKEY 65364
#define RIGTHKEY 65363
#define LEFTKEY 65361 */
//MAC
#define UPKEY 126
#define DOWNKEY 125
//CAMBIO
#define RIGHTKEY 124
#define LEFTKEY 123

extern int worldMap[mapWidth][mapHeight];


#endif