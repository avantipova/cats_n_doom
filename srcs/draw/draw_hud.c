/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_hud.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetrell <npetrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 20:50:17 by npetrell          #+#    #+#             */
/*   Updated: 2021/04/14 20:50:28 by npetrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duke.h"

void	draw_hud(t_doom *doom)
{
	char str[62];
	char str2[62];
	SDL_Color color;

	color.r = 35;
	color.g = 151;
	color.b = 35;

	ft_strcpy(str, "+ ");
	itoa(doom->health, str2);
	ft_strcat(str, str2);
	
	doom->health_bar = renderText(str, ASSETS_FOLDER_NAME "/fonts/DoomsDay.ttf", color, 50);
	ft_strcpy(str, "||| ");
	itoa(doom->player_ammo, str2);
	ft_strcat(str, str2);
	color.r = 188;
	color.g = 143;
	color.b = 43;
	doom->ammo_bar = renderText(str, ASSETS_FOLDER_NAME "/fonts/DoomsDay.ttf", color, 50);
	ft_strcpy(str, "KILLS ");
	itoa(doom->kills, str2);
	ft_strcat(str, str2);
	
	color.r = 94;
	color.g = 6;
	color.b = 6;
	doom->kills_bar = renderText(str, ASSETS_FOLDER_NAME "/fonts/DoomsDay.ttf", color, 50);

	SDL_Rect rect;

	rect.x = 0;
	rect.y = 0;
	rect.w = W;
	rect.h = H;

	SDL_BlitScaled(doom->health_bar, &rect, doom->mgl->screen_surface, NULL);
	rect.y -= 50;
	SDL_BlitScaled(doom->ammo_bar, &rect, doom->mgl->screen_surface, NULL);
	rect.y = 0;
	rect.x = -W + 200;
	SDL_BlitScaled(doom->kills_bar, &rect, doom->mgl->screen_surface, NULL);
	SDL_FreeSurface(doom->health_bar);
	SDL_FreeSurface(doom->ammo_bar);
	SDL_FreeSurface(doom->kills_bar);


}
