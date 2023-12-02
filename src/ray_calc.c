/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_calc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imontero <imontero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 12:53:30 by jzubizar          #+#    #+#             */
/*   Updated: 2023/12/02 13:51:15 by imontero         ###   ########.fr       */
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
		if(ray->side == 0)
			ray->perpWallDist = (ray->sideDistX - ray->deltaDistX);
		else
			ray->perpWallDist = (ray->sideDistY - ray->deltaDistY);
	}
}

void	ft_update_img(t_data *dt)
{
	dt->img_pp.img = mlx_new_image(dt->mlx, screenWidth, screenHeight);
	dt->img_pp.addr = mlx_get_data_addr(dt->img_pp.img, &dt->img_pp.bits_per_pixel, &dt->img_pp.line_length,
								&dt->img_pp.endian);
	

	for(int x = 0; x < dt->w; x++)
	{
		t_ray	ray;
		int		lineHeight;
		t_draw	draw;
		
		ray = ft_init_ray(*dt, x);
		ft_calc_ray(&ray, dt->info.imap);
		lineHeight = (int)(dt->h / ray.perpWallDist);
		draw.drawStart = -lineHeight / 2 + dt->h / 2;
		if(draw.drawStart < 0)
			draw.drawStart = 0;
		draw.drawEnd = lineHeight / 2 + dt->h / 2;
		if(draw.drawEnd >= dt->h)
			draw.drawEnd = dt->h - 1;
		//texturing calculations
		draw.texNum = dt->info.imap[ray.mapX][ray.mapY] - 1; //1 subtracted from it so that texture 0 can be used!
		//calculate value of wallX
		if (ray.side == 0)
			draw.wallX = dt->pos_dir.posY + ray.perpWallDist * ray.rayDirY;
		else
			draw.wallX = dt->pos_dir.posX + ray.perpWallDist * ray.rayDirX;
		draw.wallX -= floor((draw.wallX));
		//x coordinate on the texture
		draw.texX = (int)draw.wallX * (double)texWidth;
		if(ray.side == 0 && ray.rayDirX > 0)
			draw.texX = texWidth - draw.texX - 1;
		if(ray.side == 1 && ray.rayDirY < 0)
			draw.texX = texWidth - draw.texX - 1;
		my_mlx_line_put(dt, x, draw, ray.side, lineHeight);
	}
	mlx_put_image_to_window(dt->mlx, dt->mlx_w, dt->img_pp.img, 0, 0);
	mlx_destroy_image(dt->mlx,dt->img_pp.img);
}
