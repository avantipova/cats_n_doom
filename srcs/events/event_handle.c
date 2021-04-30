/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetrell <npetrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 20:55:14 by npetrell          #+#    #+#             */
/*   Updated: 2021/04/30 22:06:09 by maxim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duke.h"

void	event_hand(SDL_Event *event, void *doom_ptr, int *quit)
{
	t_doom *doom;

	doom = (t_doom *)doom_ptr;

	if (doom->menu_opened)
	{
		if (event->type == SDL_KEYDOWN)
		{
			if (event->key.keysym.sym == SDLK_w || event->key.keysym.sym == SDLK_UP)
			{
				doom->menu.active--;
				if (doom->menu.active < 0)
					doom->menu.active = 2;
			}
			else if (event->key.keysym.sym == SDLK_s || event->key.keysym.sym == SDLK_DOWN)
			{
				doom->menu.active++;
				if (doom->menu.active > 2)
					doom->menu.active = 0;
			}
			else if (event->key.keysym.sym == SDLK_RETURN)
			{
				if (doom->menu.active == 0)
					doom->menu_opened = 0;
				else if (doom->menu.active == 1)
				{
					doom->difficulty++;
					if (doom->difficulty > 2)
						doom->difficulty = 0;

					if (doom->difficulty == 0)
					{
						doom->enemy_damage = 10;
						doom->enemy_speed = 0.04;
					}
					else if (doom->difficulty == 1)
					{
						doom->enemy_damage = 20;
						doom->enemy_speed = 0.07;
					}
					else
					{
						doom->enemy_damage = 30;
						doom->enemy_speed = 0.1;
					}
					
				}
				else if (doom->menu.active == 2) //////выход (наеврно надо сделать отдельную функцию на это)
				{
					remove_files();
					*quit = 1;
					exit(-2);
				}
			}
			else if (event->key.keysym.sym == SDLK_ESCAPE) ///////выход (наеврно надо сделать отдельную функцию на это)
			{
				remove_files();
				*quit = 1;
				exit(-2);
			}
		}
		return ;
	}

	if (doom->win || doom->lose)
	{
		if (event->type == SDL_KEYDOWN && event->key.keysym.sym == SDLK_RETURN)
		{
			doom->lose = 0;
			doom->win = 0;
			doom->menu_opened = 1;
			restart(doom);
		}
		return ;
	}

	if (event->type == SDL_MOUSEBUTTONDOWN)
	{

		fire(doom);
	}
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
	else if (event->type == SDL_KEYDOWN )
	{
		if (event->key.keysym.sym == SDLK_f)
		{
			if (length(sub(doom->tv.sprite.instance.position, 
				doom->scene.camera.position)) < 2.0)
			{
				doom->tv.enable = doom->tv.enable ? 0 : 1;
			}					
		}
		else if (event->key.keysym.sym == SDLK_ESCAPE)
		{
			doom->menu_opened = 1;
		}
		else if (event->key.keysym.sym == SDLK_SPACE)
		{
			if (doom->on_ground)
				doom->g_speed -= 0.1;
		}
		else if (event->key.keysym.sym == SDLK_LSHIFT)
		{
			t_vertex new_pos = (t_vertex)
				{
					doom->scene.camera.position.x,
					doom->scene.camera.position.z,
					doom->scene.camera.position.y + 0.6,
				};
			if (if_possible_to_move(new_pos, &doom->scene.level.root,
				PHISICS_MODE_PLAYER, 1.7))
			{
				doom->sit = 0;
				doom->height = 1.7;
				doom->run = 1;
				doom->height = 1.7;
			}
			
		}
		else if (event->key.keysym.sym == SDLK_c)
		{
			if (doom->sit == 0)
			{
				doom->run = 0;
				doom->sit = 1;
				doom->height = 1.1;
			}
			else
			{
				t_vertex new_pos = (t_vertex)
					{
						doom->scene.camera.position.x,
						doom->scene.camera.position.z,
						doom->scene.camera.position.y + 0.6,
					};
				if (if_possible_to_move(new_pos, &doom->scene.level.root,
					PHISICS_MODE_PLAYER, 1.7))
				{
					doom->sit = 0;
					doom->height = 1.7;
				}
			}
		}
		else if (event->key.keysym.sym == SDLK_h)
		{
			doom->solid = (doom->solid ? 0 : 1);
		}
		else if (event->key.keysym.sym == SDLK_w  || event->key.keysym.sym == SDLK_UP)
		{
			doom->w_pressed = 1;
		}
		else if (event->key.keysym.sym == SDLK_s || event->key.keysym.sym == SDLK_DOWN)
		{
			doom->s_pressed = 1;
		}
		else if (event->key.keysym.sym == SDLK_a  || event->key.keysym.sym == SDLK_LEFT)
		{
			doom->a_pressed = 1;
		}
		else if (event->key.keysym.sym == SDLK_d  || event->key.keysym.sym == SDLK_RIGHT)
		{
			doom->d_pressed = 1;
		}
	}
	else if (event->type == SDL_KEYUP)
	{
		if (event->key.keysym.sym == SDLK_w  || event->key.keysym.sym == SDLK_UP)
		{
			doom->w_pressed = 0;
		}
		else if (event->key.keysym.sym == SDLK_s || event->key.keysym.sym == SDLK_DOWN)
		{
			doom->s_pressed = 0;
		}
		else if (event->key.keysym.sym == SDLK_a || event->key.keysym.sym == SDLK_LEFT)
		{
			doom->a_pressed = 0;
		}
		else if (event->key.keysym.sym == SDLK_d || event->key.keysym.sym == SDLK_RIGHT)
		{
			doom->d_pressed = 0;
		}
		else if (event->key.keysym.sym == SDLK_LSHIFT)
		{
			doom->run = 0;
		}
	}
	if (doom->music->playing_naruto == 0 &&
		length(sub(doom->objects[4].sprite.instance.position,
				   doom->scene.camera.position)) <= 3.0)
	{
		doom->music->playing_naruto = 1;
		if (Mix_PlayChannelTimed(2, doom->music->naruto, 1, 1300) == -1)
		{
			ft_putstr(Mix_GetError());
		}
	}
	else if ((length(sub(doom->objects[4].sprite.instance.position,
						 doom->scene.camera.position)) > 3.0) && doom->music->playing_naruto == 1)
	{
		doom->music->playing_naruto = 0;
	}

	if (doom->music->playing_tyan == 0 &&
		length(sub(doom->objects[7].sprite.instance.position,
				   doom->scene.camera.position)) <= 3.0)
	{
		doom->music->playing_tyan = 1;
		if (Mix_PlayChannelTimed(3, doom->music->anime_tyan, 1, 500) == -1)
		{
			ft_putstr(Mix_GetError());
		}
	}
	else if ((length(sub(doom->objects[7].sprite.instance.position,
						 doom->scene.camera.position)) > 3.0) && doom->music->playing_tyan == 1)
	{
		doom->music->playing_tyan = 0;
	}
}
