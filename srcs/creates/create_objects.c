/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_objects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetrell <npetrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 20:48:49 by npetrell          #+#    #+#             */
/*   Updated: 2021/04/14 21:42:50 by npetrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duke.h"

static void	init_objects(t_model *object_model)
{
	object_model->bounds_center = (t_vertex){0.0, 0.0, 0.0};
	object_model->bounds_radius = 3.0;
	object_model->triangles_count = 2;
	object_model->vertexes_count = 4;
	object_model->vertexes = malloc(sizeof(t_vertex) * 4);
	object_model->vertexes[0] = (t_vertex){-1.1, -0.8, 0.0};
	object_model->vertexes[1] = (t_vertex){-1.1, 0.8, 0.0};
	object_model->vertexes[2] = (t_vertex){1.1, 0.8, 0.0};
	object_model->vertexes[3] = (t_vertex){1.1, -0.8, 0.0};
	object_model->triangles = malloc(sizeof(t_triangle) * 2);
	object_model->triangles[0].indexes[0] = 0;
	object_model->triangles[0].indexes[1] = 1;
	object_model->triangles[0].indexes[2] = 2;
	object_model->triangles[1].indexes[0] = 0;
	object_model->triangles[1].indexes[1] = 2;
	object_model->triangles[1].indexes[2] = 3;
	object_model->triangles[0].normal = (t_vertex){0.0, 0.0, 1.0};
	object_model->triangles[1].normal = (t_vertex){0.0, 0.0, 1.0};
	object_model->triangles[0].uvs[0] = (t_point){0.0, 1.0, 0.0};
	object_model->triangles[0].uvs[1] = (t_point){0.0, 0.0, 0.0};
	object_model->triangles[0].uvs[2] = (t_point){1.0, 0.0, 0.0};
	object_model->triangles[1].uvs[0] = (t_point){0.0, 1.0, 0.0};
	object_model->triangles[1].uvs[1] = (t_point){1.0, 0.0, 0.0};
	object_model->triangles[1].uvs[2] = (t_point){1.0, 1.0, 0.0};
}

t_object	create_object(t_vertex pos, int index)
{
	t_object	object;
	t_model		object_model;
	char		str[64];
	char		str2[64];

	init_objects(&object_model);
	ft_strcpy(str, ASSETS_FOLDER_NAME "/textures/sprites/");
	itoa(index, str2);
	ft_strcat(str, str2);
	ft_strcat(str, ".bmp");
	object_model.new_tex[0] = create_texture(str, 0xffff00ff);
	object.sprite.instance.model = object_model;
	object.sprite.instance.scale = 1.0;
	object.sprite.instance.position = pos;
	object.sprite.instance.orientation = make_oy_rot_matrix(0.0);
	object.sprite.instance.model.anim = NULL;
	object.index = index;
	return (object);
}
