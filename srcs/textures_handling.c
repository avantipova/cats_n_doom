/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_handling.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetrell <npetrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 16:13:39 by npetrell          #+#    #+#             */
/*   Updated: 2021/04/11 17:07:22 by npetrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duke.h"

static void	anim_initial(t_anim *anim, float speed)
{
	anim->i = -1;
	anim->length = 0;
	anim->speed = speed;
	anim->curr_f = 0.0;
	anim->played = 1;
}

t_anim	load_anim(char *foldername, float speed, int alpha)
{
	t_anim	anim;
	char	str[128];
	char	name[32];

	anim_initial(&anim, speed);
	while (++anim.i < 64)
	{
		ft_strcpy(str, foldername);
		anim.ptr = ft_itoa(anim.i + 1);
		if (ft_strlen(anim.ptr) == 1)
			ft_strcpy(name, "000");
		else if (ft_strlen(anim.ptr) == 2)
			ft_strcpy(name, "00");
		ft_strcat(name, anim.ptr);
		if (anim.ptr)
			free(anim.ptr);
		ft_strcat(name, ".bmp");
		ft_strcat(str, name);
		anim.frames[anim.i] = create_texture(str, alpha);
		if (!anim.frames[anim.i])
			break ;
		anim.frames[anim.i]->flags = alpha;
		anim.length++;
	}
	return (anim);
}

SDL_Surface	*create_texture(char *filename, int alpha)
{
	SDL_Surface		*texture;
	SDL_Surface		*tex;
	SDL_PixelFormat	*format;

	texture = SDL_LoadBMP(filename);
	if (!texture)
	{
		return (NULL);
	}
	format = SDL_AllocFormat(SDL_PIXELFORMAT_BGRA32);
	tex = SDL_ConvertSurface(texture, format, 0);
	puts("mall");
	SDL_SetColorKey(tex, SDL_TRUE, alpha);
	SDL_FreeFormat(format);
	SDL_FreeSurface(texture);
	tex->flags = alpha;
	return (tex);
}
