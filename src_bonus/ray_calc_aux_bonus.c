/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_calc_aux_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imontero <imontero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 17:35:26 by imontero          #+#    #+#             */
/*   Updated: 2023/12/11 10:46:15 by imontero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cube_bonus.h"

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
	ray.door = 0;
	ft_init_side(dt, &ray);
	return (ray);
}

void	ft_calc_ray(t_ray *ray, int **map, t_data *dt, int x)
{
	while (ray->hit == 0)
	{
		ft_calc_ray_aux(ray);
		if (map[ray->mapx][ray->mapy] > 0 && map[ray->mapx][ray->mapy] < 3)
			ray->hit = 1;
		if (map[ray->mapx][ray->mapy] == 2)
			ray->door = 1;
		if (map[ray->mapx][ray->mapy] == -1 && dt->sprite.perpdist == 0)
		{
			if (ray->side == 0)
				dt->sprite.perpdist = (ray->sidedistx - ray->deltadistx);
			else
				dt->sprite.perpdist = (ray->sidedisty - ray->deltadisty);
			dt->sprite.lineheight = (int)(dt->h / dt->sprite.perpdist);
			dt->sprite.x = x;
		}
		if (map[ray->mapx][ray->mapy] == -1)
			dt->sprite.x_end = x;
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
	if (ray.door == 1)
		draw->texnum = 4;
	if (ray.side == 0)
		draw->wallx = dt.pos_dir.posy + ray.perpwalldist * ray.raydiry;
	else
		draw->wallx = dt.pos_dir.posx + ray.perpwalldist * ray.raydirx;
	ft_get_draw_info_aux(draw, &ray);
}

int	ft_do_move(t_data *dt)
{
	double	movespeed;
	double	rotspeed;
	int		x;
	int		y;

	movespeed = MOV_SPEED;
	rotspeed = ROT_SPEED;
	mlx_mouse_get_pos(dt->mlx_w, &x, &y);
	if (dt->move.rright || x > SCREENWIDTH / 2 + SCREENWIDTH * 0.2)
		ft_rotate_right(dt, rotspeed);
	if (dt->move.rleft || x < SCREENWIDTH / 2 - SCREENWIDTH * 0.2)
		ft_rotate_left(dt, rotspeed);
	if (dt->move.mback)
		ft_move_backward(dt, movespeed);
	if (dt->move.mfor)
		ft_move_forward(dt, movespeed);
	if (dt->move.mright)
		ft_move_right(dt, movespeed);
	if (dt->move.mleft)
		ft_move_left(dt, movespeed);
	if (dt->move.spacebar)
		ft_change_door(dt);
	return (0);
}
