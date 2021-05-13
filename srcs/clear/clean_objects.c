/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baylak <baylak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 20:53:26 by npetrell          #+#    #+#             */
/*   Updated: 2021/05/13 22:56:16 by baylak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duke.h"

void	clean_anim(t_anim *anim)
{
	int			i;
	SDL_Surface	*ptr;

	i = 0;
	while (i < anim->length)
	{
		ptr = anim->frames[i];
		SDL_FreeSurface(ptr);
		i++;
	}
}

void	clean_enemies(t_doom *doom)
{
	int	i;
	int	j;

	i = 0;
	ft_printf(" count %d\n", doom->enemies_count);
	while (i < doom->enemies_count)
	{
		free(doom->enemies[i].sprite.instance.model.vertexes);
		free(doom->enemies[i].sprite.instance.model.triangles);
		clean_anim(&doom->enemies[i].death_anim);
		clean_anim(&doom->enemies[i].damage_anim);
		clean_anim(&doom->enemies[i].attak_anim);
		j = 0;
		while (j < 8)
		{
			clean_anim(&(doom->enemies[i].walking_anims[j]));
			j++;
		}
		i++;
	}
	doom->enemies_count = 0;
}

void	remove_files(void)
{
	system("rm -rf " ASSETS_FOLDER_NAME);
}
