/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imontero <imontero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 18:26:21 by imontero          #+#    #+#             */
/*   Updated: 2023/12/07 12:30:03 by imontero         ###   ########.fr       */
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

//get just the map (str) from str. check if there are any elements after map.
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
		printf("len: %zu\n", ft_strlen(str));
		printf("i = %zu\n", i);
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
	free(str);
	
}

/*
    check if there are any repeated elements in the map (N, S, E, W)
*/
void    ft_check_repeat_elems(t_cube *cub)
{
    int i;
    int j;
    int count;
    i = 0;
    j = 0;
    count = 0;
    while (cub->map[i])
    {
        j = 0;
        while (cub->map[i][j])
        {
            if (ft_strchr("NSEW", cub->map[i][j]))
                count++;
            j++;
        }
        i++;
    }
    if (count != 1)
        free_exit("Error\nWrong number of players\n", cub);
}

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
void    ft_get_pos(t_cube *cub)
{
    int i;
    int j;
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
void    ft_get_map_size(t_cube *cub)
{
    int i;
    int j;
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
void    ft_map_values(t_cube *cub)
{
    ft_check_repeat_elems(cub);
    ft_get_pos(cub);
    ft_get_map_size(cub);
	ft_map_char_2_int(cub);
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
    ft_map_values(&cub);
	init_game(cub);
	free_exit("agur\n", &cub);
	return (0);
}


/*int	main(int argc, char **argv)
{
	int	fd;
	t_cube	*cub;

	cub = malloc(sizeof(t_cube));
	init_cub(cub);
	if (argc != 2)
		free_exit("Error\nWrong number of arguments\n", cub);
	if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 4))
		free_exit("Error\nWrong file extension\n", cub);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		free_exit("Error\nFile not found\n", cub);
	ft_checks(cub, fd);
    ft_map_values(cub);
	init_game(cub);
	free_exit("agur\n", cub);
	return (0);
}*/