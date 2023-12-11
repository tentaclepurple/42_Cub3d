/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_calc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imontero <imontero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 12:53:30 by jzubizar          #+#    #+#             */
/*   Updated: 2023/12/11 09:33:10 by imontero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cube_bonus.h"

/* 
	print the minimap
*/
void	ft_minimap_bgr(t_data *dt)
{
	int	i;
	int	j;

	i = 0;
	while (i < dt->info.map_size[0])
	{
		j = 0;
		while (j < dt->info.map_size[1])
		{
			if (dt->info.imap[i][j] != 0 || dt->info.imap[i][j] == 2
				|| dt->info.imap[i][j] == 3)
				mlx_put_image_to_window(dt->mlx, dt->mlx_w, dt->pix, \
				j * RES, i * RES);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(dt->mlx, dt->mlx_w, dt->pix, \
				dt->pos_dir.posy * RES, dt->pos_dir.posx * RES);
}

void	sprite_line_put(t_data *data, int x, t_img img, int start)
{
	t_slp	slp;

	slp.step = 1.0 * TEXHEIGHT / data->sprite.lineheight;
	slp.texpos = 0;
	slp.y = 0;
	while (slp.y < data->sprite.lineheight)
	{
		slp.texy = (int)slp.texpos & (TEXHEIGHT - 1);
		slp.texpos += slp.step;
		slp.color = data->text[5].addr[TEXHEIGHT * slp.texy + (x + start)
			* TEXHEIGHT / data->sprite.lineheight];
		slp.dst = img.addr + (slp.y * img.line_length
				/ (img.bits_per_pixel / 8) + x);
		*(unsigned int *)slp.dst = slp.color;
		slp.y++;
	}
}

int	ft_select_start(t_data *dt)
{
	t_ray	ray1;
	t_ray	ray2;

	ray1 = ft_init_ray(*dt, dt->sprite.x - 1);
	ft_calc_ray(&ray1, dt->info.imap, dt, dt->sprite.x - 1);
	ray2 = ft_init_ray(*dt, dt->sprite.x_end + 1);
	ft_calc_ray(&ray2, dt->info.imap, dt, dt->sprite.x_end + 1);
	if (ray1.perpwalldist > ray2.perpwalldist)
		return (0);
	else
		return (dt->sprite.lineheight - 1 - (dt->sprite.x_end - dt->sprite.x));
}

void	ft_put_sprite(t_data *dt)
{
	t_img	im_s;
	int		x;
	int		lim;
	int		start;

	start = 0;
	if (dt->sprite.x_end - dt->sprite.x < dt->sprite.lineheight)
	{
		start = ft_select_start(dt);
		lim = dt->sprite.x_end - dt->sprite.x;
	}
	else
		lim = dt->sprite.lineheight;
	im_s.img = mlx_new_image(dt->mlx, lim, dt->sprite.lineheight);
	im_s.addr = (int *) mlx_get_data_addr(im_s.img, &im_s.bits_per_pixel,
			&im_s.line_length, &im_s.endian);
	x = 0;
	while (x < lim)
	{
		sprite_line_put(dt, x, im_s, start);
		x++;
	}
	mlx_put_image_to_window(dt->mlx, dt->mlx_w, im_s.img, dt->sprite.x, \
			SCREENHEIGHT / 2 - dt->sprite.lineheight / 2);
	mlx_destroy_image(dt->mlx, im_s.img);
}

int	ft_update_img(void *param)
{
	t_ray	ray;
	t_draw	draw;
	int		x;
	t_data	*dt;

	dt = (t_data *)param;
	ft_do_move(dt);
	ft_init_sprite(dt);
	ft_change_key(dt);
	ft_take_key(dt);
	dt->img_pp.img = mlx_new_image(dt->mlx, SCREENWIDTH, SCREENHEIGHT);
	dt->img_pp.addr = (int *) mlx_get_data_addr(dt->img_pp.img,
			&dt->img_pp.bits_per_pixel, &dt->img_pp.line_length,
			&dt->img_pp.endian);
	x = 0;
	while (x < dt->w)
	{
		ray = ft_init_ray(*dt, x);
		ft_calc_ray(&ray, dt->info.imap, dt, x);
		ft_get_draw_info(*dt, ray, &draw);
		my_mlx_line_put(dt, x, draw);
		x++;
	}
	return (ft_update_img_aux(dt), 0);
}
