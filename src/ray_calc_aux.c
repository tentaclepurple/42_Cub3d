/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_calc_aux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imontero <imontero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 17:35:26 by imontero          #+#    #+#             */
/*   Updated: 2023/12/07 17:36:02 by imontero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cube.h"

void	ft_init_side(t_data dt, t_ray *ray)
{
	if (ray->raydirx < 0)
	{
		ray->stepx = -1;
		ray->sidedistx = (dt.pos_dir.posx - ray->mapx) * ray->deltadistx;
	}
	else
	{
		ray->stepx = 1;
		ray->sidedistx = (ray->mapx + 1.0 - dt.pos_dir.posx) * ray->deltadistx;
	}
	if (ray->raydiry < 0)
	{
		ray->stepy = -1;
		ray->sidedisty = (dt.pos_dir.posy - ray->mapy) * ray->deltadisty;
	}
	else
	{
		ray->stepy = 1;
		ray->sidedisty = (ray->mapy + 1.0 - dt.pos_dir.posy) * ray->deltadisty;
	}
}

t_ray	ft_init_ray(t_data dt, int x)
{
	t_ray	ray;

	ray.hit = 0;
	ray.camerax = 2 * x / (double)dt.w - 1;
	ray.raydirx = dt.pos_dir.dirx + dt.pos_dir.planex * ray.camerax;
	ray.raydiry = dt.pos_dir.diry + dt.pos_dir.planey * ray.camerax;
	ray.mapx = (int)dt.pos_dir.posx;
	ray.mapy = (int)dt.pos_dir.posy;
	if (ray.raydirx == 0)
		ray.deltadistx = 1e30;
	else
		ray.deltadistx = fabs(1 / ray.raydirx);
	if (ray.raydiry == 0)
		ray.deltadisty = 1e30;
	else
		ray.deltadisty = fabs(1 / ray.raydiry);
	ft_init_side(dt, &ray);
	return (ray);
}

void	ft_calc_ray(t_ray *ray, int **map)
{
	while (ray->hit == 0)
	{
		if (ray->sidedistx < ray->sidedisty)
		{
			ray->sidedistx += ray->deltadistx;
			ray->mapx += ray->stepx;
			ray->side = 0;
		}
		else
		{
			ray->sidedisty += ray->deltadisty;
			ray->mapy += ray->stepy;
			ray->side = 1;
		}
		if (map[ray->mapx][ray->mapy] > 0)
			ray->hit = 1;
	}
	if (ray->side == 0)
		ray->perpwalldist = (ray->sidedistx - ray->deltadistx);
	else
		ray->perpwalldist = (ray->sidedisty - ray->deltadisty);
}

void	ft_get_draw_info(t_data dt, t_ray ray, t_draw *draw)
{
	draw->lineheight = (int)(dt.h / ray.perpwalldist);
	draw->drawstart = -draw->lineheight / 2 + dt.h / 2;
	if (draw->drawstart < 0)
		draw->drawstart = 0;
	draw->drawend = draw->lineheight / 2 + dt.h / 2;
	if (draw->drawend >= dt.h)
		draw->drawend = dt.h - 1;
	if (ray.side == 0 && ray.raydirx > 0)
		draw->texnum = 1;
	else if (ray.side == 0 && ray.raydirx < 0)
		draw->texnum = 0;
	else if (ray.side == 1 && ray.raydiry > 0)
		draw->texnum = 2;
	else if (ray.side == 1 && ray.raydiry < 0)
		draw->texnum = 3;
	if (ray.side == 0)
		draw->wallx = dt.pos_dir.posy + ray.perpwalldist * ray.raydiry;
	else
		draw->wallx = dt.pos_dir.posx + ray.perpwalldist * ray.raydirx;
	draw->wallx -= floor((draw->wallx));
	draw->texx = (int)(draw->wallx * (double)TEXWIDTH);
	if (ray.side == 0 && ray.raydirx > 0)
		draw->texx = TEXWIDTH - draw->texx - 1;
	if (ray.side == 1 && ray.raydiry < 0)
		draw->texx = TEXWIDTH - draw->texx - 1;
}

int	ft_do_move(t_data *dt)
{
	double	movespeed;
	double	rotspeed;

	movespeed = MOV_SPEED;
	rotspeed = ROT_SPEED;
	if (dt->move.rright)
		ft_rotate_right(dt, rotspeed);
	if (dt->move.rleft)
		ft_rotate_left(dt, rotspeed);
	if (dt->move.mback)
		ft_move_backward(dt, movespeed);
	if (dt->move.mfor)
		ft_move_forward(dt, movespeed);
	if (dt->move.mright)
		ft_move_right(dt, movespeed);
	if (dt->move.mleft)
		ft_move_left(dt, movespeed);
	return (0);
}
