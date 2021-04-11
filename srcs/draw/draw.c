/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetrell <npetrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 20:23:59 by mjoss             #+#    #+#             */
/*   Updated: 2021/04/11 17:54:51 by npetrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duke.h"

int	classify_point(t_vertex cam, t_vertex line, t_vertex normal)
{
	t_vertex	new;

	cam.z = 0.0;
	normal.z = 0.0;
	new = (t_vertex){cam.x, line.x * cam.x + line.y, 0.0};
	if (dot(sub(new, cam), normal) < 0.0)
		return (BACK);
	return (FRONT);
}

static void	bsp_loop(t_bsp *node, t_scene *scene, \
								t_instance *instance, t_model *model)
{
	int			i;
	t_vertex	centre;
	t_triangle	curr;

	i = -1;
	while (++i < node->vt_trs_count)
	{
		curr.normal = instance->model.normals[node->vt_trs[i].n_ids[0]];
		curr.indexes[0] = node->vt_trs[i].ids[0];
		curr.indexes[1] = node->vt_trs[i].ids[1];
		curr.indexes[2] = node->vt_trs[i].ids[2];
		curr.uvs[0] = instance->model.uvs[node->vt_trs[i].uv_ids[0]];
		curr.uvs[1] = instance->model.uvs[node->vt_trs[i].uv_ids[1]];
		curr.uvs[2] = instance->model.uvs[node->vt_trs[i].uv_ids[2]];
		centre = multiply(sub(instance->model.vertexes[curr.indexes[0]], \
			scene->camera.position), -1.0);
		if (node->vt_trs[i].type == TR_TYPE_WALL)
			curr.tex = instance->model.new_tex[node->wall_tex];
		else if (node->vt_trs[i].type == TR_TYPE_FLOOR)
			curr.tex = instance->model.new_tex[node->floor_tex];
		else
			curr.tex = instance->model.new_tex[node->ceil_tex];
		if (dot(centre, curr.normal) >= 0.0)
			clip_triangle(&curr, scene->clipping_planes, model);
	}
}

void	bsp_render_traversal(t_bsp *node, t_scene *scene, \
								t_instance *instance, t_model *model)
{
	if (node->is_leaf)
	{
		bsp_loop(node, scene, instance, model);
	}
	else
	{
		if (classify_point((t_vertex){scene->camera.position.x, \
			scene->camera.position.z, 0.0}, node->line, node->normal) == FRONT)
		{
			bsp_render_traversal(node->back, scene, instance, model);
			bsp_render_traversal(node->front, scene, instance, model);
		}
		else
		{
			bsp_render_traversal(node->front, scene, instance, model);
			bsp_render_traversal(node->back, scene, instance, model);
		}
	}
}
