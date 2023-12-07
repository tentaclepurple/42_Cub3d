/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_aux.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imontero <imontero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 17:57:33 by imontero          #+#    #+#             */
/*   Updated: 2023/12/07 17:58:08 by imontero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cube.h"

void	ft_rotate_right(t_data *dt, double rotspeed)
{
	double	tempdirx;
	double	tempplanex;

	tempdirx = dt->pos_dir.dirx;
	tempplanex = dt->pos_dir.planex;
	dt->pos_dir.dirx = dt->pos_dir.dirx * cos(-rotspeed)
		- dt->pos_dir.diry * sin(-rotspeed);
	dt->pos_dir.diry = tempdirx * sin(-rotspeed)
		+ dt->pos_dir.diry * cos(-rotspeed);
	dt->pos_dir.planex = dt->pos_dir.planex * cos(-rotspeed)
		- dt->pos_dir.planey * sin(-rotspeed);
	dt->pos_dir.planey = tempplanex * sin(-rotspeed)
		+ dt->pos_dir.planey * cos(-rotspeed);
}

void	ft_rotate_left(t_data *dt, double rotspeed)
{
	double	tempdirx;
	double	tempplanex;

	tempdirx = dt->pos_dir.dirx;
	tempplanex = dt->pos_dir.planex;
	dt->pos_dir.dirx = dt->pos_dir.dirx * cos(rotspeed)
		- dt->pos_dir.diry * sin(rotspeed);
	dt->pos_dir.diry = tempdirx * sin(rotspeed)
		+ dt->pos_dir.diry * cos(rotspeed);
	dt->pos_dir.planex = dt->pos_dir.planex * cos(rotspeed)
		- dt->pos_dir.planey * sin(rotspeed);
	dt->pos_dir.planey = tempplanex * sin(rotspeed)
		+ dt->pos_dir.planey * cos(rotspeed);
}
