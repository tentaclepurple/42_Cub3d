/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_put.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzubizar <jzubizar@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 13:00:33 by jzubizar          #+#    #+#             */
/*   Updated: 2023/12/01 20:43:23 by jzubizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	my_mlx_line_put(t_data *data, int x, t_draw draw, int lineHeight)
{
	// How much to increase the texture coordinate per screen pixel
      double step = 1.0 * texHeight / lineHeight;
      int   color;
      // Starting texture coordinate
      double texPos = (draw.drawStart - data->h / 2 + lineHeight / 2) * step;
      int j = 0;
      //for(int y = draw.drawStart; y<draw.drawEnd; y++)
      for(int y = 0; y<screenHeight; y++)
      {
        // Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
        if (y < draw.drawStart)
            color = 0xffffff;
        else if (y >= draw.drawEnd)
            color = 0x00ff00;
        else
        {
            int texY = (int)texPos & (texHeight - 1);
            texPos += step;
            color = data->text[draw.texNum].addr[texHeight * texY + draw.texX];
            /* if (side == 1)
                color = 0x0000ff;
            else
                color = 0x0000aa; */
           j++; 
        }
        my_mlx_pixel_put(data, x, y, color);
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