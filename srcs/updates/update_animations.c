/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_animations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetrell <npetrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 20:42:58 by npetrell          #+#    #+#             */
/*   Updated: 2021/04/14 20:43:22 by npetrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duke.h"

void	animation_update(t_scene *scene, float curr_time)
{
	int i;
	int frame;

	i = 0;
	while (i < scene->sprites_count)
	{
		if (!scene->sprites[i].instance.model.anim || !scene->sprites[i].instance.model.anim->played)
		{
			i++;
			continue ;
		}
		
		scene->sprites[i].instance.model.anim->curr_f += scene->sprites[i].instance.model.anim->speed * curr_time;


		frame = (int)(scene->sprites[i].instance.model.anim->curr_f)
				% scene->sprites[i].instance.model.anim->length;

		if (frame < 0)
			frame = 0;
		scene->sprites[i].instance.model.new_tex[0] =
				scene->sprites[i].instance.model.anim->frames[frame];
		i++;
	}
}
