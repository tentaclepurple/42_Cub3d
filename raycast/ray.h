/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josu <josu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 12:54:08 by jzubizar          #+#    #+#             */
/*   Updated: 2023/11/24 14:22:43 by josu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

#include "../minilibx-linux/mlx.h"
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
}				t_data;
//ray_calc
void	ft_update_img(t_data *dt);

//pixel_put
int	ft_close(int key, void *param);
void	my_mlx_line_put(t_data *data, int x, int drawStart, int drawEnd, int color);

#define screenWidth 640
#define screenHeight 640
#define mapWidth 24
#define mapHeight 24

extern int worldMap[mapWidth][mapHeight];


#endif