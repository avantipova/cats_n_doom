/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_sound.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldeirdre <ldeirdre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 15:52:40 by mjoss             #+#    #+#             */
/*   Updated: 2021/05/15 16:36:59 by mjoss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mixer_init.h"
#include "libft.h"

static void	load_naruto(t_music *music)
{
	Mix_Chunk	*naruto;

	naruto = Mix_LoadWAV(NARUTO_SOUND);
	if (naruto == NULL)
	{
		ft_putstr("Error load naruto sound\n");
		ft_putstr(Mix_GetError());
		exit(EXIT_FAILURE);
	}
	Mix_VolumeChunk(naruto, MIX_MAX_VOLUME);
	music->naruto = naruto;
}

static void	load_anime_tyan(t_music *music)
{
	Mix_Chunk	*anime_tyan;

	anime_tyan = Mix_LoadWAV(ANIME_TYAN);
	if (anime_tyan == NULL)
	{
		ft_putstr("Error load anime_tyan sound\n");
		ft_putstr(Mix_GetError());
		exit(EXIT_FAILURE);
	}
	Mix_VolumeChunk(anime_tyan, MIX_MAX_VOLUME);
	music->anime_tyan = anime_tyan;
}

void	load_sound(t_music *music)
{
	Mix_Chunk	*shotgun;

	shotgun = Mix_LoadWAV(SHOTGUN_SOUND);
	if (shotgun == NULL)
	{
		ft_putstr("Error load shotgun sound\n");
		ft_putstr(Mix_GetError());
		exit(EXIT_FAILURE);
	}
	music->shotgun = shotgun;
	load_naruto(music);
	load_anime_tyan(music);
}
