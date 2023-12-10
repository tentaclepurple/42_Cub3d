/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imontero <imontero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 18:25:04 by josu              #+#    #+#             */
/*   Updated: 2023/12/10 20:38:05 by imontero         ###   ########.fr       */
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

void	ft_change_key(t_data *dt)
{
	static int	i = 1;

	if (i % 10 == 0)
		dt->text[5] = ft_read_texture(dt->mlx, "textures/key1.xpm");
	if (i % 20 == 0)
		dt->text[5] = ft_read_texture(dt->mlx, "textures/key2.xpm");
	if (i % 30 == 0)
		dt->text[5] = ft_read_texture(dt->mlx, "textures/key7.xpm");
	if (i % 40 == 0)
		dt->text[5] = ft_read_texture(dt->mlx, "textures/key4.xpm");
	if (i % 50 == 0)
		dt->text[5] = ft_read_texture(dt->mlx, "textures/key5.xpm");
	if (i % 60 == 0)
		dt->text[5] = ft_read_texture(dt->mlx, "textures/key6.xpm");
	if (i % 70 == 0)
		dt->text[5] = ft_read_texture(dt->mlx, "textures/key7.xpm");
	if (i % 80 == 0)
	{
		dt->text[5] = ft_read_texture(dt->mlx, "textures/key8.xpm");
		i = 0;
	}
	i++;
}

void	ft_read_textures(t_data *dt)
{
	int	res;

	res = RES;
	dt->pix = mlx_xpm_file_to_image(dt->mlx, "textures/pixel3.xpm", &res, &res);
	dt->text[0] = ft_read_texture(dt->mlx, dt->info.so);
	dt->text[1] = ft_read_texture(dt->mlx, dt->info.no);
	dt->text[2] = ft_read_texture(dt->mlx, dt->info.ea);
	dt->text[3] = ft_read_texture(dt->mlx, dt->info.we);
	dt->text[4] = ft_read_texture(dt->mlx, "textures/door.xpm");
	dt->text[5] = ft_read_texture(dt->mlx, "textures/key1.xpm");
}
