/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   welcome_screen.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoss <mjoss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 22:56:58 by mjoss             #+#    #+#             */
/*   Updated: 2021/05/12 22:56:58 by mjoss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duke.h"

void	welcome_screen(t_doom *doom, SDL_Texture **tex)
{
	*tex = SDL_CreateTextureFromSurface(doom->mgl->renderer, doom->open_menu);
	SDL_RenderCopy(doom->mgl->renderer, *tex, NULL, NULL);
	SDL_RenderPresent(doom->mgl->renderer);
}
