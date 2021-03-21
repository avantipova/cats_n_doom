/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_music.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoss <mjoss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 15:53:52 by mjoss             #+#    #+#             */
/*   Updated: 2021/03/21 15:53:52 by mjoss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mixer_init.h"
#include "../libft/libft.h"

void	play_music(Mix_Music *music, int loops)
{
	int status;

	status = Mix_PlayMusic(music, loops);
	if (status < 0)
	{
		ft_putstr("Play music error\n");
		exit(EXIT_FAILURE);
	}
}
