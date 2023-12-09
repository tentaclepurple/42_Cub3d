/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_calc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josu <josu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 12:53:30 by jzubizar          #+#    #+#             */
/*   Updated: 2023/12/09 15:35:47 by josu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cube_bonus.h"

/* 
	print the minimap
*/
void	ft_minimap_bgr(t_data *dt)
{
	int i;
	int j;

	i = 0;
	while (i < dt->info.map_size[0])
	{
		j = 0;
		while (j < dt->info.map_size[1])
		{
			if (dt->info.imap[i][j] == 1 || dt->info.imap[i][j] == 2
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


void	sprite_line_put(t_data *data, int x, t_img img)
{
	int			color;
	double		step;
	double		texpos;
	int			y;
	int			texy;
	int			*dst;

	step = 1.0 * TEXHEIGHT / data->sprite.lineheight;
	texpos = 0;
	y = 0;
	while (y < data->sprite.lineheight)
	{
		texy = (int)texpos & (TEXHEIGHT - 1);
		texpos += step;
		color = data->text[5].addr[TEXHEIGHT * texy + x];
		dst = img.addr + (y * img.line_length
			/ (img.bits_per_pixel / 8) + x);
		*(unsigned int *)dst = color;
		y++;
	}
}

void	ft_put_sprite(t_data *dt)
{
	t_img	im_s;
	int		x;

	im_s.img = mlx_new_image(dt->mlx, dt->sprite.lineheight, dt->sprite.lineheight);
	im_s.addr = (int *) mlx_get_data_addr(im_s.img, &im_s.bits_per_pixel,
			&im_s.line_length, &im_s.endian);
	x = 0;
	while (x < dt->sprite.lineheight)
	{
		sprite_line_put(dt, x, im_s);
		x++;
	}
	printf("Here\n");
	mlx_put_image_to_window(dt->mlx, dt->mlx_w, im_s.img, dt->sprite.x, SCREENHEIGHT /2 - dt->sprite.lineheight / 2);
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
	dt->img_pp.img = mlx_new_image(dt->mlx, SCREENWIDTH, SCREENHEIGHT);
	dt->img_pp.addr = (int *) mlx_get_data_addr(dt->img_pp.img,
			&dt->img_pp.bits_per_pixel, &dt->img_pp.line_length,
			&dt->img_pp.endian);
	x = 0;
	while (x < dt->w)
	{
		ray = ft_init_ray(*dt, x);
		ft_calc_ray(&ray, dt->info.imap, dt);
		if (dt->sprite.perpdist != 0 && dt->sprite.x == 0)
			dt->sprite.x = x;
		ft_get_draw_info(*dt, ray, &draw);
		my_mlx_line_put(dt, x, draw);
		x++;
	}
	ft_collisions(dt);
	mlx_put_image_to_window(dt->mlx, dt->mlx_w, dt->img_pp.img, 0, 0);
	ft_minimap_bgr(dt);
	if (dt->sprite.perpdist != 0)
		ft_put_sprite(dt);
	mlx_destroy_image(dt->mlx, dt->img_pp.img);
	return (0);
}
