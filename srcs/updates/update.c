/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baylak <baylak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 20:46:29 by npetrell          #+#    #+#             */
/*   Updated: 2021/05/07 04:54:49 by baylak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duke.h"

static void	updates(int *pixels, t_doom *doom)
{
	clear_z_buffer(doom->scene.z_buffer);
	update_bullets(doom);
	update_ammo(doom);
	update_aid(doom);
	update_enemies(doom);
	update_sprites(doom, doom->gamma);
	animation_update(&doom->scene, doom->mgl->curr_time - doom->mgl->lst_time);
	pthread_render(pixels, doom);
	drb_animation_update(doom);
	draw_hud(doom);
	draw_press_f(doom);
}

static void	update_2(t_doom *doom, float *floor_ceil, float path)
{
	t_vertex	new_pos;

	if (!doom->on_ground)
		doom->g_speed += 0.4 * (doom->mgl->curr_time - doom->mgl->lst_time);
	new_pos = (t_vertex) \
	{
		doom->scene.camera.position.x,
		doom->scene.camera.position.z,
		doom->scene.camera.position.y - doom->g_speed
	};
	if (if_possible_to_move(new_pos, &doom->scene.level.root, \
		PHISICS_MODE_PLAYER, doom->height) || doom->solid)
		doom->scene.camera.position.y -= doom->g_speed;
	else
		doom->g_speed = 0;
	if (doom->scene.camera.position.y - (doom->height - 0.2) < floor_ceil[0])
	{
		doom->on_ground = 1;
		doom->scene.camera.position.y = doom->height - 0.2 + floor_ceil[0];
		doom->g_speed = 0;
	}
	doom_pressed(doom, &new_pos, path);
	if (length(sub((t_vertex){doom->scene.camera.position.x, 0.0, \
			doom->scene.camera.position.z}, doom->aim)) < 3.0)
		doom->win = 1;
}

static void	init_traversal(t_doom *doom, float *floor_ceil)
{
	get_floor_seil_traversal(&doom->scene.level.root, \
	(t_vertex) \
	{
		doom->scene.camera.position.x,
		doom->scene.camera.position.z, 0.0
	}, \
	&floor_ceil[0], &floor_ceil[1]);
}

void	update(void *doom_ptr, int *pixels)
{
	t_doom		*doom;
	float		floor_ceil[2];
	float		path;
	float		speed;

	doom = (t_doom *)doom_ptr;
	if (menu_opened(doom) == 0)
		return ;
	doom->for_sprites = make_oy_rot_matrix(doom->gamma);
	doom->scene.camera.orientation = multiply_m_m(doom->for_sprites, \
									make_ox_rot_matrix(doom->alpha));
	ft_bzero(pixels, sizeof(int) * H_W);
	updates(pixels, doom);
	speed = 6.0;
	if (doom->sit)
		speed -= 2.0;
	else if (doom->run)
		speed += 4.0;
	path = (doom->mgl->curr_time - doom->mgl->lst_time) * speed;
	init_traversal(doom, floor_ceil);
	doom->on_ground = 0;
	update_2(doom, floor_ceil, path);
}
