/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetrell <npetrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 17:42:26 by npetrell          #+#    #+#             */
/*   Updated: 2021/04/11 18:03:37 by npetrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duke.h"

void	render_model(int *image_data, t_model *model, t_scene *scene)
{
	int	i;

	i = 0;
	while (i < model->vertexes_count)
	{
		model->projected[i] = project_vertex(model->vertexes[i]);
		i++;
	}
	i = 0;
	while (i < model->triangles_count)
	{
		render_triangle(image_data, model, &model->triangles[i], scene);
		i++;
	}
}

void	render_level(int *image_data, t_scene *scene, t_mat4x4 camera_mat)
{
	t_mat4x4	transform;
	t_model		*model;

	update_instance_transform(&scene->level.instance);
	transform = multiply_m_m(camera_mat, \
							scene->level.instance.transform);
	model = transform_and_clip(&scene->level.instance, \
										transform, scene, 1);
	if (!model)
	{
		return ;
	}
	scene->depth_mode = 1;
	render_model(image_data, model, scene);
}

void	render_sprites(int *image_data, t_scene *scene, t_mat4x4 camera_mat)
{
	t_mat4x4	transform;
	t_model		*model;
	int			i;

	i = 0;
	while (i < scene->sprites_count)
	{
		update_instance_transform(&scene->sprites[i].instance);
		transform = multiply_m_m(camera_mat, \
								scene->sprites[i].instance.transform);
		model = transform_and_clip(&scene->sprites[i].instance, \
											transform, scene, 0);
		if (!model)
		{
			i++;
			continue ;
		}
		scene->depth_mode = 0;
		render_model(image_data, model, scene);
		i++;
	}
}

void	render_scene(int *image_data, t_scene *scene)
{
	t_mat4x4	camera_mat;

	camera_mat = multiply_m_m(transposed_m(scene->camera.orientation), \
		make_translation_matrix(multiply(scene->camera.position, -1.0)));
	render_level(image_data, scene, camera_mat);
	render_sprites(image_data, scene, camera_mat);
}
