/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josu <josu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 08:41:58 by imontero          #+#    #+#             */
/*   Updated: 2023/12/08 21:19:53 by josu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cube_bonus.h"

void	free_exit_mat(char *str, t_cube *cub)
{
	printf("%s", str);
	free(cub->no);
	free(cub->so);
	free(cub->we);
	free(cub->ea);
	ft_free_split(cub->map);
	exit(-1);
}

void	free_exit(char *str, t_cube *cub)
{
	printf("%s", str);
	free(cub->no);
	free(cub->so);
	free(cub->we);
	free(cub->ea);
	exit(-1);
}
