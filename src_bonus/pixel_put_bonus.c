/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_put_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imontero <imontero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 13:00:33 by jzubizar          #+#    #+#             */
/*   Updated: 2023/12/08 09:18:23 by imontero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cube_bonus.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	int	*dst;

	dst = data->img_pp.addr + (y * data->img_pp.line_length
			/ (data->img_pp.bits_per_pixel / 8) + x);
	*(unsigned int *)dst = color;
}

void	my_mlx_line_put(t_data *data, int x, t_draw draw)
{
	int			color;
	double		step;
	double		texpos;
	int			y;
	int			texy;

	step = 1.0 * TEXHEIGHT / draw.lineheight;
	texpos = (draw.drawstart - data->h / 2 + draw.lineheight / 2) * step;
	y = 0;
	while (y < SCREENHEIGHT)
	{
		if (y < draw.drawstart)
			color = data->info.c;
		else if (y >= draw.drawend)
			color = data->info.f;
		else
		{
			texy = (int)texpos & (TEXHEIGHT - 1);
			texpos += step;
			color = data->text[draw.texnum].addr[TEXHEIGHT * texy + draw.texx];
		}
		my_mlx_pixel_put(data, x, y, color);
		y++;
	}
}

int	ft_close(t_cube *info)
{
	(void)info;
	
	/*t_cube	*info;
	
	info = (t_cube *)param;*/
	//printf("no texture: %s\n", info->no);
	exit(0);
}

int	ft_fill_color(t_img img, int x, int y)
{
	return (img.addr[y * img.line_length + x]);
}
