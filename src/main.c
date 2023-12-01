/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imontero <imontero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 18:26:21 by imontero          #+#    #+#             */
/*   Updated: 2023/11/25 09:37:19 by imontero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cube.h"

void	ft_print_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		printf("[%i]%s\n", i, map[i]);
		i++;
	}
	//delete this
}

//get just the map from str. check if there are any elements after map.
char	*ft_extract_map(t_cube *cub, char *str)
{
	size_t		i;
	int			len;

	len = 0;
	i = cub->start_map;
	while (str[i])
	{
		if (str[i] == '\n' && (str[i + 1] == '\0' || str[i + 1] == '\n'))
			break ;
		len++;
		i++;
	}
	if (ft_strlen(str) > i)
	{
		free(str);
		free_exit("Error\nUnexpected elements after map\n", cub);
	}
	return (ft_substr(str, cub->start_map, len));
}

//check unexpected characters in map
void	ft_check_premap(char **premap, t_cube *cub)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (premap[i])
	{
		j = 0;
		while (premap[i][j])
		{
			if (!ft_strchr("012NSEW ", premap[i][j]))
			{
				ft_free_split(premap);
				free_exit("Error\nUnexpected character(s) in map\n", cub);
			}
			j++;
		}
		i++;
	}
}

/* 
	start all checkes
*/
void	ft_checks(t_cube *cub, int fd)
{
	char	*str;
	char	*mapstr;
	char	**premap;

	str = ft_get_cub(cub, fd);
	ft_get_elements(cub, str);
	mapstr = ft_extract_map(cub, str);
	premap = ft_split(mapstr, '\n');
	free(mapstr);
	ft_check_premap(premap, cub);
	ft_fill_map(cub, premap);
	//ft_print_map(cub->map);	
	free(str);
	free_exit("agur\n", cub);
}



/* main function */
int	main(int argc, char **argv)
{
	int	fd;
	t_cube	cub;

	init_cub(&cub);
	if (argc != 2)
		free_exit("Error\nWrong number of arguments\n", &cub);
	if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 4))
		free_exit("Error\nWrong file extension\n", &cub);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		free_exit("Error\nFile not found\n", &cub);
	ft_checks(&cub, fd);
	return (0);
}
