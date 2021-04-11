/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetrell <npetrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 17:41:27 by npetrell          #+#    #+#             */
/*   Updated: 2021/04/11 17:41:54 by npetrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duke.h"

void	*pthread_fun(void *ptr)
{
	t_pthread_data	*data;

	data = (t_pthread_data *)ptr;
	render_scene(data->image_data, &data->scene);
	return (NULL);
}

void	pthread_render(int *image_data, t_doom *doom)
{
	t_pthread_data	f;
	t_pthread_data	s;
	pthread_t		thread1;
	pthread_t		thread2;

	f.scene = doom->scene;
	s.scene = doom->scene;
	f.image_data = image_data;
	s.image_data = image_data;
	f.scene.clipping_planes[4] = (t_plane){(t_vertex){0.0, 1.0, 0.0}, 0.0};
	s.scene.clipping_planes[3] = (t_plane){(t_vertex){0.0, -1.0, 0.0}, 0.0};
	f.scene.render_tr = &s.scene.f_render_tr;
	s.scene.render_tr = &s.scene.s_render_tr;
	pthread_create(&(thread1), NULL, pthread_fun, &f);
	pthread_create(&(thread2), NULL, pthread_fun, &s);
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
}
