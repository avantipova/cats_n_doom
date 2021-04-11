/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_music.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetrell <npetrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 15:53:52 by mjoss             #+#    #+#             */
/*   Updated: 2021/04/11 19:25:21 by npetrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mixer_init.h"
#include "../libft/libft.h"

void	play_music(Mix_Music *music, int loops)
{
	int	status;

	status = Mix_PlayMusic(music, loops);
	if (status < 0)
	{
		ft_putstr("Play music error\n");
		exit(EXIT_FAILURE);
	}
}
