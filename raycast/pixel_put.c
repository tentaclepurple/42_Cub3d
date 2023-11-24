/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_put.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzubizar <jzubizar@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 13:00:33 by jzubizar          #+#    #+#             */
/*   Updated: 2023/11/24 13:01:11 by jzubizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	my_mlx_line_put(t_data *data, int x, int drawStart, int drawEnd, int color)
{
	int i;

	i = drawStart;
	while (i < drawEnd)
	{
		my_mlx_pixel_put(data, x, i, color);
		i++;
	}
}

int	ft_close(int key, void *param)
{
	(void)key;
	(void)param;
	exit(0);
}
