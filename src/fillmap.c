/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imontero <imontero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 08:37:25 by imontero          #+#    #+#             */
/*   Updated: 2023/11/25 09:52:55 by imontero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cube.h"

static void	ft_check_map_perimeter_aux(t_cube *cub, size_t i, size_t j)
{
	if (i == 0 || i == ft_matlen(cub->map) - 1)
	{
		if (cub->map[i][j] != '1' && cub->map[i][j] != '.')
			free_exit("Error\nMap not surrounded by walls\n", cub);
	}
	else if (j == 0 || j == ft_strlen(cub->map[i]) - 1)
	{
		if (cub->map[i][j] != '1' && cub->map[i][j] != '.')
			free_exit("Error\nMap not surrounded by walls\n", cub);
	}
	else
	{
		if ((cub->map[i][j] != '1' && cub->map[i][j] != '.') &&
				(cub->map[i - 1][j] == '.' || cub->map[i + 1][j] == '.' ||
				cub->map[i][j - 1] == '.' || cub->map[i][j + 1] == '.'))
			free_exit("Error\nMap not sorrounded by walls\n", cub);
	}
}

//check if map is surrounded by '1'
void	ft_check_map_perimeter(t_cube *cub)
{
	size_t i;
	size_t j;

	i = 0;
	while (cub->map[i])
	{
		j = 0;
		while (cub->map[i][j])
		{
			ft_check_map_perimeter_aux(cub, i, j);
			j++;
		}
		i++;
	}
}

static void	ft_fill_map_aux2(t_cube *cub, int matlen, int targetlen)
{
	int	i;
	int	j;
	
	i = 0;
	while (i < matlen)
	{
		cub->map[i] = malloc(sizeof(char) * (targetlen + 1));
		if (!cub->map[i])
			free_exit("Error\nMalloc error\n", cub);
		cub->map[i][targetlen] = '\0';
		j = 0;
		while (j < targetlen)
		{
			cub->map[i][j] = '.';
			j++;
		}
		i++;
	}
}

//fill map wit '.' and substitute ' ' for '.' to check if it is surrounded by walls
static void	ft_fill_map_aux(t_cube *cub, char **premap, int matlen, int targetlen)
{
	int	i;
	int	j;

	ft_fill_map_aux2(cub, matlen, targetlen);
	i = 0;
	while (premap[i])
	{
		j = 0;
		while (premap[i][j])
		{
			if (premap[i][j] == ' ')
				cub->map[i][j] = '.';
			else
				cub->map[i][j] = premap[i][j];
			j++;
		}
		i++;
	}
	ft_check_map_perimeter(cub);
}

//fill map with '.' to check if it is surrounded by walls
void	ft_fill_map(t_cube *cub, char **premap)
{
	int	targetlen;
	int	matlen;

	matlen = ft_matlen(premap);
	targetlen = ft_longest_str(premap);
	cub->map = malloc(sizeof(char *) * (matlen + 1));
	if (!cub->map)
		free_exit("Error\nMalloc error\n", cub);
	cub->map[matlen] = NULL;
	ft_fill_map_aux(cub, premap, matlen, targetlen);
}
