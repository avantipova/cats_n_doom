/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drb_animation_update.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetrell <npetrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 20:47:18 by npetrell          #+#    #+#             */
/*   Updated: 2021/04/24 20:05:50 by npetrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duke.h"

void	drb_animation_update(t_doom *doom)
{
	int			frame;
	SDL_Rect	rect;

	if (doom->drb_anim.curr == -1)
		frame = 0;
	else
	{
		doom->drb_anim.curr_f += doom->drb_anim.speed * \
				(doom->mgl->curr_time - doom->mgl->lst_time);
		frame = (int)(doom->drb_anim.curr_f);
		if (frame >= doom->drb_anim.length)
		{
			doom->drb_anim.curr = -1;
			frame = 0;
		}
		else
			doom->drb_anim.curr = frame;
	}
	rect.x = -64;
	rect.y = -64;
	rect.h = 192;
	rect.w = 192;
	SDL_BlitScaled(doom->drb_anim.frames[frame], \
				&rect, doom->mgl->screen_surface, NULL);
}
