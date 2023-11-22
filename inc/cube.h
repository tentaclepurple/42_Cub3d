/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imontero <imontero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 18:10:37 by imontero          #+#    #+#             */
/*   Updated: 2023/11/22 12:02:16 by imontero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "../libft/libft.h"

typedef struct	s_cube
{
	char		**map;
	int			res_x;
	int			res_y;
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	char		*s;
	int			f;
	int			c;
}				t_cube;

typedef struct	s_parse
{
	int lastelem;
	int firstmap;
}				t_parse;

char	*ft_get_cub(int fd);
void	ft_checks(int fd);


#endif
