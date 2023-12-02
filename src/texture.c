/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzubizar <jzubizar@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 18:25:04 by josu              #+#    #+#             */
/*   Updated: 2023/12/02 12:25:58 by jzubizar         ###   ########.fr       */
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


t_img ft_read_texture(void *mlx, char *name)
{
  t_img image;
  
  image.img = mlx_xpm_file_to_image(mlx, name, &image.x, &image.y);
  image.addr = (int *) mlx_get_data_addr(image.img, &image.bits_per_pixel, &image.line_length, &image.endian);
  image.line_length = image.line_length / 4;
  return (image);
}

void ft_read_textures(t_data *dt)
{
  dt->text[0] = ft_read_texture(dt->mlx, "./textures/SO.xpm");
  dt->text[1] = ft_read_texture(dt->mlx, "./textures/NO.xpm");
  dt->text[2] = ft_read_texture(dt->mlx, "./textures/EA.xpm");
  dt->text[3] = ft_read_texture(dt->mlx, "./textures/WE.xpm");
}
