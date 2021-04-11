/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpolate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetrell <npetrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 21:15:21 by mjoss             #+#    #+#             */
/*   Updated: 2021/04/11 19:02:54 by npetrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duke.h"

void	interpolate(t_e_i_input in, t_float_array *dst)
{
	int		i;
	float	a;
	float	d;

	dst->length = 0;
	if (in.y0 == in.y1)
	{
		dst->length = 1;
		dst->array[0] = in.v0;
		return ;
	}
	dst->length = (int)in.y1 - (int)in.y0 + 1;
	i = 0;
	d = in.v0;
	a = (in.v1 - in.v0) / (in.y1 - in.y0);
	while (i < dst->length)
	{
		dst->array[i] = d;
		d += a;
		i++;
	}
}

float	get_inter_d(float i0, float d0, float i1, float d1)
{
	return ((d1 - d0) / (i1 - i0));
}

void	concat(t_float_array *first, t_float_array *second)
{
	int		length;

	length = first->length + second->length;
	ft_memcpy(first->array + first->length, second->array, \
								sizeof(float) * second->length);
	first->length = length;
	second->length = 0;
}

void	edge_interpolate(t_e_i_input in, t_render *render,
									t_edge_interpolate *edge)
{
	t_e_i_input	tmp;

	tmp.y0 = in.y0;
	tmp.v0 = in.v0;
	tmp.y1 = in.y1;
	tmp.v1 = in.v1;
	interpolate(tmp, &edge->v012);
	tmp.y0 = in.y1;
	tmp.v0 = in.v1;
	tmp.y1 = in.y2;
	tmp.v1 = in.v2;
	interpolate(tmp, &render->v12);
	tmp.y0 = in.y0;
	tmp.v0 = in.v0;
	tmp.y1 = in.y2;
	tmp.v1 = in.v2;
	interpolate(tmp, &edge->v02);
	edge->v012.length -= 1;
	concat(&edge->v012, &render->v12);
}

t_e_i_output	get_edge_inter(t_e_i_input in)
{
	t_e_i_output	out;

	out.v01 = get_inter_d(in.y0, in.v0, in.y1, in.v1);
	out.v12 = get_inter_d(in.y1, in.v1, in.y2, in.v2);
	out.v02 = get_inter_d(in.y0, in.v0, in.y2, in.v2);
	out.limit = in.y1;
	return (out);
}
