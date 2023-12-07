/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imontero <imontero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 08:41:58 by imontero          #+#    #+#             */
/*   Updated: 2023/12/07 11:27:29 by imontero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cube.h"

void	free_exit_mat(char *str, t_cube *cub)
{
	printf("%s", str);
	free(cub->no);
	free(cub->so);
	free(cub->we);
	free(cub->ea);
	ft_free_split(cub->map);
	exit(0);
}

void	free_exit(char *str, t_cube *cub)
{
	printf("%s", str);
	free(cub->no);
	free(cub->so);
	free(cub->we);
	free(cub->ea);
	exit(0);
}

void	free_exit_all(char *str, t_cube *cub)
{
	int	i;

	i = 0;
	printf("imap: %i\n", cub->imap[0][0]);
	printf("%s", str);
	while(i < cub->map_size[0])
	{
		free(cub->imap[i]);
		i++;
	}
	free(cub->imap);	
	free(cub->no);
	free(cub->so);
	free(cub->we);
	free(cub->ea);
	ft_free_split(cub->map);
	exit(0);
}