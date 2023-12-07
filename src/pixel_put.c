/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_put.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imontero <imontero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 13:00:33 by jzubizar          #+#    #+#             */
/*   Updated: 2023/12/07 13:01:06 by imontero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cube.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	int	*dst;

	dst = data->img_pp.addr + (y * data->img_pp.line_length /
			(data->img_pp.bits_per_pixel / 8) + x);
	*(unsigned int*)dst = color;
}

void	my_mlx_line_put(t_data *data, int x, t_draw draw)
{
    int		color;
    double	step;
    double	texPos;
	int		y;
	int		texY;
    
	step = 1.0 * TEXHEIGHT / draw.lineHeight;
	texPos = (draw.drawStart - data->h / 2 + draw.lineHeight / 2) * step;
	y = 0;
	while (y < SCREENHEIGHT)
	{
		if (y < draw.drawStart)
			color = data->info.c;
		else if (y >= draw.drawEnd)
			color = data->info.f;
		else
		{
			texY = (int)texPos & (TEXHEIGHT - 1);
			texPos += step;
			color = data->text[draw.texNum].addr[TEXHEIGHT * texY + draw.texX];
		}
		my_mlx_pixel_put(data, x, y, color);
	y++;
	}
}

int	ft_close(int key, void *param)
{
	(void)key;
	(void)param;
	exit(0);
}

int   ft_fill_color(t_img img, int x, int y)
{
	return (img.addr[y * img.line_length + x]);
}