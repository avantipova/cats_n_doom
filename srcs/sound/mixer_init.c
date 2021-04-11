/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mixer_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetrell <npetrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 15:53:38 by mjoss             #+#    #+#             */
/*   Updated: 2021/04/11 19:25:43 by npetrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mixer_init.h"
#include "../libft/libft.h"

void	mixer_init(void)
{
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, \
						CHANNELS, CHUNK_SIZE) < 0)
	{
		ft_putstr("Mixer open audio error\n");
		exit(EXIT_FAILURE);
	}
}
