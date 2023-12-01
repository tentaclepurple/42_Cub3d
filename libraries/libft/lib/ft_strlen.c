/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imontero <imontero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 19:11:59 by jzubizar          #+#    #+#             */
/*   Updated: 2023/11/24 19:57:16 by imontero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
/*
#include<stdio.h>
#include<string.h>

int	main(int argc, char **argv)
{
	if (argc == 2)
	{
		printf("mine: %lu\n", ft_strlen(argv[1]));
		printf("orig: %lu\n", strlen(argv[1]));
	}
	return (0);
}*/
