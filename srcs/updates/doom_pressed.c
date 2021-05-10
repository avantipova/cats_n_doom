/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_pressed.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baylak <baylak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 03:29:05 by baylak            #+#    #+#             */
/*   Updated: 2021/05/07 03:42:57 by baylak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duke.h"

void	w_pressed(t_doom *doom, t_vertex *new_pos, float path)
{
	if (doom->w_pressed)
	{
		*new_pos = (t_vertex)
		{
			doom->scene.camera.position.x - path * \
								sin(doom->gamma / 180 * 3.1415),
			doom->scene.camera.position.z,
			doom->scene.camera.position.y
		};
		if (if_possible_to_move(*new_pos, &doom->scene.level.root, \
			PHISICS_MODE_PLAYER, doom->height) || doom->solid)
			doom->scene.camera.position.x = new_pos->x;
		*new_pos = (t_vertex) \
		{
			doom->scene.camera.position.x,
			doom->scene.camera.position.z + path * \
								cos(doom->gamma / 180 * 3.1415),
			doom->scene.camera.position.y
		};
		if (if_possible_to_move(*new_pos, &doom->scene.level.root, \
			PHISICS_MODE_PLAYER, doom->height) || doom->solid)
			doom->scene.camera.position.z = new_pos->y;
	}
}

void	s_pressed(t_doom *doom, t_vertex *new_pos, float path)
{
	if (doom->s_pressed)
	{
		*new_pos = (t_vertex) \
		{
			doom->scene.camera.position.x + \
				path * sin(doom->gamma / 180 * 3.1415),
			doom->scene.camera.position.z,
			doom->scene.camera.position.y
		};
		if (if_possible_to_move(*new_pos, &doom->scene.level.root, \
			PHISICS_MODE_PLAYER, doom->height) || doom->solid)
			doom->scene.camera.position.x = new_pos->x;
		*new_pos = (t_vertex) \
		{
			doom->scene.camera.position.x,
			doom->scene.camera.position.z - \
				path * cos(doom->gamma / 180 * 3.1415),
			doom->scene.camera.position.y
		};
		if (if_possible_to_move(*new_pos, &doom->scene.level.root, \
			PHISICS_MODE_PLAYER, doom->height) || doom->solid)
			doom->scene.camera.position.z = new_pos->y;
	}
}

void	a_pressed(t_doom *doom, t_vertex *new_pos, float path)
{
	if (doom->a_pressed)
	{
		*new_pos = (t_vertex) \
		{
			doom->scene.camera.position.x - \
				path * cos(doom->gamma / 180 * 3.1415),
			doom->scene.camera.position.z,
			doom->scene.camera.position.y
		};
		if (if_possible_to_move(*new_pos, &doom->scene.level.root, \
			PHISICS_MODE_PLAYER, doom->height) || doom->solid)
			doom->scene.camera.position.x = new_pos->x;
		*new_pos = (t_vertex)
		{
			doom->scene.camera.position.x,
			doom->scene.camera.position.z - \
				path * sin(doom->gamma / 180 * 3.1415),
			doom->scene.camera.position.y
		};
		if (if_possible_to_move(*new_pos, &doom->scene.level.root, \
			PHISICS_MODE_PLAYER, doom->height) || doom->solid)
			doom->scene.camera.position.z = new_pos->y;
	}
}

void	d_pressed(t_doom *doom, t_vertex *new_pos, float path)
{
	if (doom->d_pressed)
	{
		*new_pos = (t_vertex)
		{
			doom->scene.camera.position.x + \
				path * cos(doom->gamma / 180 * 3.1415),
			doom->scene.camera.position.z,
			doom->scene.camera.position.y
		};
		if (if_possible_to_move(*new_pos, &doom->scene.level.root, \
			PHISICS_MODE_PLAYER, doom->height) || doom->solid)
			doom->scene.camera.position.x = new_pos->x;
		*new_pos = (t_vertex)
		{
			doom->scene.camera.position.x,
			doom->scene.camera.position.z + \
				path * sin(doom->gamma / 180 * 3.1415),
			doom->scene.camera.position.y
		};
		if (if_possible_to_move(*new_pos, &doom->scene.level.root, \
			PHISICS_MODE_PLAYER, doom->height) || doom->solid)
			doom->scene.camera.position.z = new_pos->y;
	}
}

void	doom_pressed(t_doom *doom, t_vertex *new_pos, float path)
{
	w_pressed(doom, new_pos, path);
	s_pressed(doom, new_pos, path);
	a_pressed(doom, new_pos, path);
	d_pressed(doom, new_pos, path);
}
