/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ammo_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetrell <npetrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 20:22:13 by npetrell          #+#    #+#             */
/*   Updated: 2021/04/24 22:19:41 by npetrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duke.h"

static void	init(t_model *ammo_model)
{
	ammo_model->bounds_center = (t_vertex){0.0, 0.0, 0.0};
	ammo_model->bounds_radius = 2.0;
	ammo_model->triangles_count = 2;
	ammo_model->vertexes_count = 4;
	ammo_model->vertexes = malloc(sizeof(t_vertex) * 4);
	ammo_model->vertexes[0] = (t_vertex){-0.2, -0.2, 0.0};
	ammo_model->vertexes[1] = (t_vertex){-0.2, 0.2, 0.0};
	ammo_model->vertexes[2] = (t_vertex){0.2, 0.2, 0.0};
	ammo_model->vertexes[3] = (t_vertex){0.2, -0.2, 0.0};
	ammo_model->triangles = malloc(sizeof(t_triangle) * 2);
	ammo_model->triangles[0].indexes[0] = 0;
	ammo_model->triangles[0].indexes[1] = 1;
	ammo_model->triangles[0].indexes[2] = 2;
	ammo_model->triangles[1].indexes[0] = 0;
	ammo_model->triangles[1].indexes[1] = 2;
	ammo_model->triangles[1].indexes[2] = 3;
	ammo_model->triangles[0].normal = (t_vertex){0.0, 0.0, 1.0};
	ammo_model->triangles[1].normal = (t_vertex){0.0, 0.0, 1.0};
	ammo_model->triangles[0].uvs[0] = (t_point){0.0, 1.0, 0.0};
	ammo_model->triangles[0].uvs[1] = (t_point){0.0, 0.0, 0.0};
	ammo_model->triangles[0].uvs[2] = (t_point){1.0, 0.0, 0.0};
	ammo_model->triangles[1].uvs[0] = (t_point){0.0, 1.0, 0.0};
	ammo_model->triangles[1].uvs[1] = (t_point){1.0, 0.0, 0.0};
	ammo_model->triangles[1].uvs[2] = (t_point){1.0, 1.0, 0.0};
}

void	ammo_init(t_doom *doom)
{
	t_model	ammo_model;
	t_ammo	ammo;
	int		i;

	init(&ammo_model);
	ammo_model.new_tex[0] = create_texture(ASSETS_FOLDER_NAME \
							"/textures/ammo.bmp", 0xff00feff);
	ammo_model.new_tex[0]->flags = 0xff00feff;
	ammo_model.anim = NULL;
	ammo.sprite.instance.model = ammo_model;
	ammo.sprite.instance.scale = 2.0;
	ammo.enable = 0;
	ammo.sprite.instance.orientation = make_oy_rot_matrix(0.0);
	ammo.start_enable = 0;
	i = 0;
	while (i < 40)
	{
		doom->ammo[i] = ammo;
		i++;
	}
}
