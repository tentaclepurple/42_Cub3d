/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josu <josu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 12:51:13 by imontero          #+#    #+#             */
/*   Updated: 2023/12/09 12:16:50 by josu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cube.h"

void	ft_get_vector(t_cube *cub, char c)
{
	if (c == 'N')
	{
		cub->pl_dir[1] = -1;
		cub->pl_dir[0] = 0;
	}
	else if (c == 'S')
	{
		cub->pl_dir[1] = 1;
		cub->pl_dir[0] = 0;
	}
	else if (c == 'E')
	{
		cub->pl_dir[1] = 0;
		cub->pl_dir[0] = 1;
	}
	else if (c == 'W')
	{
		cub->pl_dir[1] = 0;
		cub->pl_dir[0] = -1;
	}
}

/*
    gets the starting position of the player and the direction
    if there is no player, exit with error message
 */
void	ft_get_pos(t_cube *cub)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cub->map[i])
	{
		j = 0;
		while (cub->map[i][j])
		{
			if (ft_strchr("NSEW", cub->map[i][j]))
			{
				cub->pl_pos[0] = j;
				cub->pl_pos[1] = i;
				ft_get_vector(cub, cub->map[i][j]);
				cub->map[i][j] = '0';
				return ;
			}
			j++;
		}
		i++;
	}
	free_exit("Error\nNo player found\n", cub);
}

/*
    gets the size of the map
 */
void	ft_get_map_size(t_cube *cub)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cub->map[i])
	{
		j = 0;
		while (cub->map[i][j])
		{
			j++;
		}
		i++;
	}
	cub->map_size[0] = i;
	cub->map_size[1] = j;
}

/*
	converts char map to int map
 */
void	ft_map_char_2_int(t_cube *cub)
{
	int	i;
	int	j;

	i = 0;
	cub->imap = malloc(sizeof(int *) * cub->map_size[0]);
	while (i < cub->map_size[0])
	{
		cub->imap[i] = malloc(sizeof(int) * cub->map_size[1]);
		j = 0;
		while (j < cub->map_size[1])
		{
			if (cub->map[i][j] == '0')
				cub->imap[i][j] = 0;
			else
				cub->imap[i][j] = 1;
			j++;
		}
		i++;
	}
}

/*
    check if there are any repeated elements in the map (N, S, E, W)
    gets the starting position of the player and the direction
 */
void	ft_map_values(t_cube *cub)
{
	ft_check_repeat_elems(cub);
	ft_get_pos(cub);
	ft_get_map_size(cub);
	ft_map_char_2_int(cub);
}
