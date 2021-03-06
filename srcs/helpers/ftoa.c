/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baylak <baylak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 20:39:35 by mjoss             #+#    #+#             */
/*   Updated: 2021/05/14 18:25:47 by baylak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duke.h"

int	itoa_s(int value, char *buf)
{
	int	index;
	int	i;

	index = 0;
	i = value % 10;
	if (value >= 10)
	{
		index += itoa_s(value / 10, buf);
	}
	buf[index] = i + 0x30;
	index++;
	return (index);
}

char	*itoa(int value, char *buf)
{
	int	len;

	len = itoa_s(value, buf);
	buf[len] = '\0';
	return (buf);
}

int	insert_zeros(int ival, int decimals, char *buf)
{
	int	res;
	int	i;

	res = 0;
	while (ival)
	{
		ival /= 10;
		res++;
	}
	res = decimals - res;
	i = 0;
	ft_strcpy(buf, "");
	while (i < res)
	{
		ft_strcat(buf, "0");
		i++;
	}
	return (res);
}

int	ival_func(int decimals, float value)
{
	int	ival;
	int	d;

	ival = 1;
	d = -1;
	while (++d < decimals)
		ival *= 10;
	ival *= value;
	return (ival);
}

char	*ftoa(float value, int decimals, char *buf)
{
	int		index;
	int		d;
	int		ival;
	float	rounding;

	index = 0;
	rounding = 0.5;
	if (value < 0)
	{
		buf[index] = '-';
		index++;
		value = -value;
	}
	d = -1;
	while (++d < decimals)
		rounding /= 10.0;
	value += rounding;
	index += itoa_s((int)(value), buf + index);
	buf[index++] = '.';
	value = value - (int)(value);
	ival = ival_func(decimals, value);
	index += insert_zeros(ival, decimals, buf + index);
	index += itoa_s(ival, buf + index);
	buf[index] = '\0';
	return (buf);
}
