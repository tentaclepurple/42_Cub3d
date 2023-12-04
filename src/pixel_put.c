/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_put.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzubizar <jzubizar@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 13:00:33 by jzubizar          #+#    #+#             */
/*   Updated: 2023/12/02 17:32:50 by jzubizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	my_mlx_line_put(t_data *data, int x, t_draw draw)
{
    int		color;
    double	step;
    double	texPos;
	int		y;
	int		texY;
    
	// How much to increase the texture coordinate per screen pixel
	step = 1.0 * texHeight / draw.lineHeight;
	texPos = (draw.drawStart - data->h / 2 + draw.lineHeight / 2) * step;
	//for(int y = 0; y<screenHeight; y++)
	y = 0;
	while (y < screenHeight)
	{
		// Select color deppending it is a pixel of floor, wall or celling
		if (y < draw.drawStart)
			color = 0x696969;
		else if (y >= draw.drawEnd)
			color = 0xc0c0c0;
		else
		{
			// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
			texY = (int)texPos & (texHeight - 1);
			texPos += step;
			color = data->text[draw.texNum].addr[texHeight * texY + draw.texX];
		}
		//Put the pixel in the corresponding place and color
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