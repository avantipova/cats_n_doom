/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_text.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetrell <npetrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 20:57:40 by npetrell          #+#    #+#             */
/*   Updated: 2021/04/24 22:02:43 by npetrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duke.h"

SDL_Surface	*renderText(char *message, char *font_file,
	SDL_Color color, int fontSize)
{
	SDL_Surface	*surf;
	TTF_Font	*font;

	font = TTF_OpenFont(font_file, fontSize);
	if (font == NULL)
	{
		puts("TTF_OpenFontError");
		return (NULL);
	}
	surf = TTF_RenderText_Blended(font, message, color);
	TTF_CloseFont(font);
	return (surf);
}
