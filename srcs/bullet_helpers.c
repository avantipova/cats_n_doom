/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bullet_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetrell <npetrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 20:59:32 by npetrell          #+#    #+#             */
/*   Updated: 2021/04/24 21:57:08 by npetrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duke.h"

int	find_place_for_bullet(t_doom *doom)
{
	int	i;

	i = 0;
	while (i < 40)
	{
		if (!doom->bullets[i].enable)
			return (i);
		i++;
	}
	return (-1);
}

void	fire(t_doom *doom)
{
	int	index;

	if (doom->drb_anim.curr != -1 || doom->player_ammo == 0)
		return ;
	index = find_place_for_bullet(doom);
	if (index != -1)
	{
		doom->bullets[index].sprite.instance.position.x = \
	doom->scene.camera.position.x - 0.2 * sin(doom->gamma / 180 * 3.1415);
		doom->bullets[index].sprite.instance.position.z = \
	doom->scene.camera.position.z + 0.2 * cos(doom->gamma / 180 * 3.1415);
		doom->bullets[index].sprite.instance.position.y = \
											doom->scene.camera.position.y;
		doom->bullets[index].first = \
					doom->bullets[index].sprite.instance.position;
		doom->bullets[index].gamma = doom->gamma;
		doom->bullets[index].alpha = doom->alpha;
		doom->bullets[index].enable = 1;
		doom->player_ammo--;
		printf("ammo: %d\n", doom->player_ammo);
	}
	doom->drb_anim.curr = 0;
	doom->drb_anim.curr_f = 0.0;
	if (Mix_PlayChannelTimed(1, doom->music->shotgun, 1, 500) == -1)
		ft_putstr(Mix_GetError());
}
