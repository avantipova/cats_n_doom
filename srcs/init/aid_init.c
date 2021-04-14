/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aid_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetrell <npetrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 20:19:50 by npetrell          #+#    #+#             */
/*   Updated: 2021/04/14 20:21:57 by npetrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duke.h"

void	aid_init(t_doom *doom)
{
	t_model aid_model;
	t_aid aid;
	int i;
	
	aid_model.bounds_center = (t_vertex) {0.0,0.0,0.0};
	aid_model.bounds_radius = 2.0;
	aid_model.triangles_count = 2;
	aid_model.vertexes_count = 4;

	aid_model.vertexes = malloc(sizeof(t_vertex) * 4);

	aid_model.vertexes[0] = (t_vertex) {-0.2,-0.2,0.0};
	aid_model.vertexes[1] = (t_vertex) {-0.2,0.2,0.0};
	aid_model.vertexes[2] = (t_vertex) {0.2,0.2,0.0};
	aid_model.vertexes[3] = (t_vertex) {0.2,-0.2,0.0};

	aid_model.triangles = malloc(sizeof(t_triangle) * 2);
	aid_model.triangles[0].indexes[0] = 0;
	aid_model.triangles[0].indexes[1] = 1;
	aid_model.triangles[0].indexes[2] = 2;

	aid_model.triangles[1].indexes[0] = 0;
	aid_model.triangles[1].indexes[1] = 2;
	aid_model.triangles[1].indexes[2] = 3;

	aid_model.triangles[0].normal = (t_vertex) {0.0,0.0,1.0};
	aid_model.triangles[1].normal = (t_vertex) {0.0,0.0,1.0};

	aid_model.triangles[0].uvs[0] = (t_point) {0.0, 1.0,0.0};
	aid_model.triangles[0].uvs[1] = (t_point) {0.0, 0.0,0.0};
	aid_model.triangles[0].uvs[2] = (t_point) {1.0, 0.0,0.0};

	aid_model.triangles[1].uvs[0] = (t_point) {0.0, 1.0,0.0};
	aid_model.triangles[1].uvs[1] = (t_point) {1.0, 0.0,0.0};
	aid_model.triangles[1].uvs[2] = (t_point) {1.0, 1.0,0.0};

	aid_model.new_tex[0] = create_texture(ASSETS_FOLDER_NAME "/textures/aid.bmp", 0xff00feff);
	aid_model.new_tex[0]->flags = 0xff00feff;

	aid_model.anim = NULL;
	
	aid.sprite.instance.model = aid_model;
	aid.sprite.instance.scale = 2.0;
	aid.enable = 0;
	aid.start_enable = 0;

	aid.sprite.instance.orientation = make_oy_rot_matrix(0.0);

	i = 0;
	while (i < 40)
	{
		doom->aid[i] = aid;
		i++;
	}
}
