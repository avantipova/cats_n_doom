/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_bullets.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetrell <npetrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 20:44:25 by npetrell          #+#    #+#             */
/*   Updated: 2021/04/24 20:45:34 by npetrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duke.h"

static void	instance(t_doom *doom, t_vertex new_pos, int i)
{
	doom->bullets[i].sprite.instance.position.z = new_pos.y;
	doom->bullets[i].sprite.instance.position.x = new_pos.x;
	doom->bullets[i].sprite.instance.position.y = new_pos.z;
}

void	update_bullets(t_doom *doom)
{
	int			i;
	t_vertex	new_pos;
	float		path;

	path = (doom->mgl->curr_time - doom->mgl->lst_time) * 10;
	i = -1;
	while (++i < 40)
	{
		if (doom->bullets[i].enable)
		{
			new_pos = (t_vertex){doom->bullets[i].sprite.instance.position.x - \
							path * sin(doom->bullets[i].gamma / 180 * 3.1415),
				doom->bullets[i].sprite.instance.position.z + \
							path * cos(doom->bullets[i].gamma / 180 * 3.1415),
				doom->bullets[i].sprite.instance.position.y + \
							path * sin(doom->bullets[i].alpha / 180 * 3.1415)};
			if (if_possible_to_move(new_pos, &doom->scene.level.root, \
					PHISICS_MODE_BULLET, 1) || doom->solid)
				instance(doom, new_pos, i);
			else
				doom->bullets[i].enable = 0;
			if (check_enemy(doom, doom->bullets[i].sprite.instance.position))
				doom->bullets[i].enable = 0;
		}
	}
}
