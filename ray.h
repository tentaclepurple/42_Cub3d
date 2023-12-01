/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imontero <imontero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 12:54:08 by jzubizar          #+#    #+#             */
/*   Updated: 2023/12/01 18:48:42 by imontero         ###   ########.fr       */
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

typedef struct	s_data {
	void	*mlx;
	void	*mlx_w;
	/*void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;*/
	t_img		img_pp;
	t_pos_dir	pos_dir;
	int			w;
	int			h;
	t_img		text;
	t_cube		info;
}				t_data;


typedef struct	s_draw {
	int		drawStart;
	int		drawEnd;
	int		texNum;
	int		texX;
	double	wallX;
}				t_draw;
//ray_calc
void	ft_update_img(t_data *dt);

//pixel_put
int	ft_close(int key, void *param);
void	my_mlx_line_put(t_data *data, int x, t_draw draw, int side, int lineHeight);

//texture
int	**ft_gen_texture(void);
void	ft_free_textures(int **textures);
t_img ft_read_texture(void *mlx);

#define screenWidth 640
#define screenHeight 640
#define mapWidth 24
#define mapHeight 24
#define texWidth 32
#define texHeight 32
//LINUX
/* #define UPKEY 65362
#define DOWNKEY 65364
#define RIGTHKEY 65363
#define LEFTKEY 65361 */
//MAC
#define UPKEY 126
#define DOWNKEY 125
#define RIGTHKEY 124
#define LEFTKEY 123




#endif