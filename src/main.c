/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imontero <imontero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 18:26:21 by imontero          #+#    #+#             */
/*   Updated: 2023/11/21 21:43:20 by imontero         ###   ########.fr       */
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


/* main function */
int	main(int argc, char **argv)
{
	int	fd;
	
	if (argc != 2)
		return (printf("Error\nWrong number of arguments\n"), 0);
	if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 4))
		return (printf("Error\nWrong file extension\n"), 0);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (printf("Error\nFile not found\n"), 0);
	ft_checks(fd);
	return (0);
}
