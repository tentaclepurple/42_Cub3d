/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imontero <imontero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 18:26:21 by imontero          #+#    #+#             */
/*   Updated: 2023/11/23 12:24:49 by imontero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cube.h"

static char	**ft_freeall(char **tab, int k)
{
	while (k >= 0)
	{
		free(tab[k]);
		k--;
	}
	free(tab);
	return (NULL);
}

static int	ft_count(char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (s[0] && (s[0] != ' ' || s[0] == '\n'))
	{
		count++;
		i++;
	}
	while (s[i])
	{
		if (s[i] == ' ' || s[i] == '\n')
			i++;
		else if (i != 0 && ((s[i] != ' ' && s[i - 1] == ' ') || ((s[i] != '\n') &&
			(s[i - 1] == '\n'))))
		{
			count++;
			i++;
		}
		else
			i++;
	}
	return (count);
}

static char	**ft_strings(char **tab, char *s)
{
	int	i;
	int	start;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (i == 0 && (s[i] != ' ' || s[i] == '\n'))
			start = 0;
		if (i == 0 && (s[i] == ' ' || s[i] == '\n'))
			i++;
		if (i && (((s[i - 1] == ' ') && (s[i] != ' ')) || ((s[i - 1] == '\n') &&
				(s[i] != '\n'))))
			start = i;
		if ((s[i] != ' ') && ((s[i + 1] == ' ') || ((s[i] != '\n') &&
			((s[i + 1] == '\n') || (s[i + 1] == '\0')))))
		{
			printf("j: %i\n", j);
			tab[j] = ft_substr(s, start, i - start + 1);
			if (!tab[j])
				return (ft_freeall(tab, j - 1));
			j++;
		}
		i++;
	}
	return (tab);
}

char	**ft_split_spnl(char const *s)
{
	int		count;
	char	**tab;

	if (!s)
		return (NULL);
	count = ft_count((char *)s);
	printf("count: %i\n", count);
	tab = malloc(sizeof(char *) * (count + 1));
	if (!tab)
		return (NULL);
	tab[count] = 0;
	return (ft_strings(tab, (char *)s));
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
void	ft_save_path(t_cube *cub, char *path, t_parse *p, char *elem)
{
	int fd;

	printf("[path: %s]\n", path);
	fd = open(path, O_RDONLY);
	printf("fd: %i\n", fd);
	if (ft_strncmp(path + ft_strlen(path) - 4, ".xpm", 4) || fd == -1)
		free_exit("Error\nInvalid pathKKK\n", cub);
	free(elem);
	elem = ft_strdup(path);
	printf("elem: %s\n", elem);
	p->lastelem = p->i;
	
	
}
void	ft_save_color(t_cube *cub, char *path, t_parse *p, char *elem)
{
	(void)cub;
	(void)path;
	(void)p;
	(void)elem;
	p->lastelem = p->i;
	
}

/* 
	search lines starting with "1" or any of the elements. 
	Anythig else is invalid.
 */
void	ft_search_elems_aux(t_cube *cub, t_parse *p, char **spl)
{
	printf("spl[%i]: %s\n", p->i, spl[p->i]);
	if (!ft_strncmp("1", spl[p->i], 1))
		{
			p->firstmap = p->i;
			p->count1++;
		}
	else if (spl[p->i + 1] && !ft_strncmp("NO", spl[p->i], 2))
	{
		printf("i dentro de func: %i\n", p->i);
		ft_save_path(cub, spl[p->i + 1], p, cub->no);
		
	}
	else if (spl[p->i + 1] && !ft_strncmp("SO", spl[p->i], 2))
	{
		ft_save_path(cub, spl[p->i + 1], p, cub->so);
		
	}
	else if (spl[p->i + 1] && !ft_strncmp("WE", spl[p->i], 2))
		ft_save_path(cub, spl[p->i + 1], p, cub->we);
	else if (spl[p->i + 1] && !ft_strncmp("EA", spl[p->i], 2))
		ft_save_path(cub, spl[p->i + 1], p, cub->ea);
	/*else if (spl[p->i + 1] && !ft_strncmp("F", spl[p->i], 1))
		ft_save_color(cub, spl[p->i + 1], p, cub->f);
	else if (spl[p->i + 1] && !ft_strncmp("C", spl[p->i], 1))
		ft_save_color(cub, spl[p->i + 1], p, cub->c);*/
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
		printf("i: %i\n", p.i);
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
	if (p.count1 != 1 || (p.lastelem > p.firstmap))
		free_exit("Error\nInvalid elements\n", cub);
}



void	ft_get_elements(t_cube *cub, char *str)
{
	char	**splspa;
	int		i;

	i = 0;	
	splspa = ft_split_spnl(str);
	while (splspa[i])
	{
		printf("%s\n", splspa[i]);
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
