/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_flat.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imontero <imontero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 15:58:43 by codespace         #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/12/01 20:46:37 by imontero         ###   ########.fr       */
=======
/*   Updated: 2023/12/02 17:56:10 by jzubizar         ###   ########.fr       */
>>>>>>> decddd0613eabcf19a113d0a6ac651c79da7aef5
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cube.h"

int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};


int	ft_press_key(int key, void *param)
{
	t_data	*dt;
	
	dt = (t_data *)param;
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
		ft_close(0, NULL);
	return (0);
}

<<<<<<< HEAD
void	init_game(t_cube info)
=======
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

int	main(void)
>>>>>>> decddd0613eabcf19a113d0a6ac651c79da7aef5
{
	t_data	dt;

	dt.info = info;
	dt.mlx = mlx_init();
	dt.w = screenWidth;
	dt.h = screenHeight;
<<<<<<< HEAD
	dt.pos_dir.posX = 3;
	dt.pos_dir.posY = 10;  //x and y start position
=======
	ft_init_move(&dt);
	dt.pos_dir.posX = 22;
	dt.pos_dir.posY = 16;  //x and y start position
>>>>>>> decddd0613eabcf19a113d0a6ac651c79da7aef5
	dt.pos_dir.dirX = -1;
	dt.pos_dir.dirY = 0; //initial direction vector
	dt.pos_dir.planeX = 0;
	dt.pos_dir.planeY = 0.66; //the 2d raycaster version of camera plane
	//double time = 0; //time of current frame
	//double oldTime = 0; //time of previous frame
<<<<<<< HEAD

	dt.text = ft_read_texture(dt.mlx);
=======
	ft_read_textures(&dt);
>>>>>>> decddd0613eabcf19a113d0a6ac651c79da7aef5
	dt.mlx_w = mlx_new_window(dt.mlx, screenWidth, screenHeight, "Raycaster");
	mlx_hook(dt.mlx_w, 2, (1L<<0), *ft_press_key, &dt);
	mlx_hook(dt.mlx_w, 3, (1L<<1), *ft_release_key, &dt);
	mlx_loop_hook(dt.mlx, &ft_update_img, &dt);
	mlx_hook(dt.mlx_w, 17, 0, ft_close, NULL);
	mlx_loop(dt.mlx);
}