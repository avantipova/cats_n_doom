/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clip_triangle_by_planes.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetrell <npetrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 20:15:24 by mjoss             #+#    #+#             */
/*   Updated: 2021/04/11 17:39:09 by npetrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duke.h"

static void	classify_vertexes_2(t_clip_triangle *cl, \
								t_model *model, int k, int i)
{
	if (dot(cl->planes[k].normal, model->vertexes[cl->crop[k][i].indexes[1]]) + \
											cl->planes[k].distance < 0)
	{
		cl->outsides[cl->outside_count] = 1;
		cl->outside_count++;
	}
	else
	{
		cl->insides[cl->inside_count] = 1;
		cl->inside_count++;
	}
	if (dot(cl->planes[k].normal, model->vertexes[cl->crop[k][i].indexes[2]]) + \
											cl->planes[k].distance < 0)
	{
		cl->outsides[cl->outside_count] = 2;
		cl->outside_count++;
	}
	else
	{
		cl->insides[cl->inside_count] = 2;
		cl->inside_count++;
	}
}

void	classify_vertexes(t_clip_triangle *cl, t_model *model, int k, int i)
{
	if (dot(cl->planes[k].normal, model->vertexes[cl->crop[k][i].indexes[0]]) + \
											cl->planes[k].distance < 0)
	{
		cl->outsides[cl->outside_count] = 0;
		cl->outside_count++;
	}
	else
	{
		cl->insides[cl->inside_count] = 0;
		cl->inside_count++;
	}
	classify_vertexes_2(cl, model, k, i);
}

int	clip_tr(t_clip_triangle *cl, t_model *model, int k, int i)
{
	cl->outside_count = 0;
	cl->inside_count = 0;
	classify_vertexes(cl, model, k, i);
	if (cl->outside_count > 2)
	{
		return (0);
	}
	else if (cl->outside_count == 0)
	{
		cl->crop[k + 1][cl->l] = cl->crop[k][i];
		cl->l++;
	}
	else if (cl->outside_count == 2)
	{
		clip_2_outsides(cl, model, k, i);
	}
	else if (cl->outside_count == 1)
	{
		clip_1_outside(cl, model, k, i);
	}
	return (1);
}

void	clip_triangle_2(t_model *model, t_clip_triangle cl, int l_prev)
{
	int	r;

	r = 0;
	while (r < l_prev)
	{
		model->triangles[model->triangles_count] = cl.crop[5][r];
		model->triangles[model->triangles_count].used = r;
		model->triangles_count++;
		r++;
	}
}

void	clip_triangle(t_triangle *trs, t_plane *planes, t_model *model)
{
	int				k;
	int				i;
	t_clip_triangle	cl;
	int				l_prev;

	cl.crop[0][0] = trs[0];
	cl.planes = planes;
	l_prev = 1;
	k = -1;
	while (++k < 5)
	{	
		i = 0;
		cl.l = 0;
		while (i < l_prev)
		{
			if (!clip_tr(&cl, model, k, i))
			{
				i++;
				continue ;
			}
			i++;
		}
		l_prev = cl.l;
	}
	clip_triangle_2(model, cl, l_prev);
}
