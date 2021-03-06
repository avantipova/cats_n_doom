/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   depth_buffer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baylak <baylak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 20:23:45 by mjoss             #+#    #+#             */
/*   Updated: 2021/05/07 04:54:49 by baylak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duke.h"

float	*clear_z_buffer(float *z_buffer)
{
	ft_bzero((void *)z_buffer, sizeof(float) * H_W);
	return (z_buffer);
}

float	*create_z_buffer(void)
{
	float	*z_buffer;

	z_buffer = malloc(sizeof(float) * H_W);
	clear_z_buffer(z_buffer);
	return (z_buffer);
}

int	set_z_buffer(float *z_buffer, int x, int y, float value)
{
	int	index;

	index = (H_2 - y - 1) * W + W_2 + x;
	if (index < 0 || index >= H_W)
		return (0);
	if (z_buffer[index] < value)
	{
		z_buffer[index] = value;
		return (1);
	}
	return (0);
}

int	set_z_buffer_bsp(float *z_buffer, int x, int y, float value)
{
	int	index;

	index = (H_2 - y - 1) * W + W_2 + x;
	if (index < 0 || index >= H_W)
		return (0);
	if (!z_buffer[index])
	{
		z_buffer[index] = value;
		return (1);
	}
	return (0);
}
