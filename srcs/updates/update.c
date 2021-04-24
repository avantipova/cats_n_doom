/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetrell <npetrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 20:46:29 by npetrell          #+#    #+#             */
/*   Updated: 2021/04/24 22:25:04 by npetrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duke.h"

static void	doom_pressed(t_doom *doom, t_vertex *new_pos, float path)
{
	if (doom->w_pressed)
	{
		*new_pos = (t_vertex){ \
			doom->scene.camera.position.x - path * sin(doom->gamma / 180 * 3.1415),
			doom->scene.camera.position.z,
			doom->scene.camera.position.y};
		if (if_possible_to_move(*new_pos, &doom->scene.level.root,
			PHISICS_MODE_PLAYER, doom->height) || doom->solid)
			doom->scene.camera.position.x = new_pos->x;
		*new_pos = (t_vertex){ \
			doom->scene.camera.position.x,
			doom->scene.camera.position.z + path * cos(doom->gamma / 180 * 3.1415),
			doom->scene.camera.position.y};
		if (if_possible_to_move(*new_pos, &doom->scene.level.root,
			PHISICS_MODE_PLAYER, doom->height) || doom->solid)
			doom->scene.camera.position.z = new_pos->y;
	}
	if (doom->s_pressed)
	{
		*new_pos = (t_vertex){ \
			doom->scene.camera.position.x + path * sin(doom->gamma / 180 * 3.1415),
			doom->scene.camera.position.z,
			doom->scene.camera.position.y};
		if (if_possible_to_move(*new_pos, &doom->scene.level.root,
			PHISICS_MODE_PLAYER, doom->height) || doom->solid)
			doom->scene.camera.position.x = new_pos->x;
		*new_pos = (t_vertex){ \
			doom->scene.camera.position.x,
			doom->scene.camera.position.z - path * cos(doom->gamma / 180 * 3.1415),
			doom->scene.camera.position.y};
		if (if_possible_to_move(*new_pos, &doom->scene.level.root,
			PHISICS_MODE_PLAYER, doom->height) || doom->solid)
			doom->scene.camera.position.z = new_pos->y;
	}
	if (doom->a_pressed)
	{
		*new_pos = (t_vertex){ \
			doom->scene.camera.position.x - path * cos(doom->gamma / 180 * 3.1415),
			doom->scene.camera.position.z,
			doom->scene.camera.position.y};
		if (if_possible_to_move(*new_pos, &doom->scene.level.root,
			PHISICS_MODE_PLAYER, doom->height) || doom->solid)
			doom->scene.camera.position.x = new_pos->x;
		*new_pos = (t_vertex){ \
			doom->scene.camera.position.x,
			doom->scene.camera.position.z - path * sin(doom->gamma / 180 * 3.1415),
			doom->scene.camera.position.y};
		if (if_possible_to_move(*new_pos, &doom->scene.level.root,
			PHISICS_MODE_PLAYER, doom->height) || doom->solid)
			doom->scene.camera.position.z = new_pos->y;
	}
	if (doom->d_pressed)
	{
		*new_pos = (t_vertex){ \
			doom->scene.camera.position.x + path * cos(doom->gamma / 180 * 3.1415),
			doom->scene.camera.position.z,
			doom->scene.camera.position.y};
		if (if_possible_to_move(*new_pos, &doom->scene.level.root,
			PHISICS_MODE_PLAYER, doom->height) || doom->solid)
			doom->scene.camera.position.x = new_pos->x;
		*new_pos = (t_vertex){ \
			doom->scene.camera.position.x,
			doom->scene.camera.position.z + path * sin(doom->gamma / 180 * 3.1415),
			doom->scene.camera.position.y};
		if (if_possible_to_move(*new_pos, &doom->scene.level.root,
			PHISICS_MODE_PLAYER, doom->height) || doom->solid)
			doom->scene.camera.position.z = new_pos->y;
	}
}

void	update(void *doom_ptr, int *pixels)
{
	t_doom *doom;
	t_vertex new_pos;
	float floor;
	float ceil;
	float path;
	SDL_Surface *haha;

	haha = SDL_LoadBMP("/Editor/textures/lol.bmp");
	doom = (t_doom *)doom_ptr;
	if (doom->menu_opened)
	{
		if (doom->flag == 0)
		{
			SDL_Delay(2000);
			SDL_Texture *tex = SDL_CreateTextureFromSurface(doom->mgl->renderer, haha);
			SDL_RenderCopy(doom->mgl->renderer, tex, NULL, NULL);
			SDL_RenderPresent(doom->mgl->renderer);
			SDL_Delay(3000);
			SDL_DestroyTexture(tex);

			doom->flag = 1;
		}
		draw_menu(doom);
		return;
	}
	if (doom->lose)
	{
		draw_lose(doom);
		return ;
	}
	if (doom->win)
	{
		draw_win(doom);
		return ;
	}
	doom->for_sprites = make_oy_rot_matrix(doom->gamma);
	doom->scene.camera.orientation = multiply_m_m(doom->for_sprites,
												make_ox_rot_matrix(doom->alpha));
	ft_bzero(pixels, sizeof(int) * HxW);
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
	float speed = 6.0;
	if (doom->sit)
		speed -= 2.0;
	else if (doom->run)
		speed += 4.0;
	path = (doom->mgl->curr_time - doom->mgl->lst_time) * speed;
	get_floor_seil_traversal(&doom->scene.level.root,
			(t_vertex){doom->scene.camera.position.x,
			doom->scene.camera.position.z, 0.0}, &floor, &ceil);
	doom->on_ground = 0;
	if (!doom->on_ground)
	{
		doom->g_speed += 0.4 * (doom->mgl->curr_time - doom->mgl->lst_time);
	}
	new_pos = (t_vertex){ \
		doom->scene.camera.position.x,
		doom->scene.camera.position.z,
		doom->scene.camera.position.y - doom->g_speed };
	if (if_possible_to_move(new_pos, &doom->scene.level.root,
		PHISICS_MODE_PLAYER, doom->height) || doom->solid)
		doom->scene.camera.position.y -= doom->g_speed;
	else
		doom->g_speed = 0;
	if (doom->scene.camera.position.y - (doom->height - 0.2) < floor)
	{
		doom->on_ground = 1;
		doom->scene.camera.position.y = doom->height - 0.2 + floor;
		doom->g_speed = 0;
	}
	doom_pressed(doom, &new_pos, path);
	if (length(sub((t_vertex){doom->scene.camera.position.x, 0.0,
			doom->scene.camera.position.z}, doom->aim)) < 3.0)
		doom->win = 1;
}
