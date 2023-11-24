/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imontero <imontero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 18:26:21 by imontero          #+#    #+#             */
/*   Updated: 2023/11/24 00:32:04 by imontero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cube.h"

#include <stdlib.h>

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
char	*ft_get_cub(int fd)
{
	char	*line;
	char	*tmp;
	char	*aux;

	tmp = ft_strdup("");
	line = get_next_line(fd);
	while (line)
	{
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

int	ft_save_color(char **spl, t_parse *p, t_cube *cub)
{
	int	k;
	int	rgb[3];
	
	p->lastelem = p->i;
	k = 0;
	p->i++;
	while (k < 3)
	{
		if (!spl[p->i] || (spl[p->i]) < 0 || my_atoi(spl[p->i]) > 255)
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
	//printf("spl[%i]: %s\n", p->i, spl[p->i]);
	if (!ft_strncmp("1", spl[p->i], 1))
		{
			p->firstmap = p->i;
			p->count1++;
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
		cub->f = ft_save_color(spl, p, cub);
	else if (spl[p->i + 1] && !ft_strncmp("C", spl[p->i], 1))
		cub->c = ft_save_color(spl, p, cub);
	/* printf("lastelem: %i\n", p->lastelem);
	printf("firstmap: %i\n", p->firstmap);
	printf("count1: %i\n", p->count1); */
	 else if (ft_strncmp("C", spl[p->i], 1) && ft_strncmp("F", spl[p->i], 1) &&
			ft_strncmp("NO", spl[p->i], 2) && ft_strncmp("SO", spl[p->i], 2) &&
			ft_strncmp("WE", spl[p->i], 2) && ft_strncmp("EA", spl[p->i], 2) &&
			ft_strncmp("1", spl[p->i], 1))
		free_exit("Error\nInvalid character\n", cub);
}

/* 
	search for NO, SO, WE, EA, S, F elems.
	get wall textures paths and C, F rgb values 
	get the index for last elem and first map line.
	if "1" is found, count1 is incremented. if more than 1 found, error.
	if last elem index is greater than first map index, error.
 */
void	ft_search_elems(t_cube *cub, char **spl)
{
	t_parse	p;

	ft_bzero(&p, sizeof(t_parse));
	while (spl[p.i])
	{
		ft_search_elems_aux(cub, &p, spl);
		/* if (!ft_strncmp("1", spl[i], 1))
		{
			elemidxs[1] = i;
			count1++;
		}
		else if (spl[i + 1] && !ft_strncmp("NO", spl[i], 2))
			ft_save_path(spl[i + 1], i, elemidxs[0], cub->no);
		else if (spl[i + 1] && !ft_strncmp("SO", spl[i], 2))
			ft_save_path(spl[i + 1], i, elemidxs[0], cub->so);
		else if (spl[i + 1] && !ft_strncmp("WE", spl[i], 2))
			ft_save_path(spl[i + 1], i, elemidxs[0], cub->we);
		else if (spl[i + 1] && !ft_strncmp("EA", spl[i], 2))
			ft_save_path(spl[i + 1], i, elemidxs[0], cub->ea);
		else if (spl[i + 1] && !ft_strncmp("F", spl[i], 1))
			ft_save_color(spl[i + 1], i, elemidxs[0], cub->f);
		else if (spl[i + 1] && !ft_strncmp("C", spl[i], 1))
			ft_save_color(spl[i + 1], i, elemidxs[0], cub->c);
		else if (ft_strncmp("C", spl[i], 1) && ft_strncmp("F", spl[i], 1) &&
				ft_strncmp("NO", spl[i], 2) && ft_strncmp("SO", spl[i], 2) &&
				ft_strncmp("WE", spl[i], 2) && ft_strncmp("EA", spl[i], 2) &&
				ft_strncmp("1", spl[i], 1))
			free_exit("Error\nInvalid element\n"); */
		p.i++;
	}
	printf("cube->no: %s\n", cub->no);
	printf("cube->so: %s\n", cub->so);
	printf("cube->we: %s\n", cub->we);
	printf("cube->ea: %s\n", cub->ea);
	printf("cube->f: %i\n", cub->f);
	printf("cube->c: %i\n", cub->c);
	
	//if (p.count1 != 1 || (p.lastelem > p.firstmap))
	free_exit("Error\nInvalid elementsmmmm\n", cub);
}


void	ft_get_elements(t_cube *cub, char *str)
{
	char	**splspa;
	int		i;

	i = 0;	
	splspa = custom_split(str);
	while (splspa[i])
	{
		printf("[%i]%s\n", i, splspa[i]);
		i++;
	}
	ft_search_elems(cub, splspa);
	ft_free_split(splspa);
}

/* 
	*.cub checks:
		- elements first, map last.
		- valid elements in cub file:
			- color for ceiling and floor:
				F 220,100,0 or C 225,30,0 (RGB 0-255)
			-texture for walls:
				NO ./path_to_the_north_texture
				SO ./path_to_the_south_texture
				WE ./path_to_the_west_texture
				EA ./path_to_the_east_texture
		- only 1 player and valid characters (N, S, E, W)
		- surrounded by walls
*/
void	ft_checks(t_cube *cub, int fd)
{
	char	*str;

	str = ft_get_cub(fd);
	ft_get_elements(cub, str);
	/* printf("%s\n", str);
	printf("\n**************\n\n");
	spl = ft_split(str, '\n'); */
	free(str);
}

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
