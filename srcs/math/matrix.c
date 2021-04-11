/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetrell <npetrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 19:08:12 by npetrell          #+#    #+#             */
/*   Updated: 2021/04/11 19:21:13 by npetrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"
#include "linear_algebra.h"
#include "duke.h"

t_mat4x4	make_oy_rot_matrix(float degrees)
{
	float		sinus;
	float		cosinus;
	t_mat4x4	mat;

	sinus = sin(degrees * 3.1415f / 180.0f);
	cosinus = cos(degrees * 3.1415f / 180.0f);
	mat.mat[0][0] = cosinus;
	mat.mat[0][1] = 0;
	mat.mat[0][2] = -sinus;
	mat.mat[0][3] = 0;
	mat.mat[1][0] = 0;
	mat.mat[1][1] = 1;
	mat.mat[1][2] = 0;
	mat.mat[1][3] = 0;
	mat.mat[2][0] = sinus;
	mat.mat[2][1] = 0;
	mat.mat[2][2] = cosinus;
	mat.mat[2][3] = 0;
	mat.mat[3][0] = 0;
	mat.mat[3][1] = 0;
	mat.mat[3][2] = 0;
	mat.mat[3][3] = 1;
	return (mat);
}

t_mat4x4	make_ox_rot_matrix(float degrees)
{
	float		sinus;
	float		cosinus;
	t_mat4x4	mat;

	sinus = sin(degrees * 3.1415f / 180.0f);
	cosinus = cos(degrees * 3.1415f / 180.0f);
	mat.mat[0][0] = 1;
	mat.mat[0][1] = 0;
	mat.mat[0][2] = 0;
	mat.mat[0][3] = 0;
	mat.mat[1][0] = 0;
	mat.mat[1][1] = cosinus;
	mat.mat[1][2] = sinus;
	mat.mat[1][3] = 0;
	mat.mat[2][0] = 0;
	mat.mat[2][1] = -sinus;
	mat.mat[2][2] = cosinus;
	mat.mat[2][3] = 0;
	mat.mat[3][0] = 0;
	mat.mat[3][1] = 0;
	mat.mat[3][2] = 0;
	mat.mat[3][3] = 1;
	return (mat);
}

t_mat4x4	make_translation_matrix(t_vertex translation)
{
	t_mat4x4	mat;

	mat.mat[0][0] = 1;
	mat.mat[0][1] = 0;
	mat.mat[0][2] = 0;
	mat.mat[0][3] = translation.x;
	mat.mat[1][0] = 0;
	mat.mat[1][1] = 1;
	mat.mat[1][2] = 0;
	mat.mat[1][3] = translation.y;
	mat.mat[2][0] = 0;
	mat.mat[2][1] = 0;
	mat.mat[2][2] = 1;
	mat.mat[2][3] = translation.z;
	mat.mat[3][0] = 0;
	mat.mat[3][1] = 0;
	mat.mat[3][2] = 0;
	mat.mat[3][3] = 1;
	return (mat);
}

t_mat4x4	make_scaling_matrix(float scale)
{
	t_mat4x4	mat;

	mat.mat[0][0] = scale;
	mat.mat[0][1] = 0;
	mat.mat[0][2] = 0;
	mat.mat[0][3] = 0;
	mat.mat[1][0] = 0;
	mat.mat[1][1] = scale;
	mat.mat[1][2] = 0;
	mat.mat[1][3] = 0;
	mat.mat[2][0] = 0;
	mat.mat[2][1] = 0;
	mat.mat[2][2] = scale;
	mat.mat[2][3] = 0;
	mat.mat[3][0] = 0;
	mat.mat[3][1] = 0;
	mat.mat[3][2] = 0;
	mat.mat[3][3] = 1;
	return (mat);
}

t_mat4x4	transposed_m(t_mat4x4 mat)
{
	t_mat4x4	result;
	int			i;
	int			j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			result.mat[i][j] = mat.mat[j][i];
			j++;
		}
		i++;
	}
	return (result);
}
