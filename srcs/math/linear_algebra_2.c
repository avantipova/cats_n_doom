/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linear_algebra_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetrell <npetrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 19:06:18 by npetrell          #+#    #+#             */
/*   Updated: 2021/04/11 19:19:43 by npetrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"
#include "linear_algebra.h"
#include "duke.h"

t_vertex	multiply(t_vertex vec, float k)
{
	return ((t_vertex){vec.x * k, vec.y * k, vec.z * k});
}

float	dot(t_vertex v1, t_vertex v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vertex	normalize(t_vertex v)
{
	return (multiply(v, 1.0 / length(v)));
}

t_vertex	sub(t_vertex v1, t_vertex v2)
{
	return ((t_vertex){
		v1.x - v2.x,
		v1.y - v2.y,
		v1.z - v2.z
	});
}

t_vertex	cross(t_vertex v1, t_vertex v2)
{
	return ((t_vertex){\
		v1.y * v2.z - v1.z * v2.y,
		v1.z * v2.x - v1.x * v2.z,
		v1.x * v2.y - v1.y * v2.x
	});
}
