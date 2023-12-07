/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_split_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imontero <imontero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 18:20:12 by jzubizar          #+#    #+#             */
/*   Updated: 2023/12/07 19:42:28 by imontero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cube_bonus.h"

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
