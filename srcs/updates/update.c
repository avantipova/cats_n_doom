/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetrell <npetrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 20:46:29 by npetrell          #+#    #+#             */
/*   Updated: 2021/04/14 20:46:44 by npetrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duke.h"

void	update(void *doom_ptr, int *pixels)
{
	t_doom *doom;

	

	doom = (t_doom *)doom_ptr;

	if (doom->menu_opened)
	{
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

	// SDL_PixelFormat *format = SDL_AllocFormat(SDL_PIXELFORMAT_BGRA32);
	// SDL_Surface	*tex = SDL_ConvertSurface(doom->menu_back, format, 0);

	// SDL_FreeSurface(tex);

	// tex = SDL_ConvertSurface(doom->menu_back, format, 0);

	// SDL_FreeSurface(tex);

	// tex = SDL_ConvertSurface(doom->menu_back, format, 0);
	// SDL_FreeSurface(tex);

	// SDL_FreeFormat(format);
	



	pthread_render(pixels, doom);

	//  render_scene(pixels, &doom->scene);

	drb_animation_update(doom);

	draw_hud(doom);

	draw_press_f(doom);

	float speed = 6.0;
	if (doom->sit)
		speed -= 2.0;
	else if (doom->run)
		speed += 4.0;

	float path = (doom->mgl->curr_time - doom->mgl->lst_time) * speed;

	t_vertex new_pos;


	float floor;
	float ceil;
	get_floor_seil_traversal(&doom->scene.level.root,
			(t_vertex){doom->scene.camera.position.x,
			doom->scene.camera.position.z, 0.0}, &floor, &ceil);
	//printf("on_ground %d\n", doom->on_ground);

	doom->on_ground = 0;

	if (!doom->on_ground)
	{
		doom->g_speed += 0.4 * (doom->mgl->curr_time - doom->mgl->lst_time);
	}
	new_pos = (t_vertex)
		{
			doom->scene.camera.position.x,
			doom->scene.camera.position.z,
			doom->scene.camera.position.y - doom->g_speed
		};
	if (if_possible_to_move(new_pos, &doom->scene.level.root,
		PHISICS_MODE_PLAYER, doom->height) || doom->solid)
	{
		doom->scene.camera.position.y -= doom->g_speed;
	}
	else
	{
		doom->g_speed = 0;
	}
	
	

	if (doom->scene.camera.position.y - (doom->height - 0.2) < floor)
	{
		doom->on_ground = 1;
		doom->scene.camera.position.y = doom->height - 0.2 + floor;
		doom->g_speed = 0;
	}


	///doom->scene.camera.position.y = floor + 1.0;

	//printf ("player: %f %f\n", doom->scene.camera.position.x, doom->scene.camera.position.z);

	if (doom->w_pressed)
	{
		new_pos = (t_vertex)
		{
			doom->scene.camera.position.x - path * sin(doom->gamma / 180 * 3.1415),
			doom->scene.camera.position.z,
			doom->scene.camera.position.y
		};
		if (if_possible_to_move(new_pos, &doom->scene.level.root,
			PHISICS_MODE_PLAYER, doom->height) || doom->solid)
		{
			
			doom->scene.camera.position.x = new_pos.x;
		}
		new_pos = (t_vertex)
		{
			doom->scene.camera.position.x,
			doom->scene.camera.position.z + path * cos(doom->gamma / 180 * 3.1415),
			doom->scene.camera.position.y
		};
		if (if_possible_to_move(new_pos, &doom->scene.level.root,
			PHISICS_MODE_PLAYER, doom->height) || doom->solid)
		{
			doom->scene.camera.position.z = new_pos.y;
		}
	}
	if (doom->s_pressed)
	{
		new_pos = (t_vertex)
		{
			doom->scene.camera.position.x + path * sin(doom->gamma / 180 * 3.1415),
			doom->scene.camera.position.z,
			doom->scene.camera.position.y
		};
		if (if_possible_to_move(new_pos, &doom->scene.level.root,
			PHISICS_MODE_PLAYER, doom->height) || doom->solid)
		{
			doom->scene.camera.position.x = new_pos.x;
		}
		new_pos = (t_vertex)
		{
			doom->scene.camera.position.x,
			doom->scene.camera.position.z - path * cos(doom->gamma / 180 * 3.1415),
			doom->scene.camera.position.y
		};
		if (if_possible_to_move(new_pos, &doom->scene.level.root,
			PHISICS_MODE_PLAYER, doom->height) || doom->solid)
		{
			doom->scene.camera.position.z = new_pos.y;
		}
	}
	if (doom->a_pressed)
	{
		new_pos = (t_vertex)
		{
			doom->scene.camera.position.x - path * cos(doom->gamma / 180 * 3.1415),
			doom->scene.camera.position.z,
			doom->scene.camera.position.y
		};
		if (if_possible_to_move(new_pos, &doom->scene.level.root,
			PHISICS_MODE_PLAYER, doom->height) || doom->solid)
		{
			doom->scene.camera.position.x = new_pos.x;
		}
		new_pos = (t_vertex)
		{
			doom->scene.camera.position.x,
			doom->scene.camera.position.z - path * sin(doom->gamma / 180 * 3.1415),
			doom->scene.camera.position.y
		};
		if (if_possible_to_move(new_pos, &doom->scene.level.root,
			PHISICS_MODE_PLAYER, doom->height) || doom->solid)
		{
			doom->scene.camera.position.z = new_pos.y;
		}
	}
	if (doom->d_pressed)
	{
		new_pos = (t_vertex)
		{
			doom->scene.camera.position.x + path * cos(doom->gamma / 180 * 3.1415),
			doom->scene.camera.position.z,
			doom->scene.camera.position.y
		};
		if (if_possible_to_move(new_pos, &doom->scene.level.root,
			PHISICS_MODE_PLAYER, doom->height) || doom->solid)
		{
			doom->scene.camera.position.x = new_pos.x;
		}
		new_pos = (t_vertex)
		{
			doom->scene.camera.position.x,
			doom->scene.camera.position.z + path * sin(doom->gamma / 180 * 3.1415),
			doom->scene.camera.position.y
		};
		if (if_possible_to_move(new_pos, &doom->scene.level.root,
			PHISICS_MODE_PLAYER, doom->height) || doom->solid)
		{
			doom->scene.camera.position.z = new_pos.y;
		}
	}
	if (length(sub((t_vertex){doom->scene.camera.position.x, 0.0,
			doom->scene.camera.position.z}, doom->aim)) < 3.0)
	{
		doom->win = 1;
	}
}
