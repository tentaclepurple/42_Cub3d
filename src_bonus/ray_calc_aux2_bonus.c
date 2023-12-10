/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_calc_aux2_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imontero <imontero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 20:58:43 by imontero          #+#    #+#             */
/*   Updated: 2023/12/10 21:48:30 by imontero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

void	ft_calc_ray_aux(t_ray *ray)
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
}

void	ft_get_draw_info_aux(t_draw *draw, t_ray *ray)
{
	draw->wallx -= floor((draw->wallx));
	draw->texx = (int)(draw->wallx * (double)TEXWIDTH);
	if (ray->side == 0 && ray->raydirx > 0)
		draw->texx = TEXWIDTH - draw->texx - 1;
	if (ray->side == 1 && ray->raydiry < 0)
		draw->texx = TEXWIDTH - draw->texx - 1;
}

void	ft_update_img_aux(t_data *dt)
{
	ft_collisions(dt);
	mlx_put_image_to_window(dt->mlx, dt->mlx_w, dt->img_pp.img, 0, 0);
	ft_minimap_bgr(dt);
	if (dt->sprite.perpdist != 0)
		ft_put_sprite(dt);
	mlx_destroy_image(dt->mlx, dt->img_pp.img);
}
