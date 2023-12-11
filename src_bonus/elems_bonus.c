/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elems_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imontero <imontero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 08:54:31 by imontero          #+#    #+#             */
/*   Updated: 2023/12/11 11:42:53 by imontero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cube_bonus.h"

int	ft_check_bonus_textures(void)
{
	int	fd[8];
	int	i;

	i = 0;
	fd[0] = open("textures/key1.xpm", O_RDONLY);
	fd[1] = open("textures/key2.xpm", O_RDONLY);
	fd[2] = open("textures/key4.xpm", O_RDONLY);
	fd[3] = open("textures/key5.xpm", O_RDONLY);
	fd[4] = open("textures/key6.xpm", O_RDONLY);
	fd[5] = open("textures/key7.xpm", O_RDONLY);
	fd[6] = open("textures/key8.xpm", O_RDONLY);
	fd[7] = open("textures/pixel3.xpm", O_RDONLY);
	if (fd[0] == -1 || fd[1] == -1 || fd[2] == -1 || fd[3] == -1 || fd[4] == -1
		|| fd[5] == -1 || fd[6] == -1 || fd[7] == -1)
		return (0);
	while (i < 8)
		close(fd[i++]);
	return (1);
}

//check if path is xpm and opens it to check if it is a valid path
void	ft_save_path(t_cube *cub, char *path, t_parse *p, char **elem)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (ft_strncmp(path + ft_strlen(path) - 4, ".xpm", 4) || fd == -1)
		free_exit("Error\nInvalid path\n", cub);
	free(*elem);
	*elem = ft_strdup(path);
	p->lastelem = p->i;
	p->i++;
	p->counttx++;
}

/* 
	checks if color is valid and returns it converted to int.
 */
int	ft_save_color(char **spl, t_parse *p, t_cube *cub, int count)
{
	int	k;
	int	rgb[3];

	(void)count;
	p->lastelem = p->i;
	k = 0;
	p->i++;
	while (k < 3)
	{
		if (!spl[p->i] || my_atoi(spl[p->i]) < 0 || my_atoi(spl[p->i]) > 255)
			free_exit("Error\nInvalid color\n", cub);
		rgb[k] = my_atoi(spl[p->i]);
		p->i++;
		k++;
	}
	p->i--;
	return (transf_rgb(rgb[0], rgb[1], rgb[2]));
}

/* 
	search lines starting with "1" or any of the elements. 
	Anythig else is invalid.
 */
void	ft_search_elems_aux(t_cube *cub, t_parse *p, char **spl)
{
	if (!ft_strncmp("1", spl[p->i], 1))
	{
		if (!ft_strncmp("1", spl[0], 1))
			free_exit("Error\nUnexpected map position\n", cub);
		if (p->firstmap == 0)
			p->firstmap = p->i;
	}
	else if (spl[p->i + 1] && !ft_strncmp("NO", spl[p->i], 2))
		ft_save_path(cub, spl[p->i + 1], p, &(cub->no));
	else if (spl[p->i + 1] && !ft_strncmp("SO", spl[p->i], 2))
		ft_save_path(cub, spl[p->i + 1], p, &(cub->so));
	else if (spl[p->i + 1] && !ft_strncmp("WE", spl[p->i], 2))
		ft_save_path(cub, spl[p->i + 1], p, &(cub->we));
	else if (spl[p->i + 1] && !ft_strncmp("EA", spl[p->i], 2))
		ft_save_path(cub, spl[p->i + 1], p, &(cub->ea));
	else if (spl[p->i + 1] && !ft_strncmp("F", spl[p->i], 1))
		cub->f = ft_save_color(spl, p, cub, p->countf++);
	else if (spl[p->i + 1] && !ft_strncmp("C", spl[p->i], 1))
		cub->c = ft_save_color(spl, p, cub, p->countc++);
	else
		free_exit("Error\nUnexpected element/character\n", cub);
}
