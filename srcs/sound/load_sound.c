/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_sound.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Chorange <Chorange@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 15:52:40 by mjoss             #+#    #+#             */
/*   Updated: 2021/04/03 01:05:29 by Chorange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mixer_init.h"
#include "libft.h"

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
}
