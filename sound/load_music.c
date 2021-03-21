/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_music.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoss <mjoss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 15:53:31 by mjoss             #+#    #+#             */
/*   Updated: 2021/03/21 15:53:31 by mjoss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mixer_init.h"

void	load_music(t_music *music)
{
	Mix_Music	*background;

	background = Mix_LoadMUS(BACKGROUND_MUSIC);
	if (background == NULL)
	{
		ft_putstr("Error load background music\n");
		ft_putstr(Mix_GetError());
		exit(EXIT_FAILURE);
	}
	music->background = background;
}
