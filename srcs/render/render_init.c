/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetrell <npetrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 17:41:47 by npetrell          #+#    #+#             */
/*   Updated: 2021/04/14 17:52:14 by npetrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duke.h"

void	controls_init(t_doom *doom)
{
	doom->beta = 0.0;
	doom->gamma = 0.0;
	doom->alpha = 0.0;
	doom->w_pressed = 0;
	doom->s_pressed = 0;
	doom->a_pressed = 0;
	doom->d_pressed = 0;
	doom->mouse_pressed = 0;
	doom->mouse_right_pressed = 0;
}

void	clipping_planes_init(t_scene *scene)
{
	float	sins;
	float	coss;

	sins = 1 / sqrt(5);
	coss = sins * 2;
	scene->clipping_planes[0] = (t_plane){(t_vertex){0.0, 0.0, 1.0}, 0.0};
	scene->clipping_planes[1] = (t_plane){(t_vertex){coss, 0.0, sins}, 0.0};
	scene->clipping_planes[2] = (t_plane){(t_vertex){-coss, 0.0, sins}, 0.0};
	scene->clipping_planes[3] = (t_plane){(t_vertex){0.0, -coss, sins}, 0.0};
	scene->clipping_planes[4] = (t_plane){(t_vertex){0.0, coss, sins}, 0.0};
}

static void	render_init_1(t_scene *scene)
{
	scene->s_render_tr.iz.v012.array = malloc(sizeof(float) * H * 20);
	scene->s_render_tr.iz.v02.array = malloc(sizeof(float) * H * 20);
	scene->s_render_tr.uz.v012.array = malloc(sizeof(float) * H * 20);
	scene->s_render_tr.uz.v02.array = malloc(sizeof(float) * H * 20);
	scene->s_render_tr.vz.v012.array = malloc(sizeof(float) * H * 20);
	scene->s_render_tr.vz.v02.array = malloc(sizeof(float) * H * 20);
	scene->s_render_tr.zscan.array = malloc(sizeof(float) * W * 20);
	scene->s_render_tr.uzscan.array = malloc(sizeof(float) * W * 20);
	scene->s_render_tr.vzscan.array = malloc(sizeof(float) * W * 20);
	scene->s_render_tr.v02.array = malloc(sizeof(float) * H * 20);
	scene->s_render_tr.v01.array = malloc(sizeof(float) * H * 20);
	scene->s_render_tr.v12.array = malloc(sizeof(float) * H * 20);
	scene->s_render_tr.rendered.vertexes = malloc(sizeof(t_vertex) * 30000);
	scene->s_render_tr.rendered.projected = malloc(sizeof(t_point) * 30000);
	scene->s_render_tr.rendered.triangles = malloc(sizeof(t_triangle) * 30000);
}

void	render_init(t_scene *scene)
{
	scene->f_render_tr.x.v012.array = malloc(sizeof(float) * H * 20);
	scene->f_render_tr.x.v02.array = malloc(sizeof(float) * H * 20);
	scene->f_render_tr.iz.v012.array = malloc(sizeof(float) * H * 20);
	scene->f_render_tr.iz.v02.array = malloc(sizeof(float) * H * 20);
	scene->f_render_tr.uz.v012.array = malloc(sizeof(float) * H * 20);
	scene->f_render_tr.uz.v02.array = malloc(sizeof(float) * H * 20);
	scene->f_render_tr.vz.v012.array = malloc(sizeof(float) * H * 20);
	scene->f_render_tr.vz.v02.array = malloc(sizeof(float) * H * 20);
	scene->f_render_tr.zscan.array = malloc(sizeof(float) * W * 20);
	scene->f_render_tr.uzscan.array = malloc(sizeof(float) * W * 20);
	scene->f_render_tr.vzscan.array = malloc(sizeof(float) * W * 20);
	scene->f_render_tr.v02.array = malloc(sizeof(float) * H * 20);
	scene->f_render_tr.v01.array = malloc(sizeof(float) * H * 20);
	scene->f_render_tr.v12.array = malloc(sizeof(float) * H * 20);
	scene->f_render_tr.rendered.vertexes = malloc(sizeof(t_vertex) * 30000);
	scene->f_render_tr.rendered.projected = malloc(sizeof(t_point) * 30000);
	scene->f_render_tr.rendered.triangles = malloc(sizeof(t_triangle) * 30000);
	scene->s_render_tr.x.v012.array = malloc(sizeof(float) * H * 20);
	scene->s_render_tr.x.v02.array = malloc(sizeof(float) * H * 20);
	render_init_1(scene);
}
