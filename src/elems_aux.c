/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elems_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imontero <imontero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 08:56:07 by imontero          #+#    #+#             */
/*   Updated: 2023/12/11 10:35:36 by imontero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cube.h"

/* 
	search for NO, SO, WE, EA, S, F elems.
	get wall textures paths and C, F rgb values 
	get the index for last elem and first map line.
	if "1" is found, count1 is incremented. if more than 1 found, error.
	if last elem index is greater than first map index, error.
 */
void	ft_search_elems(t_cube *cub, char **spl, t_parse *p)
{
	while (spl[p->i])
	{
		ft_search_elems_aux(cub, p, spl);
		p->i++;
	}
	if (p->counttx != 4 || p->countf != 1 || p->countc != 1)
		free_exit("Error\nInvalid number of textures or colors\n", cub);
	else if (p->lastelem > p->firstmap)
		free_exit("Error\nUnexpeted element order\n", cub);
}

//get elements from cub file
void	ft_get_elements(t_cube *cub, char *str)
{
	char	**spl;
	t_parse	p;

	ft_bzero(&p, sizeof(t_parse));
	spl = custom_split(str);
	ft_search_elems(cub, spl, &p);
	ft_free_split(spl);
}

//initialize cub struct
void	init_cub(t_cube *cub)
{
	ft_bzero(cub, sizeof(t_cube));
	cub->start_map = 0;
	cub->no = ft_strdup("");
	cub->so = ft_strdup("");
	cub->we = ft_strdup("");
	cub->ea = ft_strdup("");
}
