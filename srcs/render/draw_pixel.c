/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pixel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetrell <npetrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 17:30:38 by npetrell          #+#    #+#             */
/*   Updated: 2021/04/14 17:31:29 by npetrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duke.h"

static int	check_texel(t_triangle *tr, t_uv *data_uv, \
								t_scene *scene, float *inv_z)
{
	if (tr->tex->flags)
	{
		if (get_texel(tr->tex, data_uv->u / *inv_z, \
									data_uv->v / *inv_z) == (int)tr->tex->flags)
		{
			data_uv->x_it++;
			*inv_z += scene->render_tr->d_z;
			data_uv->u += scene->render_tr->d_u;
			data_uv->v += scene->render_tr->d_v;
			return (1);
		}
	}
	return (0);
}

static int	init_draw_pixel(float *inv_z, t_scene *scene, t_uv *data_uv)
{
	int		x_it;

	*inv_z = scene->render_tr->zl;
	data_uv->u = scene->render_tr->uzl;
	data_uv->v = scene->render_tr->vzl;
	x_it = (int)scene->render_tr->xl;
	return (x_it);
}

void	draw_pixel(t_scene *scene, int *image_data, t_triangle *tr, int y_it)
{
	float	inv_z;
	t_uv	data_uv;

	data_uv.x_it = init_draw_pixel(&inv_z, scene, &data_uv);
	while (data_uv.x_it <= (int)scene->render_tr->xr)
	{
		if (check_texel(tr, &data_uv, scene, &inv_z) == 1)
			continue ;
		if (scene->depth_mode)
		{
			if (set_z_buffer_bsp(scene->z_buffer, data_uv.x_it, y_it, inv_z))
				put_pixel(image_data, data_uv.x_it, y_it, \
				get_texel(tr->tex, data_uv.u / inv_z, data_uv.v / inv_z));
		}
		else
		{
			if (set_z_buffer(scene->z_buffer, data_uv.x_it, y_it, inv_z))
				put_pixel(image_data, data_uv.x_it, y_it, \
				get_texel(tr->tex, data_uv.u / inv_z, data_uv.v / inv_z));
		}
		data_uv.x_it++;
		inv_z += scene->render_tr->d_z;
		data_uv.u += scene->render_tr->d_u;
		data_uv.v += scene->render_tr->d_v;
	}
}
