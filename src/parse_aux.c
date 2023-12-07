/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imontero <imontero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 08:38:49 by imontero          #+#    #+#             */
/*   Updated: 2023/12/07 12:42:04 by imontero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cube.h"

//get number of lines in map
size_t	ft_matlen(char **str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

//get longest string in map
int	ft_longest_str(char **str)
{
	int	i;
	int	j;
	int	max;

	i = 0;
	max = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
			j++;
		if (j > max)
			max = j;
		i++;
	}
	return (max);
}

int	my_atoi(const char *str)
{
	int	i;
	int	sign;
	int	res;

	i = 0;
	sign = 1;
	res = 0;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		str++;
	while (*str)
	{
        if (*str >= '0' && *str <= '9')
            res = res * 10 + (*str - '0');
        else
            return -1;
        str++;
    }
	return (res * sign);
}

int	transf_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

/* 
	uses get_netx_line to read the file return it.
*/
char	*ft_get_cub(t_cube *cub, int fd)
{
	char	*line;
	char	*tmp;
	char	*aux;
	int		count;

	count = 0;
	tmp = ft_strdup("");
	line = get_next_line(fd);
	//QUE cojones pasa aqui
	while (line)
	{
		if (ft_strnstr(line, "11", ft_strlen(line)) && !ft_strchr(line, ',') &&
				!ft_strnstr(line, ".xpm", ft_strlen(line)) && cub->start_map == 0)
			cub->start_map = count;
		count += ft_strlen(line);
		aux = ft_strjoin(tmp, line);
		free(tmp);
		free(line);
		tmp = ft_strdup(aux);
		free(aux);
		line = get_next_line(fd);
	}
	return (tmp);	
}
