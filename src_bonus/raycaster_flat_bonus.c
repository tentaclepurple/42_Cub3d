/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_flat_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imontero <imontero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 15:58:43 by codespace         #+#    #+#             */
/*   Updated: 2023/12/08 12:53:27 by imontero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cube_bonus.h"

int	ft_press_key(int key, void *param)
{
	t_data	*dt;

	dt = (t_data *)param;
	printf("texture: %s\n", dt->info.no);
	if (key == RIGHTKEY)
		dt->move.rright = 1;
	else if (key == LEFTKEY)
		dt->move.rleft = 1;
	else if ((key == DOWNKEY || key == 1))
		dt->move.mback = 1;
	else if ((key == UPKEY || key == 13))
		dt->move.mfor = 1;
	else if (key == 2)
		dt->move.mright = 1;
	else if (key == 0)
		dt->move.mleft = 1;
	else if (key == 53)
		ft_close(param);
		//ft_close(0, NULL);
	return (0);
}

int	ft_release_key(int key, void *param)
{
	t_data	*dt;

	dt = (t_data *)param;
	if (key == RIGHTKEY)
		dt->move.rright = 0;
	else if (key == LEFTKEY)
		dt->move.rleft = 0;
	else if ((key == DOWNKEY || key == 1))
		dt->move.mback = 0;
	else if ((key == UPKEY || key == 13))
		dt->move.mfor = 0;
	else if (key == 2)
		dt->move.mright = 0;
	else if (key == 0)
		dt->move.mleft = 0;
	return (0);
}

void	ft_init_move(t_data *dt)
{
	dt->move.mfor = 0;
	dt->move.mback = 0;
	dt->move.mright = 0;
	dt->move.mleft = 0;
	dt->move.rright = 0;
	dt->move.rleft = 0;
}




void	init_game(t_cube info)
{
	t_data	dt;

	dt.info = info;
	dt.mlx = mlx_init();
	dt.w = SCREENWIDTH;
	dt.h = SCREENHEIGHT;
	ft_init_move(&dt);
	dt.pos_dir.posx = (double)info.pl_pos[1] + 0.5;
	dt.pos_dir.posy = (double)info.pl_pos[0] + 0.5;
	dt.pos_dir.dirx = (double)info.pl_dir[1];
	dt.pos_dir.diry = (double)info.pl_dir[0];
	dt.pos_dir.planex = dt.pos_dir.diry * (0.66);
	dt.pos_dir.planey = dt.pos_dir.dirx * (-0.66);
	ft_read_textures(&dt);
	dt.mlx_w = mlx_new_window(dt.mlx, SCREENWIDTH, SCREENHEIGHT, "Raycaster");
	mlx_hook(dt.mlx_w, 2, (1L << 0), *ft_press_key, &dt);
	mlx_hook(dt.mlx_w, 3, (1L << 1), *ft_release_key, &dt);
	//mlx_mouse_hook(dt.mlx_w, &ft_mouse_move, &dt);
	mlx_loop_hook(dt.mlx, &ft_update_img, &dt);
	mlx_hook(dt.mlx_w, 17, 0, ft_close, &info);
	mlx_loop(dt.mlx);
}

/*void	init_game(t_cube *info)
{
	t_data	dt;

	dt.info = info;
	dt.mlx = mlx_init();
	dt.w = SCREENWIDTH;
	dt.h = SCREENHEIGHT;
	ft_init_move(&dt);
	dt.pos_dir.posx = (double)info->pl_pos[1] + 0.5;
	dt.pos_dir.posy = (double)info->pl_pos[0] + 0.5;
	dt.pos_dir.dirx = (double)info->pl_dir[1];
	dt.pos_dir.diry = (double)info->pl_dir[0];
	dt.pos_dir.planex = dt.pos_dir.diry * (0.66);
	dt.pos_dir.planey = dt.pos_dir.dirx * (-0.66);
	ft_read_textures(&dt);
	dt.mlx_w = mlx_new_window(dt.mlx, SCREENWIDTH, SCREENHEIGHT, "Raycaster");
	mlx_hook(dt.mlx_w, 2, (1L << 0), *ft_press_key, &dt);
	mlx_hook(dt.mlx_w, 3, (1L << 1), *ft_release_key, &dt);
	mlx_loop_hook(dt.mlx, &ft_update_img, &dt);
	mlx_hook(dt.mlx_w, 17, 0, ft_close, info);
	mlx_loop(dt.mlx);
}*/
