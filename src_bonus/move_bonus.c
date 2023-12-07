/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imontero <imontero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 16:12:00 by jzubizar          #+#    #+#             */
/*   Updated: 2023/12/07 19:43:06 by imontero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cube_bonus.h"

void	ft_move_forward(t_data *dt, double movespeed)
{
	if (dt->info.imap[(int)(dt->pos_dir.posx + dt->pos_dir.dirx
			* movespeed)][(int)dt->pos_dir.posy] == 0)
		dt->pos_dir.posx += dt->pos_dir.dirx * movespeed;
	if (dt->info.imap[(int)dt->pos_dir.posx][(int)(dt->pos_dir.posy
		+ dt->pos_dir.diry * movespeed)] == 0)
		dt->pos_dir.posy += dt->pos_dir.diry * movespeed;
}

void	ft_move_backward(t_data *dt, double movespeed)
{
	if (dt->info.imap[(int)(dt->pos_dir.posx - dt->pos_dir.dirx
			* movespeed)][(int)dt->pos_dir.posy] == 0)
		dt->pos_dir.posx -= dt->pos_dir.dirx * movespeed;
	if (dt->info.imap[(int)dt->pos_dir.posx][(int)(dt->pos_dir.posy
		- dt->pos_dir.diry * movespeed)] == 0)
		dt->pos_dir.posy -= dt->pos_dir.diry * movespeed;
}

void	ft_move_left(t_data *dt, double movespeed)
{
	if (dt->info.imap[(int)(dt->pos_dir.posx - dt->pos_dir.diry
			* movespeed)][(int)dt->pos_dir.posy] == 0)
		dt->pos_dir.posx -= dt->pos_dir.diry * movespeed;
	if (dt->info.imap[(int)dt->pos_dir.posx][(int)(dt->pos_dir.posy
		+ dt->pos_dir.dirx * movespeed)] == 0)
		dt->pos_dir.posy += dt->pos_dir.dirx * movespeed;
}

void	ft_move_right(t_data *dt, double movespeed)
{
	if (dt->info.imap[(int)(dt->pos_dir.posx + dt->pos_dir.diry
			* movespeed)][(int)dt->pos_dir.posy] == 0)
		dt->pos_dir.posx += dt->pos_dir.diry * movespeed;
	if (dt->info.imap[(int)dt->pos_dir.posx][(int)(dt->pos_dir.posy
		- dt->pos_dir.dirx * movespeed)] == 0)
		dt->pos_dir.posy -= dt->pos_dir.dirx * movespeed;
}
