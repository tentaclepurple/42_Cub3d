/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_spnl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imontero <imontero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 18:20:12 by jzubizar          #+#    #+#             */
/*   Updated: 2023/11/23 12:03:54 by imontero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"

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
		else if (i != 0 && (s[i] != ' ' && s[i - 1] == ' ') || (s[i] != '\n' &&
			s[i - 1] == '\n'))
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

	i = -1;
	j = 0;
	while (s[++i])
	{
		if (i == 0 && (s[i] != ' ' || s[i] == '\n'))
			start = 0;
		if (i == 0 && (s[i] == ' ' || s[i] == '\n'))
			i++;
		if (i && ((s[i - 1] == ' ' && s[i] != ' ') || s[i - 1] == '\n' &&
				s[i] != '\n'))
			start = i;
		if ((s[i] != ' ' && (s[i + 1] == ' ') || (s[i] != '\n' &&
			(s[i + 1] == '\n')) || s[i + 1] == '\0'))
		{
			tab[j] = ft_substr(s, start, i - start + 1);
			if (!tab[j])
				return (ft_freeall(tab, j - 1));
			j++;
		}
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
	tab = malloc(sizeof(char *) * (count + 1));
	if (!tab)
		return (NULL);
	tab[count] = 0;
	return (ft_strings(tab, (char *)s));
}
