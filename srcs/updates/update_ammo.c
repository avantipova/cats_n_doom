/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_ammo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetrell <npetrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 20:45:05 by npetrell          #+#    #+#             */
/*   Updated: 2021/04/24 20:06:37 by npetrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duke.h"

void	update_ammo(t_doom *doom)
{
	int	i;

	i = 0;
	while (i < 40)
	{
		if (doom->ammo[i].enable)
		{
			if (length(sub(doom->ammo[i].sprite.instance.position, \
				doom->scene.camera.position)) < 1.5)
			{
				doom->player_ammo += 10;
				printf("ammo: %d\n", doom->player_ammo);
				doom->ammo[i].enable = 0;
			}
		}
		i++;
	}
}
