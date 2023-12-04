/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzubizar <jzubizar@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 16:12:00 by jzubizar          #+#    #+#             */
/*   Updated: 2023/12/02 17:15:20 by jzubizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"

void	ft_rotate_right(t_data *dt, double rotSpeed)
{
	double tempDirX;
	double tempPlaneX;

	tempDirX = dt->pos_dir.dirX;
	tempPlaneX = dt->pos_dir.planeX;
	dt->pos_dir.dirX = dt->pos_dir.dirX * cos(-rotSpeed) - dt->pos_dir.dirY * sin(-rotSpeed);
	dt->pos_dir.dirY = tempDirX * sin(-rotSpeed) + dt->pos_dir.dirY * cos(-rotSpeed);
	dt->pos_dir.planeX = dt->pos_dir.planeX * cos(-rotSpeed) - dt->pos_dir.planeY * sin(-rotSpeed);
	dt->pos_dir.planeY = tempPlaneX * sin(-rotSpeed) + dt->pos_dir.planeY * cos(-rotSpeed);
}

void	ft_rotate_left(t_data *dt, double rotSpeed)
{
	double tempDirX;
	double tempPlaneX;

	tempDirX = dt->pos_dir.dirX;
	tempPlaneX = dt->pos_dir.planeX;
	dt->pos_dir.dirX = dt->pos_dir.dirX * cos(rotSpeed) - dt->pos_dir.dirY * sin(rotSpeed);
	dt->pos_dir.dirY = tempDirX * sin(rotSpeed) + dt->pos_dir.dirY * cos(rotSpeed);
	dt->pos_dir.planeX = dt->pos_dir.planeX * cos(rotSpeed) - dt->pos_dir.planeY * sin(rotSpeed);
	dt->pos_dir.planeY = tempPlaneX * sin(rotSpeed) + dt->pos_dir.planeY * cos(rotSpeed);
}

void	ft_move_forward(t_data *dt, double moveSpeed)
{
	if (worldMap[(int)(dt->pos_dir.posX + dt->pos_dir.dirX * moveSpeed)][(int)dt->pos_dir.posY] == 0)
		dt->pos_dir.posX += dt->pos_dir.dirX * moveSpeed;
	if (worldMap[(int)dt->pos_dir.posX][(int)(dt->pos_dir.posY + dt->pos_dir.dirY * moveSpeed)] == 0)
		dt->pos_dir.posY += dt->pos_dir.dirY * moveSpeed;
}

void	ft_move_backward(t_data *dt, double moveSpeed)
{
	if (worldMap[(int)(dt->pos_dir.posX - dt->pos_dir.dirX * moveSpeed)][(int)dt->pos_dir.posY] == 0)
		dt->pos_dir.posX -= dt->pos_dir.dirX * moveSpeed;
	if (worldMap[(int)dt->pos_dir.posX][(int)(dt->pos_dir.posY - dt->pos_dir.dirY * moveSpeed)] == 0)
		dt->pos_dir.posY -= dt->pos_dir.dirY * moveSpeed;
}

void	ft_move_left(t_data *dt, double moveSpeed)
{
	if (worldMap[(int)(dt->pos_dir.posX - dt->pos_dir.dirY * moveSpeed)][(int)dt->pos_dir.posY] == 0)
		dt->pos_dir.posX -= dt->pos_dir.dirY * moveSpeed;
	if (worldMap[(int)dt->pos_dir.posX][(int)(dt->pos_dir.posY + dt->pos_dir.dirX * moveSpeed)] == 0)
		dt->pos_dir.posY += dt->pos_dir.dirX * moveSpeed;
}

void	ft_move_right(t_data *dt, double moveSpeed)
{
	if (worldMap[(int)(dt->pos_dir.posX + dt->pos_dir.dirY * moveSpeed)][(int)dt->pos_dir.posY] == 0)
		dt->pos_dir.posX += dt->pos_dir.dirY * moveSpeed;
	if (worldMap[(int)dt->pos_dir.posX][(int)(dt->pos_dir.posY - dt->pos_dir.dirX * moveSpeed)] == 0)
		dt->pos_dir.posY -= dt->pos_dir.dirX * moveSpeed;
}