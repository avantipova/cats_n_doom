/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_triangle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetrell <npetrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 16:35:30 by npetrell          #+#    #+#             */
/*   Updated: 2021/04/14 17:34:15 by npetrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duke.h"

void	get_arrays(t_scene *scene, t_triangle *tr, t_model *model)
{
	int	*ids;

	ids = tr->indexes;
	edge_interpolate((t_e_i_input){
		model->projected[ids[0]].y, model->projected[ids[0]].x,
		model->projected[ids[1]].y, model->projected[ids[1]].x,
		model->projected[ids[2]].y, model->projected[ids[2]].x,
	}, scene->render_tr, &scene->render_tr->x);
	edge_interpolate((t_e_i_input){
		model->projected[ids[0]].y, 1.0 / model->vertexes[ids[0]].z,
		model->projected[ids[1]].y, 1.0 / model->vertexes[ids[1]].z,
		model->projected[ids[2]].y, 1.0 / model->vertexes[ids[2]].z,
	}, scene->render_tr, &scene->render_tr->iz);
	edge_interpolate((t_e_i_input){
		model->projected[ids[0]].y, tr->uvs[0].x / model->vertexes[ids[0]].z,
		model->projected[ids[1]].y, tr->uvs[1].x / model->vertexes[ids[1]].z,
		model->projected[ids[2]].y, tr->uvs[2].x / model->vertexes[ids[2]].z,
	}, scene->render_tr, &scene->render_tr->uz);
	edge_interpolate((t_e_i_input){
		model->projected[ids[0]].y, tr->uvs[0].y / model->vertexes[ids[0]].z,
		model->projected[ids[1]].y, tr->uvs[1].y / model->vertexes[ids[1]].z,
		model->projected[ids[2]].y, tr->uvs[2].y / model->vertexes[ids[2]].z,
	}, scene->render_tr, &scene->render_tr->vz);
}

void	transform_arrays(t_scene *scene)
{
	int	m;

	m = (int)(scene->render_tr->x.v02.length / 2);
	if (scene->render_tr->x.v02.array[m] < scene->render_tr->x.v012.array[m])
	{
		scene->render_tr->x_left = &scene->render_tr->x.v02;
		scene->render_tr->x_right = &scene->render_tr->x.v012;
		scene->render_tr->iz_left = &scene->render_tr->iz.v02;
		scene->render_tr->iz_right = &scene->render_tr->iz.v012;
		scene->render_tr->uz_left = &scene->render_tr->uz.v02;
		scene->render_tr->uz_right = &scene->render_tr->uz.v012;
		scene->render_tr->vz_left = &scene->render_tr->vz.v02;
		scene->render_tr->vz_right = &scene->render_tr->vz.v012;
	}
	else
	{
		scene->render_tr->x_left = &scene->render_tr->x.v012;
		scene->render_tr->x_right = &scene->render_tr->x.v02;
		scene->render_tr->iz_left = &scene->render_tr->iz.v012;
		scene->render_tr->iz_right = &scene->render_tr->iz.v02;
		scene->render_tr->uz_left = &scene->render_tr->uz.v012;
		scene->render_tr->uz_right = &scene->render_tr->uz.v02;
		scene->render_tr->vz_left = &scene->render_tr->vz.v012;
		scene->render_tr->vz_right = &scene->render_tr->vz.v02;
	}
}

void	draw_row(int *image_data, t_scene *scene, int y_it, t_triangle *tr)
{
	scene->render_tr->xl = scene->render_tr->x_left->array[(y_it - \
				(int)scene->render_tr->pts[0].y)];
	scene->render_tr->xr = scene->render_tr->x_right->array[(y_it - \
				(int)scene->render_tr->pts[0].y)];
	scene->render_tr->zl = scene->render_tr->iz_left->array[(y_it - \
				(int)scene->render_tr->pts[0].y)];
	scene->render_tr->zr = scene->render_tr->iz_right->array[(y_it - \
				(int)scene->render_tr->pts[0].y)];
	scene->render_tr->uzl = scene->render_tr->uz_left->array[(y_it - \
				(int)scene->render_tr->pts[0].y)];
	scene->render_tr->uzr = scene->render_tr->uz_right->array[(y_it - \
				(int)scene->render_tr->pts[0].y)];
	scene->render_tr->vzl = scene->render_tr->vz_left->array[(y_it - \
				(int)scene->render_tr->pts[0].y)];
	scene->render_tr->vzr = scene->render_tr->vz_right->array[(y_it - \
				(int)scene->render_tr->pts[0].y)];
	scene->render_tr->d_z = get_inter_d(scene->render_tr->xl, \
		scene->render_tr->zl, scene->render_tr->xr, scene->render_tr->zr);
	scene->render_tr->d_u = get_inter_d(scene->render_tr->xl, \
		scene->render_tr->uzl, scene->render_tr->xr, scene->render_tr->uzr);
	scene->render_tr->d_v = get_inter_d(scene->render_tr->xl, \
		scene->render_tr->vzl, scene->render_tr->xr, scene->render_tr->vzr);
	draw_pixel(scene, image_data, tr, y_it);
}

void	render_triangle(int *image_data, t_model *model, \
								t_triangle *tr, t_scene *scene)
{
	int	y_it;

	sort_vertex_indexes(tr, model->projected);
	scene->render_tr->vers[0] = model->vertexes[tr->indexes[0]];
	scene->render_tr->vers[1] = model->vertexes[tr->indexes[1]];
	scene->render_tr->vers[2] = model->vertexes[tr->indexes[2]];
	scene->render_tr->pts[0] = model->projected[tr->indexes[0]];
	scene->render_tr->pts[1] = model->projected[tr->indexes[1]];
	scene->render_tr->pts[2] = model->projected[tr->indexes[2]];
	get_arrays(scene, tr, model);
	transform_arrays(scene);
	y_it = (int)scene->render_tr->pts[0].y;
	while (y_it <= (int)scene->render_tr->pts[2].y)
	{
		draw_row(image_data, scene, y_it, tr);
		y_it++;
	}
}
