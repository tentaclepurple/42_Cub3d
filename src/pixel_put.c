/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_put.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imontero <imontero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 13:00:33 by jzubizar          #+#    #+#             */
/*   Updated: 2023/12/01 21:13:39 by imontero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cube.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	int	*dst;

	dst = data->img_pp.addr + (y * data->img_pp.line_length / 4 + x);
	*(unsigned int*)dst = color;
}

void	my_mlx_line_put(t_data *data, int x, t_draw draw, int side, int lineHeight)
{
	//ft_print_map(data->info.map);
	// How much to increase the texture coordinate per screen pixel
	double step = 1.0 * texHeight / lineHeight;
	int   color;
      // Starting texture coordinate
	double texPos = (draw.drawStart - data->h / 2 + lineHeight / 2) * step;
    int j = 0;
      //for(int y = draw.drawStart; y<draw.drawEnd; y++)
    for(int y = 0; y<screenHeight; y++)
    {
	if (j == data->text.line_length)
		j = 0;
        // Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
        //int texY = (int)texPos & (texHeight - 1);
        texPos += step;
		/* printf("Nº: %i -- texY: %i -- texX: %i\n", draw.texNum, texY, draw.texX);
		printf("texture: %i\n", data->textures[1][100]); */
        //int color = data->textures[draw.texNum][texHeight * texY + draw.texX];
        if (y < draw.drawStart)
            color = 0xffffff;
        else if (y >= draw.drawEnd)
            color = 0x00ff00;
        else
        {
            //color = data->text.addr[j * data->text.line_length + x];
            if (side == 1)
                color = 0x0000ff;
            else
                color = 0x0000aa;
           j++; 
        }
        //make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
        //if(side == 1) color = (color >> 1) & 8355711;
        if(side == 1)
            j++;
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