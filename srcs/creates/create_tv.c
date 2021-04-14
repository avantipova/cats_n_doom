/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetrell <npetrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 20:49:22 by npetrell          #+#    #+#             */
/*   Updated: 2021/04/14 21:46:20 by npetrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duke.h"

static void	init_tv_model(t_model *tv_model)
{
	tv_model->bounds_center = (t_vertex){0.0, 0.0, 0.0};
	tv_model->bounds_radius = 3.0;
	tv_model->triangles_count = 2;
	tv_model->vertexes_count = 4;
	tv_model->vertexes = malloc(sizeof(t_vertex) * 4);
	tv_model->vertexes[0] = (t_vertex){-1.2, -0.8, 0.0};
	tv_model->vertexes[1] = (t_vertex){-1.2, 0.8, 0.0};
	tv_model->vertexes[2] = (t_vertex){1.2, 0.8, 0.0};
	tv_model->vertexes[3] = (t_vertex){1.2, -0.8, 0.0};
	tv_model->triangles = malloc(sizeof(t_triangle) * 2);
	tv_model->triangles[0].indexes[0] = 0;
	tv_model->triangles[0].indexes[1] = 1;
	tv_model->triangles[0].indexes[2] = 2;
	tv_model->triangles[1].indexes[0] = 0;
	tv_model->triangles[1].indexes[1] = 2;
	tv_model->triangles[1].indexes[2] = 3;
	tv_model->triangles[0].normal = (t_vertex){0.0, 0.0, 1.0};
	tv_model->triangles[1].normal = (t_vertex){0.0, 0.0, 1.0};
	tv_model->triangles[0].uvs[0] = (t_point){0.0, 1.0, 0.0};
	tv_model->triangles[0].uvs[1] = (t_point){0.0, 0.0, 0.0};
	tv_model->triangles[0].uvs[2] = (t_point){1.0, 0.0, 0.0};
	tv_model->triangles[1].uvs[0] = (t_point){0.0, 1.0, 0.0};
	tv_model->triangles[1].uvs[1] = (t_point){1.0, 0.0, 0.0};
	tv_model->triangles[1].uvs[2] = (t_point){1.0, 1.0, 0.0};
}

void	create_tv(t_doom *doom)
{
	t_model	tv_model;

	init_tv_model(&tv_model);
	doom->tv.anim = load_anim(ASSETS_FOLDER_NAME "/textures/anim1/", 15.0, 0);
	doom->tv.anim.played = 1;
	doom->tv.sprite.instance.model.anim = &doom->tv.anim;
	doom->tv.anim.curr_f = 0.0;
	doom->tv.sprite.instance.model = tv_model;
	doom->tv.sprite.instance.model.new_tex[0] = doom->tv.anim.frames[0];
	doom->tv.sprite.instance.scale = 1.0;
	doom->tv.sprite.instance.orientation = make_oy_rot_matrix(doom->tv.beta);
	doom->tv.sprite.instance.model.anim = NULL;
}
