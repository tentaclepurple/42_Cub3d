/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_calc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imontero <imontero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 12:53:30 by jzubizar          #+#    #+#             */
/*   Updated: 2023/12/04 17:44:21 by imontero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cube.h"

void	ft_init_side(t_data dt, t_ray *ray)
{
	if(ray->rayDirX < 0)
	{
		ray->stepX = -1;
		ray->sideDistX = (dt.pos_dir.posX -ray->mapX) * ray->deltaDistX;
	}
	else
	{
		ray->stepX = 1;
		ray->sideDistX = (ray->mapX + 1.0 - dt.pos_dir.posX) * ray->deltaDistX;
	}
	if(ray->rayDirY < 0)
	{
		ray->stepY = -1;
		ray->sideDistY = (dt.pos_dir.posY - ray->mapY) * ray->deltaDistY;
	}
	else
	{
		ray->stepY = 1;
		ray->sideDistY = (ray->mapY + 1.0 - dt.pos_dir.posY) * ray->deltaDistY;
	}
}

t_ray ft_init_ray(t_data dt, int x)
{
	t_ray	ray;

	ray.hit = 0;
	ray.cameraX = 2 * x / (double)dt.w - 1; //x-coordinate in camera space
	ray.rayDirX = dt.pos_dir.dirX + dt.pos_dir.planeX * ray.cameraX;
	ray.rayDirY = dt.pos_dir.dirY + dt.pos_dir.planeY * ray.cameraX;
	ray.mapX = (int)dt.pos_dir.posX;
	ray.mapY = (int)dt.pos_dir.posY;
	if (ray.rayDirX == 0)
		ray.deltaDistX = 1e30;
	else
		ray.deltaDistX = fabs(1 / ray.rayDirX);
	if (ray.rayDirY == 0)
		ray.deltaDistY = 1e30;
	else
		ray.deltaDistY = fabs(1 / ray.rayDirY);
	ft_init_side(dt, &ray);
	return (ray);
}

void	cd ft_calc_ray(t_ray *ray, int **map)
{
	while(ray->hit == 0)
	{
		if(ray->sideDistX < ray->sideDistY)
		{
			ray->sideDistX += ray->deltaDistX;
			ray->mapX += ray->stepX;
			ray->side = 0;
		}
		else
		{
			ray->sideDistY += ray->deltaDistY;
			ray->mapY += ray->stepY;
			ray->side = 1;
		}
		if(map[ray->mapX][ray->mapY] > 0)
			ray->hit = 1;
	}
	if(ray->side == 0)
		ray->perpWallDist = (ray->sideDistX - ray->deltaDistX);
	else
		ray->perpWallDist = (ray->sideDistY - ray->deltaDistY);
}

void	ft_get_draw_info(t_data dt, t_ray ray, t_draw	*draw)
{
	//calculate the length of the column line to put in the image column
	draw->lineHeight = (int)(dt.h / ray.perpWallDist);
	//With a screen oh height h, the starting pixel to represent the wall
	draw->drawStart = -draw->lineHeight / 2 + dt.h / 2;
	if(draw->drawStart < 0)
		draw->drawStart = 0;
	//With a screen oh height h, the final pixel to represent the wall
	draw->drawEnd = draw->lineHeight / 2 + dt.h / 2;
	if(draw->drawEnd >= dt.h)
		draw->drawEnd = dt.h - 1;
	//texturing chose deppending on direction of side hit
	if(ray.side == 0 && ray.rayDirX > 0)
		draw->texNum = 1;
	else if(ray.side == 0 && ray.rayDirX < 0)
		draw->texNum = 0;
	else if(ray.side == 1 && ray.rayDirY > 0)
		draw->texNum = 2;
	else if(ray.side == 1 && ray.rayDirY < 0)
		draw->texNum = 3;
	//Calculate distance from wall start where ray hits (prop to texture width)
	if (ray.side == 0)
		draw->wallX = dt.pos_dir.posY + ray.perpWallDist * ray.rayDirY;
	else
		draw->wallX = dt.pos_dir.posX + ray.perpWallDist * ray.rayDirX;
	//Get decimals of the value -> The percentage of the texture witdh we need to represent
	draw->wallX -= floor((draw->wallX));
	//Gety x coordinate on the texture
	draw->texX = (int)(draw->wallX * (double)texWidth);
	if(ray.side == 0 && ray.rayDirX > 0)
		draw->texX = texWidth - draw->texX - 1;
	if(ray.side == 1 && ray.rayDirY < 0)
		draw->texX = texWidth - draw->texX - 1;
}

int	ft_do_move(t_data *dt)
{
	double	moveSpeed = 0.05;
	double	rotSpeed = 0.05;
	
	if (dt->move.rright)
		ft_rotate_right(dt, rotSpeed);
	if (dt->move.rleft)
		ft_rotate_left(dt, rotSpeed);
	if (dt->move.mback)
		ft_move_backward(dt, moveSpeed);
	if (dt->move.mfor)
		ft_move_forward(dt, moveSpeed);
	if (dt->move.mright)
		ft_move_right(dt, moveSpeed);
	if (dt->move.mleft)
		ft_move_left(dt, moveSpeed);
	return (0);
}

int	ft_update_img(void *param)
{
	t_ray	ray;
	t_draw	draw;
	int		x;
	t_data	*dt;
	
	dt = (t_data *)param;
	ft_do_move(dt);
	//Start a new MAIN image
	dt->img = mlx_new_image(dt->mlx, screenWidth, screenHeight);
	dt->addr = mlx_get_data_addr(dt->img, &dt->bits_per_pixel, &dt->line_length,
								&dt->endian);
	/*Starts the loop of:
		1- Send and calculate distance of a ray
		2- Calculate in the texture which pixels to represent
		3- Include pixel column into the main image
		4- Loop
	*/	
	x = 0;
	while (x < dt->w)
	{
		//Put ray values to initial ones
		ray = ft_init_ray(*dt, x);
		//Calculate Ray distances
		ft_calc_ray(&ray);
		//Calculate drawing parameters
		ft_get_draw_info(*dt, ray, &draw);
		//Include the pixel column into the main image
		my_mlx_line_put(dt, x, draw);
		x++;
	}
	mlx_put_image_to_window(dt->mlx, dt->mlx_w, dt->img, 0, 0);
	mlx_destroy_image(dt->mlx,dt->img);
	return (0);
}
