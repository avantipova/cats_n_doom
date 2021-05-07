/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_down.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baylak <baylak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 04:11:29 by baylak            #+#    #+#             */
/*   Updated: 2021/05/07 04:29:03 by baylak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duke.h"

static void	key_down_3(t_doom *doom, SDL_Event *event)
{
	if (event->key.keysym.sym == SDLK_h)
	{
		if (doom->solid)
			doom->solid = 0;
		else
			doom->solid = 1;
	}
	else if (event->key.keysym.sym == SDLK_p)
	{
		doom->screen_nmb++;
		ft_putstr("Saved image in png");
		screen_png(doom->mgl->screen_surface, doom->screen_nmb);
	}
	else
		arrow_keys(doom, event, 1);
}

static void	key_down_2(t_doom *doom, SDL_Event *event, t_vertex new_pos)
{
	if (event->key.keysym.sym == SDLK_c)
	{
		if (doom->sit == 0)
		{
			doom->run = 0;
			doom->sit = 1;
			doom->height = 1.1;
		}
		else
		{
			new_pos = (t_vertex) \
			{
				doom->scene.camera.position.x, doom->scene.camera.position.z, \
				doom->scene.camera.position.y + 0.6
			};
			if (if_possible_to_move(new_pos, &doom->scene.level.root, \
			PHISICS_MODE_PLAYER, 1.7))
			{
				doom->sit = 0;
				doom->height = 1.7;
			}
		}
	}
	else
		key_down_3(doom, event);
}

static void	key_down_1(t_doom *doom, SDL_Event *event)
{
	t_vertex	new_pos;

	if (event->key.keysym.sym == SDLK_LSHIFT)
	{
		new_pos = (t_vertex) \
		{
			doom->scene.camera.position.x, \
			doom->scene.camera.position.z, \
			doom->scene.camera.position.y + 0.6, \
		};
		if (if_possible_to_move(new_pos, &doom->scene.level.root, \
			PHISICS_MODE_PLAYER, 1.7))
		{
			doom->sit = 0;
			doom->height = 1.7;
			doom->run = 1;
			doom->height = 1.7;
		}
	}
	else
		key_down_2(doom, event, (t_vertex){0, 0, 0});
}

void	key_down_src(t_doom *doom, SDL_Event *event)
{
	if (event->key.keysym.sym == SDLK_f)
	{
		if (length(sub(doom->tv.sprite.instance.position, \
			doom->scene.camera.position)) < 2.0)
		{
			if (doom->tv.enable)
				doom->tv.enable = 0;
			else
				doom->tv.enable = 1;
		}					
	}
	else if (event->key.keysym.sym == SDLK_ESCAPE)
		doom->menu_opened = 1;
	else if (event->key.keysym.sym == SDLK_SPACE)
	{
		if (doom->on_ground)
			doom->g_speed -= 0.1;
	}
	else
		key_down_1(doom, event);
}
