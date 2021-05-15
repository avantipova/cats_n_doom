/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_aid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baylak <baylak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 20:45:47 by npetrell          #+#    #+#             */
/*   Updated: 2021/05/15 15:24:28 by mjoss            ###   ########.fr       */
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
				doom->aid[i].enable = 0;
			}
		}
		i++;
	}
}
