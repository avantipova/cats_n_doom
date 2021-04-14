/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drb_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetrell <npetrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 20:32:54 by npetrell          #+#    #+#             */
/*   Updated: 2021/04/14 20:33:18 by npetrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duke.h"

void	drb_init(t_doom *doom)
{
	doom->drb_anim = load_anim(ASSETS_FOLDER_NAME "/textures/drb/", 15, 0xff00ffff);
	
	doom->drb_anim.curr = -1;
}
