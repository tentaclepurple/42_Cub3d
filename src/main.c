/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imontero <imontero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 18:26:21 by imontero          #+#    #+#             */
/*   Updated: 2023/11/22 13:20:00 by imontero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cube.h"

/* 
	uses get_netx_line to read the file return it.
*/
char	*ft_get_cub(int fd)
{
	char	*line;
	char	*tmp;
	char	*aux;

	tmp = ft_strdup("");
	line = get_next_line(fd);
	while (line)
	{
		aux = ft_strjoin(tmp, line);
		free(tmp);
		free(line);
		tmp = ft_strdup(aux);
		free(aux);
		line = get_next_line(fd);
	}
	return (tmp);	
}

/* 
	search for NO, SO, WE, EA, S, F, C, R elems.
	get wall textures paths and C, F rgb values 
	get the index for last elem and first map line.
	elemidxs[0] = lastelem
	elemidxs[1] = firstmap
 */
void	ft_search_elems(t_cube *cub, char **spl, int **elemidxs)
{
	int	i;

	i = 0;
	while (spl[i])
	{
		if (!ft_strncmp("1", spl[i], 1))
			*(elemidxs[1]) = i;
		else if (spl[i + 1] != NULL && !ft_strncmp("NO", spl[i], 2))
			ft_save_path(spl[i + 1], i, elemidxs);
	}
}



void	ft_get_elements(t_cube *cub, char *str)
{
	char	**spl;
	int		i;
	int		elemidxs[2];

	i = 0;	
	spl = ft_split(str, ' ');
	ft_search_elems(cub, spl, &elemidxs);
	while (spl[i])
	{
		printf("%s\n", spl[i]);
		i++;
	}
	
	
	
	ft_free_split(spl);
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
void	ft_checks(t_cube *cub, int fd)
{
	char	*str;

	str = ft_get_cub(fd);
	ft_get_elements(cub, str);
	/* printf("%s\n", str);
	printf("\n**************\n\n");
	spl = ft_split(str, '\n'); */
	free(str);
	
}

/* main function */
int	main(int argc, char **argv)
{
	int	fd;
	t_cube	cub;

	if (argc != 2)
		return (printf("Error\nWrong number of arguments\n"), 0);
	if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 4))
		return (printf("Error\nWrong file extension\n"), 0);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (printf("Error\nFile not found\n"), 0);
	ft_checks(&cub, fd);
	return (0);
}
