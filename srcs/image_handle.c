/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baylak <baylak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 21:04:34 by mjoss             #+#    #+#             */
/*   Updated: 2021/05/07 04:54:49 by baylak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duke.h"

void	put_pixel(int *image_data, int x, int y, int color)
{
	int	index;

	index = ((H_2 - y - 1) * W + W_2 + x);
	if (index >= 0 && index < H_W && x > -W_2 && x < W_2)
		image_data[index] = color;
}

int	get_texel(SDL_Surface *image_data, float u, float v)
{
	int	pitch;
	int	index;
	int	*pixels;

	pitch = image_data->w;
	u = u - floor(u);
	v = v - floor(v);
	index = (int)(image_data->h *v) *pitch + (int)(pitch *u);
	pixels = (int *)image_data->pixels;
	if (index >= 0 && index < image_data->w * image_data->h)
		return (pixels[index]);
	return (0);
}
