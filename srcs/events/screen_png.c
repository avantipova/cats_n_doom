/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen_png.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baylak <baylak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 04:14:08 by baylak            #+#    #+#             */
/*   Updated: 2021/05/07 04:16:41 by baylak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duke.h"

static char	*get_name(int nmb)
{
	char	*tmp;

	tmp = ft_itoa(nmb);
	tmp = ft_strjoin(tmp, "_doom_screenshot.png");
	if (!tmp)
		return (NULL);
	return (tmp);
}

void	screen_png(SDL_Surface *srf, int num)
{
	char	*name;

	name = get_name(num);
	IMG_SavePNG(srf, name);
	free(name);
}
