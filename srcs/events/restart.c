/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restart.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetrell <npetrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 20:56:17 by npetrell          #+#    #+#             */
/*   Updated: 2021/04/14 20:56:25 by npetrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duke.h"

void	restart(t_doom *doom)
{
	doom->health = 100;
	doom->player_ammo = 10;
	doom->kills = 0;
	doom->drb_anim.curr_f = 0.0;
	doom->drb_anim.curr = -1;

	doom->scene.camera.position = doom->start_pos;
	
	int i;
	i = 0;
	while (i < 40)
	{
		doom->ammo[i].enable = doom->ammo[i].start_enable;
		doom->bullets[i].enable = 0;
		doom->aid[i].enable = doom->aid[i].start_enable;
		i++;
	}
	i = 0;
	while (i < doom->enemies_count)
	{
		doom->enemies[i].sprite.instance.position = doom->enemies[i].start_pos;
		doom->enemies[i].health = 100;
		i++;
	}
	
	controls_init(doom);
	// clean_enemies(doom);
	// clear_bsp(&doom->scene.level.root);
	// read_bsp(doom, "bsp_test/new_saved_bsp.json");
}
