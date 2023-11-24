/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imontero <imontero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 18:10:37 by imontero          #+#    #+#             */
/*   Updated: 2023/11/24 16:29:15 by imontero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
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
	int			f;
	int			c;
	int			start_map;
}				t_cube;

typedef struct	s_parse
{
	int i;
	int lastelem;
	int firstmap;
	int counttx;
	int countfc;

}				t_parse;

char	*ft_get_cub(t_cube *cub, int fd);
void	ft_checks(t_cube *cub, int fd);




#endif
