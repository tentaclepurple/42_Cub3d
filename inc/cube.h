/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imontero <imontero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 18:10:37 by imontero          #+#    #+#             */
/*   Updated: 2023/11/25 09:15:07 by imontero         ###   ########.fr       */
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

/*
	parse
*/
char	*ft_get_cub(t_cube *cub, int fd);
void	ft_checks(t_cube *cub, int fd);

/* 
	fill map
*/
void	ft_fill_map(t_cube *cub, char **premap);
void	ft_check_map_perimeter(t_cube *cub);

/* 
	elems
 */
void	ft_search_elems_aux(t_cube *cub, t_parse *p, char **spl);
int		ft_save_color(char **spl, t_parse *p, t_cube *cub, int count);
void	ft_save_path(t_cube *cub, char *path, t_parse *p, char **elem);
void	ft_get_elements(t_cube *cub, char *str);
void	ft_search_elems(t_cube *cub, char **spl, t_parse *p);

/* 
	utils
*/
int		transf_rgb(int r, int g, int b);
int		my_atoi(const char *str);
int		ft_longest_str(char **str);
size_t	ft_matlen(char **str);
char	**custom_split(char const *s);
void	init_cub(t_cube *cub);

/* 
	errors
*/
void	free_exit(char *str, t_cube *cub);
void	free_exit_mat(char *str, t_cube *cub);



#endif
