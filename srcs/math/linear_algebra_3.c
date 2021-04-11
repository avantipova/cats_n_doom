/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linear_algebra_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetrell <npetrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 19:06:47 by npetrell          #+#    #+#             */
/*   Updated: 2021/04/11 19:20:20 by npetrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"
#include "linear_algebra.h"
#include "duke.h"

t_vertex	add(t_vertex v1, t_vertex v2)
{
	return ((t_vertex){
		v1.x + v2.x,
		v1.y + v2.y,
		v1.z + v2.z
	});
}

float	length(t_vertex vec)
{
	return (sqrt(dot(vec, vec)));
}

t_vertex	triangle_normal(t_vertex v0, t_vertex v1, t_vertex v2)
{
	t_vertex	v0v1;
	t_vertex	v0v2;
	t_vertex	tmp;

	tmp = multiply(v0, -1.0);
	v0v1 = add(v1, tmp);
	v0v2 = add(v2, tmp);
	return (normalize(cross(v0v1, v0v2)));
}

float	sqr(float a)
{
	return (a * a);
}
