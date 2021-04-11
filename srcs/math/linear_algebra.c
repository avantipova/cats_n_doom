#include "data.h"
#include "linear_algebra.h"
#include "duke.h"

t_vertex4	multiply_m_v(t_mat4x4 mat, t_vertex4 vec)
{
	float	result[4];
	float	tmp[4];
	int		i;
	int		j;

	ft_bzero(result, sizeof(float) * 4);
	tmp[0] = vec.x;
	tmp[1] = vec.y;
	tmp[2] = vec.z;
	tmp[3] = vec.w;
	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			result[i] += mat.mat[i][j] * tmp[j];
	}
	return ((t_vertex4){
		result[0],
		result[1],
		result[2],
		result[3],
	});
}

t_mat4x4	multiply_m_m(t_mat4x4 m1, t_mat4x4 m2)
{
	t_mat4x4	result;
	int			i;
	int			j;
	int			k;

	i = 0;
	ft_bzero(&result, sizeof(t_mat4x4));
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			k = 0;
			while (k < 4)
			{
				result.mat[i][j] += m1.mat[i][k] * m2.mat[k][j];
				k++;
			}
			j++;
		}
		i++;
	}
	return (result);
}

t_point	viewport_to_canvas(t_point p)
{
	return ((t_point){\
		p.x * W / CW,
		p.y * H / CH,
		0.0
	});
}

t_point	project_vertex(t_vertex v)
{
	return (viewport_to_canvas(\
		(t_point){\
			v.x * PROJ_PLANE_Z / v.z,
			v.y * PROJ_PLANE_Z / v.z,
			0.0
		}
	));
}

t_mat4x4	update_instance_transform(t_instance *instance)
{
	instance->transform = multiply_m_m(make_translation_matrix(instance->position), \
	multiply_m_m(instance->orientation, make_scaling_matrix(instance->scale)));
	return (instance->transform);
}
