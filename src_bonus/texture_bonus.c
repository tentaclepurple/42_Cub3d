/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imontero <imontero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 18:25:04 by josu              #+#    #+#             */
/*   Updated: 2023/12/07 19:43:30 by imontero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cube_bonus.h"

void	ft_free_textures(int **textures)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		free(textures[i]);
		i++;
	}
	free(textures);
}

t_img	ft_read_texture(void *mlx, char *name)
{
	t_img	image;

	image.img = mlx_xpm_file_to_image(mlx, name, &image.x, &image.y);
	image.addr = (int *) mlx_get_data_addr(image.img, &image.bits_per_pixel,
			&image.line_length, &image.endian);
	image.line_length = image.line_length / 4;
	return (image);
}

void	ft_read_textures(t_data *dt)
{
	dt->text[0] = ft_read_texture(dt->mlx, dt->info.so);
	dt->text[1] = ft_read_texture(dt->mlx, dt->info.no);
	dt->text[2] = ft_read_texture(dt->mlx, dt->info.ea);
	dt->text[3] = ft_read_texture(dt->mlx, dt->info.we);
}
