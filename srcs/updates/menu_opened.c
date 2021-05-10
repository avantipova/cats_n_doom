/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_opened.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baylak <baylak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 03:26:39 by baylak            #+#    #+#             */
/*   Updated: 2021/05/07 03:27:11 by baylak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duke.h"

static int	handler(void (*func)(t_doom *), t_doom *doom)
{
	func(doom);
	return (0);
}

int	menu_opened(t_doom *doom)
{
	SDL_Surface	*haha;
	SDL_Texture	*tex;

	haha = SDL_LoadBMP("/Editor/textures/lol.bmp");
	if (doom->menu_opened)
	{
		if (doom->flag == 0)
		{
			SDL_Delay(2000);
			tex = SDL_CreateTextureFromSurface(doom->mgl->renderer, haha);
			SDL_RenderCopy(doom->mgl->renderer, tex, NULL, NULL);
			SDL_RenderPresent(doom->mgl->renderer);
			SDL_Delay(3000);
			SDL_DestroyTexture(tex);
			doom->flag = 1;
		}
		return (handler(&draw_menu, doom));
	}
	if (doom->lose)
		return (handler(&draw_lose, doom));
	if (doom->win)
		return (handler(&draw_menu, doom));
	return (1);
}
