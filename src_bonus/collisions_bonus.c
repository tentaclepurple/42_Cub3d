/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzubizar <jzubizar@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 08:00:06 by imontero          #+#    #+#             */
/*   Updated: 2023/12/10 20:04:31 by jzubizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cube_bonus.h"

void	ft_collisions(t_data *dt)
{
	static int	i = 0;
	
	if ((dt->info.imap[(int)(dt->pos_dir.posx) - 1][(int)(dt->pos_dir.posy)]
		> 0 && (dt->pos_dir.posx - (int)dt->pos_dir.posx < 0.04))
		|| ((dt->info.imap[(int)(dt->pos_dir.posx) + 1][(int)(dt->pos_dir.posy)]
		> 0 && dt->pos_dir.posx - (int)dt->pos_dir.posx > 0.94))
		|| ((dt->info.imap[(int)(dt->pos_dir.posx)][(int)(dt->pos_dir.posy - 1)]
		> 0 && dt->pos_dir.posy - (int)dt->pos_dir.posy < 0.04))
		|| ((dt->info.imap[(int)(dt->pos_dir.posx)][(int)(dt->pos_dir.posy + 1)]
		> 0 && dt->pos_dir.posy - (int)dt->pos_dir.posy > 0.94)))
		printf("COLLISION Nº%i!!!\n", ++i);
}
