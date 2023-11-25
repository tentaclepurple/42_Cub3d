/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imontero <imontero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 18:26:21 by imontero          #+#    #+#             */
/*   Updated: 2023/11/25 07:59:23 by imontero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cube.h"

#include <stdlib.h>

void	ft_print_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		printf("[%i]%s\n", i, map[i]);
		i++;
	}
}

static int	word_count(char const *s)
{
	unsigned int	i;
	unsigned int	flag;
	int				num;

	i = 0;
	flag = 0;
	num = 0;
	while (s[i])
	{
		if (s[i] != ' ' && s[i] != '\n' && s[i] != ',')
			flag = 1;
		else if (flag && (s[i] == ' ' || s[i] == '\n' || s[i] == ','))
		{
			num++;
			flag = 0;
		}
		i++;
	}
	if (flag)
		num++;
	return (num);
}

static int	str_char_len(char const *s)
{
	unsigned int	i;

	i = 0;
	while (s[i] != ' ' && s[i] != '\n' && s[i] != ',' && s[i])
		i++;
	return (i);
}

static char	*fill_word(char *wrd, char *str)
{
	unsigned int	i;

	i = 0;
	while (str[i] != ' ' && str[i] != '\n' && str[i] != ',' && str[i])
	{
		wrd[i] = str[i];
		i++;
	}
	wrd[i] = '\0';
	return (wrd);
}

static int	split_low(char **split, char const *s)
{
	char	*str;
	char	*word;
	int		len;
	int		i;

	str = (char *)s;
	i = 0;
	while (i < word_count(s))
	{
		len = str_char_len(str);
		if (len > 0)
		{
			word = malloc(sizeof(char) * (len + 1));
			if (!word)
				return (i + 1);
			word = fill_word(word, str);
			split[i++] = word;
			str += len;
		}
		else
			str++;
		while (*str == ' ' || *str == '\n' || *str == ',')
			str++;
	}
	return (split[i] = NULL, 0);
}

//split string by spaces, commas and \n
char	**custom_split(char const *s)
{
	char	**split;
	int		err;
	int		i;

	split = malloc(sizeof(char *) * (word_count(s) + 1));
	if (!split)
		return (NULL);
	err = split_low(split, s);
	if (err)
	{
		i = 0;
		while (i < err - 1)
		{
			free(split[i]);
			i++;
		}
		free(split);
		return (NULL);
	}
	return (split);
}

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

//check if path is xpm and opens it to check if it is a valid path
void	ft_save_path(t_cube *cub, char *path, t_parse *p, char **elem)
{
	int fd;

	fd = open(path, O_RDONLY);
	if (ft_strncmp(path + ft_strlen(path) - 4, ".xpm", 4) || fd == -1)
		free_exit("Error\nInvalid path\n", cub);
	free(*elem);
	*elem = ft_strdup(path);
	p->lastelem = p->i;
	p->i++;
	p->counttx++;
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
		cub->f = ft_save_color(spl, p, cub, p->countfc++);
	else if (spl[p->i + 1] && !ft_strncmp("C", spl[p->i], 1))
		cub->c = ft_save_color(spl, p, cub, p->countfc++);
	/* else if (ft_strncmp("C", spl[p->i], 1) && ft_strncmp("F", spl[p->i], 1) &&
			ft_strncmp("NO", spl[p->i], 2) && ft_strncmp("SO", spl[p->i], 2) &&
			ft_strncmp("WE", spl[p->i], 2) && ft_strncmp("EA", spl[p->i], 2) &&
			ft_strncmp("1", spl[p->i], 1) && (!ft_strncmp("1", spl[p->i], 1) && ft_strlen(spl[p->i]) > 1))
	{
		printf("spl[%i] ---> %s\n", p->i, spl[p->i]);
		free_exit("Error\nUnexpected element/character\n", cub);
	}	 */
	
	else
	{
		printf("spl[%i] ---> %s\n", p->i, spl[p->i]);
		free_exit("Error\nUnexpected element/character\n", cub);
	}	
}

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
	if (p->counttx != 4 || p->countfc != 2)
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

//check if map is surrounded by '1'
void	ft_check_map_perimeter(t_cube *cub)
{
	size_t i;
	size_t j;

	i = 0;
	while (cub->map[i])
	{
		j = 0;
		while (cub->map[i][j])
		{
			if (i == 0 || i == ft_matlen(cub->map) - 1)
			{
				if (cub->map[i][j] != '1' && cub->map[i][j] != '.')
					free_exit("Error\nMap not surrounded by walls\n", cub);
			}
			else if (j == 0 || j == ft_strlen(cub->map[i]) - 1)
			{
				if (cub->map[i][j] != '1' && cub->map[i][j] != '.')
					free_exit("Error\nMap not surrounded by walls\n", cub);
			}
			else
			{
				if ((cub->map[i][j] != '1' && cub->map[i][j] != '.') &&
						(cub->map[i - 1][j] == '.' || cub->map[i + 1][j] == '.' ||
						cub->map[i][j - 1] == '.' || cub->map[i][j + 1] == '.'))
					free_exit("Error\nMap not sorrounded by walls\n", cub);
			}
			j++;
		}
		i++;
	}
}

void	ft_fill_map_aux2(t_cube *cub, int matlen, int targetlen)
{
	int	i;
	int	j;
	
	i = 0;
	while (i < matlen)
	{
		cub->map[i] = malloc(sizeof(char) * (targetlen + 1));
		if (!cub->map[i])
			free_exit("Error\nMalloc error\n", cub);
		cub->map[i][targetlen] = '\0';
		j = 0;
		while (j < targetlen)
		{
			cub->map[i][j] = '.';
			j++;
		}
		i++;
	}
}

//fill map wit '.' and substitute ' ' for '.' to check if it is surrounded by walls
void	ft_fill_map_aux(t_cube *cub, char **premap, int matlen, int targetlen)
{
	int	i;
	int	j;

	ft_fill_map_aux2(cub, matlen, targetlen);
	i = 0;
	while (premap[i])
	{
		j = 0;
		while (premap[i][j])
		{
			if (premap[i][j] == ' ')
				cub->map[i][j] = '.';
			else
				cub->map[i][j] = premap[i][j];
			j++;
		}
		i++;
	}
	ft_check_map_perimeter(cub);
}

//fill map with '.' to check if it is surrounded by walls
void	ft_fill_map(t_cube *cub, char **premap)
{
	int	targetlen;
	int	matlen;

	matlen = ft_matlen(premap);
	targetlen = ft_longest_str(premap);
	cub->map = malloc(sizeof(char *) * (matlen + 1));
	if (!cub->map)
		free_exit("Error\nMalloc error\n", cub);
	cub->map[matlen] = NULL;
	ft_fill_map_aux(cub, premap, matlen, targetlen);
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

//initialize cub struct
void	init_cub(t_cube *cub)
{
	ft_bzero(cub, sizeof(t_cube));
	cub->no = ft_strdup("");
	cub->so = ft_strdup("");
	cub->we = ft_strdup("");
	cub->ea = ft_strdup("");
}

/* main function */
int	main(int argc, char **argv)
{
	int	fd;
	t_cube	cub;

	init_cub(&cub);
	if (argc != 2)
		return (printf("Error\nWrong number of arguments\n"), 0);
	if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 4))
		return (printf("Error\nWrong file extension\n"), 0);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (printf("Error\nFile not found\n"), 0);
	ft_checks(&cub, fd);
	return (0);
}
