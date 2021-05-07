/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sounds_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baylak <baylak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 04:08:50 by baylak            #+#    #+#             */
/*   Updated: 2021/05/07 04:12:52 by baylak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duke.h"

void	sounds_events(t_doom *doom)
{
	if (doom->music->playing_naruto == 0 && \
		length(sub(doom->objects[4].sprite.instance.position,
				   doom->scene.camera.position)) <= 3.0)
	{
		doom->music->playing_naruto = 1;
		if (Mix_PlayChannelTimed(2, doom->music->naruto, 1, 1300) == -1)
			ft_putstr(Mix_GetError());
	}
	else if ((length(sub(doom->objects[4].sprite.instance.position, \
						 doom->scene.camera.position)) > 3.0) && \
						 doom->music->playing_naruto == 1)
		doom->music->playing_naruto = 0;
	if (doom->music->playing_tyan == 0 && \
		length(sub(doom->objects[7].sprite.instance.position,
				   doom->scene.camera.position)) <= 3.0)
	{
		doom->music->playing_tyan = 1;
		if (Mix_PlayChannelTimed(3, doom->music->anime_tyan, 1, 500) == -1)
			ft_putstr(Mix_GetError());
	}
	else if ((length(sub(doom->objects[7].sprite.instance.position, \
						 doom->scene.camera.position)) > 3.0) && \
						 				doom->music->playing_tyan == 1)
		doom->music->playing_tyan = 0;
}

void	event_naruto(t_doom *doom)
{
	if (doom->music->playing_naruto == 0 && \
		length(sub(doom->objects[4].sprite.instance.position,
				   doom->scene.camera.position)) <= 3.0)
	{
		doom->music->playing_naruto = 1;
		if (Mix_PlayChannelTimed(2, doom->music->naruto, 1, 1300) == -1)
			ft_putstr(Mix_GetError());
	}
	else if ((length(sub(doom->objects[4].sprite.instance.position, \
						doom->scene.camera.position)) > 3.0) && \
						 		doom->music->playing_naruto == 1)
		doom->music->playing_naruto = 0;
}
