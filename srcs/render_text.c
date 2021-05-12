/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_text.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoss <mjoss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 22:58:01 by mjoss             #+#    #+#             */
/*   Updated: 2021/05/12 22:58:01 by mjoss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duke.h"

void	render_text(t_doom *doom)
{
	SDL_Surface	*temp;
	SDL_Color	color;
	SDL_Rect	rect;

	color.r = 35;
	color.g = 151;
	color.b = 35;
	rect.x = -200;
	rect.y = -100;
	rect.w = W + 400;
	rect.h = H + 200;
	temp = renderText("WIN", ASSETS_FOLDER_NAME \
						"/fonts/DoomsDay.ttf", color, 300);
	SDL_BlitScaled(temp, &rect, doom->win_surface, NULL);
	color.r = 94;
	color.g = 6;
	color.b = 6;
	SDL_FreeSurface(temp);
	temp = renderText("LOSE", ASSETS_FOLDER_NAME \
						"/fonts/DoomsDay.ttf", color, 300);
	SDL_BlitScaled(temp, &rect, doom->lose_surface, NULL);
	SDL_FreeSurface(temp);
}
