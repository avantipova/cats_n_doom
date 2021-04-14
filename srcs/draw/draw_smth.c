/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_smth.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetrell <npetrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 20:51:56 by npetrell          #+#    #+#             */
/*   Updated: 2021/04/14 20:52:26 by npetrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duke.h"

void	draw_menu(t_doom *doom)
{
	SDL_Rect rect;
	int step;
	int i;
	int j;

	step = (H) / 5;

	rect.x = -100;
	rect.y = 0;
	rect.w = W + 200;
	rect.h = H;

	SDL_BlitScaled(doom->menu_back, NULL, doom->mgl->screen_surface, NULL);
	rect.y -= step;
	SDL_BlitScaled(doom->menu.play, &rect, doom->mgl->screen_surface, NULL);
	rect.y -= step;
	if (doom->difficulty == 0)
		SDL_BlitScaled(doom->menu.difficulty_1, &rect, doom->mgl->screen_surface, NULL);
	else if (doom->difficulty == 1)
		SDL_BlitScaled(doom->menu.difficulty_2, &rect, doom->mgl->screen_surface, NULL);
	else
		SDL_BlitScaled(doom->menu.difficulty_3, &rect, doom->mgl->screen_surface, NULL);
	rect.y -= step;
	SDL_BlitScaled(doom->menu.exit_b, &rect, doom->mgl->screen_surface, NULL);

	i = -25;
	while (i < 24)
	{
		j = -25;
		while (j < 24)
		{
			put_pixel(doom->mgl->screen_surface->pixels, i - W_2 + 50, -j - (doom->menu.active + 1.5) * step + H_2, 0xcea322);
			j++;
		}
		i++;
	}
}

void	draw_lose(t_doom *doom)
{
	SDL_BlitScaled(doom->lose_surface, NULL,
			doom->mgl->screen_surface, NULL);
}
void	draw_win(t_doom *doom)
{
	SDL_BlitScaled(doom->win_surface, NULL,
			doom->mgl->screen_surface, NULL);
}
void	draw_press_f(t_doom *doom)
{
	SDL_Rect rect;

	rect.x = -400;
	rect.w = 1000;
	rect.y = -500;
	rect.h = 720;
	if (length(sub(doom->tv.sprite.instance.position, 
				doom->scene.camera.position)) < 2.0)
		SDL_BlitScaled(doom->press_f, &rect,
			doom->mgl->screen_surface, NULL);
}
