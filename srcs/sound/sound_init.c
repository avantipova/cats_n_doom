/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetrell <npetrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 15:54:00 by mjoss             #+#    #+#             */
/*   Updated: 2021/04/29 08:29:42 by maxim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mixer_init.h"
#include "libft.h"
#include <stdlib.h>

t_music	*sound_init(void)
{
	t_music	*music;

	music = (t_music *)malloc(sizeof(t_music));
	if (music == NULL)
	{
		ft_putstr("malloc returns NULL\n");
		exit(EXIT_FAILURE);
	}
	mixer_init();
	load_sound(music);
	load_music(music);
	music->playing_naruto = 0;
	music->playing_tyan = 0;
	return (music);
}
