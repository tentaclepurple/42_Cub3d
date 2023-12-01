/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzubizar <jzubizar@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 18:25:04 by josu              #+#    #+#             */
/*   Updated: 2023/12/01 17:57:57 by jzubizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"

void	ft_free_textures(int **textures)
{
	for (int i = 0; i < 8; i++)
	{
		free(textures[i]);
	}
	free(textures);
}

t_img ft_read_texture(void *mlx)
{
  t_img image;
  
  image.img = mlx_xpm_file_to_image(mlx, "./sprites/pac_semi_right.xpm", &image.x, &image.y);
  image.addr = (int *) mlx_get_data_addr(image.img, &image.bits_per_pixel, &image.line_length, &image.endian);
  image.line_length = image.line_length / 4;
  return (image);
}

int	**ft_gen_texture(void)
{
	int	**texture;
	
	texture = malloc(sizeof(int *) * 8);
	for (int i = 0; i < 8; i++)
	{
		texture[i] = malloc(sizeof(int) * (texWidth * texHeight));
	}
	//generate some textures
  for(int x = 0; x < texWidth; x++)
  for(int y = 0; y < texHeight; y++)
  {
    int xorcolor = (x * 256 / texWidth) ^ (y * 256 / texHeight);
    //int xcolor = x * 256 / texWidth;
    int ycolor = y * 256 / texHeight;
    int xycolor = y * 128 / texHeight + x * 128 / texWidth;
    texture[0][texWidth * y + x] = 65536 * 254 * (x != y && x != texWidth - y); //flat red texture with black cross
    texture[1][texWidth * y + x] = xycolor + 256 * xycolor + 65536 * xycolor; //sloped greyscale
    texture[2][texWidth * y + x] = 256 * xycolor + 65536 * xycolor; //sloped yellow gradient
    texture[3][texWidth * y + x] = xorcolor + 256 * xorcolor + 65536 * xorcolor; //xor greyscale
    texture[4][texWidth * y + x] = 256 * xorcolor; //xor green
    texture[5][texWidth * y + x] = 65536 * 192 * (x % 16 && y % 16); //red bricks
    texture[6][texWidth * y + x] = 65536 * ycolor; //red gradient
    texture[7][texWidth * y + x] = 128 + 256 * 128 + 65536 * 128; //flat grey texture
  }
  return (texture);
}