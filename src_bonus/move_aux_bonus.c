/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_aux_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josu <josu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 17:57:33 by imontero          #+#    #+#             */
/*   Updated: 2023/12/09 12:51:53 by josu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cube_bonus.h"

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

void	ft_change_door(t_data *dt)
{
	int	x;
	int	y;

	x = (int)dt->pos_dir.posx;
	y = (int)dt->pos_dir.posy;
	if (fabs((double)dt->info.imap[x + 1][y]) == 2)
		dt->info.imap[x + 1][y] *= (-1);
	if (fabs((double)dt->info.imap[x - 1][y]) == 2)
		dt->info.imap[x - 1][y] *= (-1);
	if (fabs((double)dt->info.imap[x][y + 1]) == 2)
		dt->info.imap[x][y + 1] *= (-1);
	if (fabs((double)dt->info.imap[x][y - 1]) == 2)
		dt->info.imap[x][y - 1] *= (-1);
	dt->move.spacebar = 0;
}