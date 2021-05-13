/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baylak <baylak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 20:55:14 by npetrell          #+#    #+#             */
/*   Updated: 2021/05/13 21:47:19 by maxim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duke.h"

void	arrow_keys(t_doom *doom, SDL_Event *event, int value)
{
	if (event->key.keysym.sym == SDLK_w || \
							event->key.keysym.sym == SDLK_UP)
		doom->w_pressed = value;
	else if (event->key.keysym.sym == SDLK_s || \
						event->key.keysym.sym == SDLK_DOWN)
		doom->s_pressed = value;
	else if (event->key.keysym.sym == SDLK_a || \
						event->key.keysym.sym == SDLK_LEFT)
		doom->a_pressed = value;
	else if (event->key.keysym.sym == SDLK_d || \
						event->key.keysym.sym == SDLK_RIGHT)
		doom->d_pressed = value;
}

void	event_hand_1(t_doom *doom, SDL_Event *event)
{
	if (event->type == SDL_MOUSEBUTTONDOWN)
		fire(doom);
	else if (event->type == SDL_MOUSEBUTTONUP)
	{
		doom->mouse_pressed = 0;
		doom->mouse_right_pressed = 0;
	}
	else if (event->type == SDL_MOUSEMOTION)
	{
		doom->gamma -= (event->motion.xrel) * 0.5;
		doom->alpha -= (event->motion.yrel) * 0.5;
		doom->prev_x = event->motion.xrel;
		doom->prev_y = event->motion.yrel;
	}
	else if (event->type == SDL_KEYDOWN)
		key_down_src(doom, event);
	else if (event->type == SDL_KEYUP)
	{
		if (event->key.keysym.sym == SDLK_LSHIFT)
			doom->run = 0;
		else
			arrow_keys(doom, event, 0);
	}
	sounds_events(doom);
}

void	event_hand(SDL_Event *event, void *doom_ptr, int *quit)
{
	t_doom		*doom;
	int			return_doom_menu;

	doom = (t_doom *)doom_ptr;
	return_doom_menu = doom_menu(event, doom, quit);
	if (return_doom_menu == 0)
		return ;
	if (doom->win || doom->lose)
	{
		doom->lose = 0;
		doom->win = 0;
		doom->menu_opened = 1;
		restart(doom);
	}
	event_hand_1(doom, event);
}
