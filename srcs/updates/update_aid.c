/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_aid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetrell <npetrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 20:45:47 by npetrell          #+#    #+#             */
/*   Updated: 2021/04/24 20:06:22 by npetrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duke.h"

void	update_aid(t_doom *doom)
{
	int	i;

	i = 0;
	while (i < 40)
	{
		if (doom->aid[i].enable)
		{
			if (length(sub(doom->aid[i].sprite.instance.position, \
				doom->scene.camera.position)) < 1.5)
			{
				doom->health += 30;
				printf("health: %d\n", doom->health);
				doom->aid[i].enable = 0;
			}
		}
		i++;
	}
}
