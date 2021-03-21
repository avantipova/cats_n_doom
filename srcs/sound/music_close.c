/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   music_close.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoss <mjoss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 15:53:47 by mjoss             #+#    #+#             */
/*   Updated: 2021/03/21 15:53:47 by mjoss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mixer_init.h"

void	music_close(t_music *music)
{
	Mix_FreeMusic(music->background);
	Mix_FreeChunk(music->shotgun);
	free(music);
	Mix_CloseAudio();
}
