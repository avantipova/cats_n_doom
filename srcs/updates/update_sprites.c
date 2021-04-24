/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_sprites.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetrell <npetrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 20:41:08 by npetrell          #+#    #+#             */
/*   Updated: 2021/04/24 22:00:51 by npetrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duke.h"

static void	sprite_change_2(t_doom *doom, t_sprite *sprite, int i, float gamma)
{
	int			d;
	int			my;
	int			him;

	if (doom->enemies[i].in_attak)
	{
		sprite->instance.model.anim = &doom->enemies[i].attak_anim;
		if ((int)sprite->instance.model.anim->curr_f >= \
						sprite->instance.model.anim->length - 1)
			doom->enemies[i].in_attak = 0;
	}
	else
	{
		my = ((int)gamma + 22) % 360;
		if (my < 0)
			my += 360;
		him = ((int)(doom->enemies[i].beta)) % 360;
		if (him < 0)
			him += 360;
		d = (my - him);
		if (d < 0)
			d += 360;
		d /= 45;
		sprite->instance.model.anim = &doom->enemies[i].walking_anims[d];
	}
}

static void	sprite_change(t_doom *doom, t_sprite *sprite, int i, float gamma)
{
	if (doom->enemies[i].damaged && doom->enemies[i].health <= 0)
	{
		sprite->instance.model.anim = &doom->enemies[i].death_anim;
		if ((int)sprite->instance.model.anim->curr_f >= \
						sprite->instance.model.anim->length - 1)
		{
			sprite->instance.model.anim->played = 0;
			sprite->instance.model.new_tex[0] = \
							doom->enemies[i].death_anim.frames[5];
		}
	}
	else if (doom->enemies[i].damaged)
	{
		sprite->instance.model.anim = &doom->enemies[i].damage_anim;
		if ((int)sprite->instance.model.anim->curr_f >= \
						sprite->instance.model.anim->length - 1)
			doom->enemies[i].damaged = 0;
	}
	else
		sprite_change_2(doom, sprite, i, gamma);
}

static void	update_sprites_3(t_doom *doom)
{
	int			i;

	i = -1;
	while (++i < doom->objects_count)
	{
		doom->scene.sprites[doom->scene.sprites_count] = \
														doom->objects[i].sprite;
		doom->scene.sprites[doom->scene.sprites_count].instance.orientation = \
					doom->for_sprites;
		doom->scene.sprites_count++;
	}
	doom->scene.sprites[doom->scene.sprites_count] = doom->tv.sprite;
	if (doom->tv.enable)
		doom->scene.sprites[doom->scene.sprites_count].instance.model.anim = \
																&doom->tv.anim;
	else
	{
		doom->scene.sprites[doom->scene.sprites_count].instance.model.anim = \
																		NULL;
		doom->scene.sprites[doom->scene.sprites_count].instance.model.new_tex[0] = \
				doom->tv.anim.frames[(int)doom->tv.anim.curr_f % \
													doom->tv.anim.length];
	}
	doom->scene.sprites_count++;
}

static void	update_sprites_2(t_doom *doom)
{
	int			i[2];

	i[0] = -1;
	while (++i[0] < 40)
	{
		if (doom->ammo[i[0]].enable)
		{
			i[1] = doom->scene.sprites_count;
			doom->scene.sprites[i[1]] = doom->ammo[i[0]].sprite;
			doom->scene.sprites[i[1]].instance.orientation = doom->for_sprites;
			doom->scene.sprites_count++;
		}
	}
	i[0] = -1;
	while (++i[0] < 40)
	{
		if (doom->aid[i[0]].enable)
		{
			i[1] = doom->scene.sprites_count;
			doom->scene.sprites[i[1]] = doom->aid[i[0]].sprite;
			doom->scene.sprites[i[1]].instance.orientation = doom->for_sprites;
			doom->scene.sprites_count++;
		}
	}
	update_sprites_3(doom);
}

void	update_sprites(t_doom *doom, float gamma)
{
	int			i[2];
	t_sprite	sprite;

	i[0] = -1;
	doom->scene.sprites_count = 0;
	while (++i[0] < doom->enemies_count)
	{
		sprite = doom->enemies[i[0]].sprite;
		sprite_change(doom, &sprite, i[0], gamma);
		sprite.instance.orientation = doom->for_sprites;
		doom->scene.sprites[i[0]] = sprite;
		doom->scene.sprites_count++;
	}
	i[0] = -1;
	while (++i[0] < 40)
	{
		if (doom->bullets[i[0]].enable)
		{
			i[1] = doom->scene.sprites_count;
			doom->scene.sprites[i[1]] = doom->bullets[i[0]].sprite;
			doom->scene.sprites[i[1]].instance.orientation = doom->for_sprites;
			doom->scene.sprites_count++;
		}
	}
	update_sprites_2(doom);
}
