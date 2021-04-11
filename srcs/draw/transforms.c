/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transforms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetrell <npetrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 17:44:50 by npetrell          #+#    #+#             */
/*   Updated: 2021/04/11 17:58:48 by npetrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duke.h"

void	clip_triangles(t_model *model, t_instance *instance,
							t_scene *scene, int lol)
{
	int			i;
	t_triangle	curr;
	t_vertex	centre;

	i = 0;
	while (i < instance->model.triangles_count)
	{
		curr = instance->model.triangles[i];
		centre = multiply(sub(instance->model.vertexes[curr.indexes[0]], \
			scene->camera.position), -1.0);
		curr.tex = instance->model.new_tex[0];
		if (dot(centre, curr.normal) >= 0.0 || lol)
		{
			clip_triangle(&curr, scene->clipping_planes, model);
		}
		i++;
	}
}

int	check_bounds_radius(t_instance *instance, t_scene *scene,
									t_mat4x4 *transform)
{
	t_vertex4	tmp;
	t_vertex	center;
	float		radius2;
	int			i;
	float		distance2;

	radius2 = instance->model.bounds_radius * instance->scale;
	tmp = multiply_m_v(*transform, (t_vertex4){\
									instance->model.bounds_center.x, \
									instance->model.bounds_center.y, \
									instance->model.bounds_center.z, \
									1.0 \
									});
	center = (t_vertex){tmp.x, tmp.y, tmp.z};
	i = 0;
	while (i < 5)
	{
		distance2 = dot(scene->clipping_planes[i].normal, center) + \
							scene->clipping_planes[i].distance;
		if (distance2 < -radius2)
			return (0);
		i++;
	}
	return (1);
}

void	transform_vertexes(t_model *model, t_instance *instance,
								t_mat4x4 *transform)
{
	int			i;
	t_vertex4	tmp;

	i = 0;
	while (i < instance->model.vertexes_count)
	{
		tmp = (t_vertex4){
			instance->model.vertexes[i].x,
			instance->model.vertexes[i].y,
			instance->model.vertexes[i].z,
			1.0
		};
		tmp = multiply_m_v(*transform, tmp);
		model->vertexes[i] = (t_vertex){tmp.x, tmp.y, tmp.z};
		model->vertexes_count++;
		i++;
	}
}

t_model	*transform_and_clip(t_instance *instance, t_mat4x4 transform,
							t_scene *scene, int mode)
{
	t_model	*model;

	model = &scene->render_tr->rendered;
	model->vertexes_count = 0;
	model->triangles_count = 0;
	model->uvs_count = 0;
	if (!check_bounds_radius(instance, scene, &transform))
	{
		return (NULL);
	}
	transform_vertexes(model, instance, &transform);
	if (mode == 1)
		bsp_render_traversal(&scene->level.root, scene, instance, model);
	else
		clip_triangles(model, instance, scene, 1);
	return (model);
}
