/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_enemies.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baylak <baylak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 20:58:06 by npetrell          #+#    #+#             */
/*   Updated: 2021/05/13 23:50:17 by baylak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duke.h"

int	check_enemy(t_doom *doom, t_vertex pos)
{
	int	i;
	int	damage;

	i = 0;
	while (i < doom->enemies_count)
	{
		if (doom->enemies[i].health > 0)
		{
			if (length(sub(doom->enemies[i].sprite.instance.position, \
				pos)) < 1.0)
			{
				damage = 100 / length(sub(doom->scene.camera.position, \
				pos));
				printf("damage: %d\n", damage);
				doom->enemies[i].health -= damage;
				if (doom->enemies[i].health <= 0)
					doom->kills++;
				doom->enemies[i].damage_anim.curr_f = 0.0;
				doom->enemies[i].damaged = 1;
				return (1);
			}
		}
		i++;
	}
	return (0);
}
