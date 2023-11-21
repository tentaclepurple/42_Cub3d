/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imontero <imontero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 18:46:22 by imontero          #+#    #+#             */
/*   Updated: 2023/11/21 21:30:01 by imontero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cube.h"

char	*ft_get_cube(int fd)
{
	char	*line;
	char	*tmp;

	line = get_next_line(fd);
	while (line)
	{
		tmp = ft_strjoin(tmp, line);
		free(line);
		line = get_next_line(fd);
	}
	return (tmp);
}

/* 
	*.cub checks:
		- elements first, map last.
		- valid elements in cub file:
			- color for ceiling and floor:
				F 220,100,0 or C 225,30,0 (RGB 0-255)
			-texture for walls:
				NO ./path_to_the_north_texture
				SO ./path_to_the_south_texture
				WE ./path_to_the_west_texture
				EA ./path_to_the_east_texture
		- only 1 player and valid characters (N, S, E, W)
		- surrounded by walls
*/
void	ft_checks(int fd)
{
	char	*str;

	str = ft_get_cube(fd);
	printf("%s\n", str);
	free(str);
}
