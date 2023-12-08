/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josu <josu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 08:00:06 by imontero          #+#    #+#             */
/*   Updated: 2023/12/08 21:27:40 by josu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cube_bonus.h"

void	ft_collisions(t_data *dt)
{
	if ((dt->info.imap[(int)(dt->pos_dir.posx) - 1][(int)(dt->pos_dir.posy)]
		== 1 && (dt->pos_dir.posx - (int)dt->pos_dir.posx < 0.04))
		|| ((dt->info.imap[(int)(dt->pos_dir.posx) + 1][(int)(dt->pos_dir.posy)]
		== 1 && dt->pos_dir.posx - (int)dt->pos_dir.posx > 0.94))
		|| ((dt->info.imap[(int)(dt->pos_dir.posx)][(int)(dt->pos_dir.posy - 1)]
		== 1 && dt->pos_dir.posy - (int)dt->pos_dir.posy < 0.04))
		|| ((dt->info.imap[(int)(dt->pos_dir.posx)][(int)(dt->pos_dir.posy + 1)]
		== 1 && dt->pos_dir.posy - (int)dt->pos_dir.posy > 0.94)))
		printf("COLLISION!!!\n");
	/* else
		printf("\n"); */
}
