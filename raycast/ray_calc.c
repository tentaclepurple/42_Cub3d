/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_calc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzubizar <jzubizar@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 12:53:30 by jzubizar          #+#    #+#             */
/*   Updated: 2023/11/24 12:59:59 by jzubizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"

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

void	ft_calc_ray(t_ray *ray)
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
		if(worldMap[ray->mapX][ray->mapY] > 0)
			ray->hit = 1;
		if(ray->side == 0)
			ray->perpWallDist = (ray->sideDistX - ray->deltaDistX);
		else
			ray->perpWallDist = (ray->sideDistY - ray->deltaDistY);
	}
}

void	ft_update_img(t_data *dt)
{
	dt->img = mlx_new_image(dt->mlx, screenHeight, screenHeight);
	dt->addr = mlx_get_data_addr(dt->img, &dt->bits_per_pixel, &dt->line_length,
								&dt->endian);
	for(int x = 0; x < dt->w; x++)
	{
		t_ray	ray;
		int		lineHeight;
		int		drawStart;
		int		drawEnd;
		int		color;
		
		ray = ft_init_ray(*dt, x);
		ft_calc_ray(&ray);
		lineHeight = (int)(dt->h / ray.perpWallDist);
		drawStart = -lineHeight / 2 + dt->h / 2;
		if(drawStart < 0)
			drawStart = 0;
		drawEnd = lineHeight / 2 + dt->h / 2;
		if(drawEnd >= dt->h)
			drawEnd = dt->h - 1;
		color = 0x00FF0000;
		if(ray.side == 1)
			color = color / 2;
		my_mlx_line_put(dt, x, drawStart, drawEnd, color);
	}
	mlx_put_image_to_window(dt->mlx, dt->mlx_w, dt->img, 0, 0);
	mlx_destroy_image(dt->mlx,dt->img);
}