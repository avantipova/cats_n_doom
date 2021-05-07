/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baylak <baylak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 04:14:49 by baylak            #+#    #+#             */
/*   Updated: 2021/05/07 04:25:06 by baylak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duke.h"

static void	set_param(t_doom *doom, float enemy_damage, float enemy_speed)
{
	doom->enemy_damage = enemy_damage;
	doom->enemy_speed = enemy_speed;
}

static void	sdlk_return(t_doom *doom, int *quit)
{
	if (doom->menu.active == 0)
		doom->menu_opened = 0;
	else if (doom->menu.active == 1)
	{
		doom->difficulty++;
		if (doom->difficulty > 2)
			doom->difficulty = 0;
		if (doom->difficulty == 0)
			set_param(doom, 10, 0.04);
		else if (doom->difficulty == 1)
			set_param(doom, 20, 0.07);
		else
			set_param(doom, 30, 0.1);
	}
	else if (doom->menu.active == 2)
	{
		remove_files();
		*quit = 1;
		exit(-2);
	}
}

static void	doom_menu_1(SDL_Event *event, t_doom *doom, int *quit)
{
	if (event->key.keysym.sym == SDLK_RETURN)
		sdlk_return(doom, quit);
	else if (event->key.keysym.sym == SDLK_ESCAPE)
	{
		remove_files();
		*quit = 1;
		exit(-2);
	}
}

int	doom_menu(SDL_Event *event, t_doom *doom, int *quit)
{
	if (doom->menu_opened)
	{
		if (event->type == SDL_KEYDOWN)
		{
			if (event->key.keysym.sym == SDLK_w || \
								event->key.keysym.sym == SDLK_UP)
			{
				doom->menu.active--;
				if (doom->menu.active < 0)
					doom->menu.active = 2;
			}
			else if (event->key.keysym.sym == SDLK_s || \
								event->key.keysym.sym == SDLK_DOWN)
			{
				doom->menu.active++;
				if (doom->menu.active > 2)
					doom->menu.active = 0;
			}
			else
				doom_menu_1(event, doom, quit);
		}
		return (0);
	}
	return (1);
}
