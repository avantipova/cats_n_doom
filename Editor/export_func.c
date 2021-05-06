/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreicher <sreicher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 18:11:06 by sreicher          #+#    #+#             */
/*   Updated: 2021/05/06 18:25:33 by sreicher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

float new_less_zero(t_vertex base, t_vertex new)
{
	double	angle1;
	
	angle1 = acosf(dot(base, new));
	if (cross(base, new).z < 0.0)
		angle1 = 2 * M_PI - angle1;
	return (angle1);
}

float end_less_zero(t_vertex base, t_vertex end)
{
	double	angle2;
	
	angle2 = acosf(dot(base, end));
	if (cross(base, end).z < 0.0)
		angle2 = 2 * M_PI - angle2;
	return (angle2);
}