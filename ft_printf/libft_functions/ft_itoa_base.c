/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreicher <sreicher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 15:31:19 by aagrivan          #+#    #+#             */
/*   Updated: 2021/05/12 22:05:24 by sreicher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_get_length(int value, int base)
{
	int		len;

	if (value <= 0)
		len = 1;
	else
		len = 0;
	while (value)
	{
		len++;
		value /= base;
	}
	return (len);
}

int	ft_itoa_plus_minus_nbr(int value)
{
	long	nbr;

	nbr = 0;
	if (value < 0)
		nbr = -(long)value;
	else
		nbr = (long)value;
	return (nbr);
}

char	*ft_itoa_base(int value, int base)
{
	char	*str;
	long	nbr;
	int		len;

	if (base < 2 || base > 36)
		return (NULL);
	nbr = ft_itoa_plus_minus_nbr(value);
	len = ft_get_length(value, base);
	str = ft_strnew(len);
	if (!str)
		return (NULL);
	len--;
	while (nbr)
	{
		if (nbr % base < 10)
			str[len--] = (nbr % base) + '0';
		else
			str[len--] = (nbr % base) + 'a' - 10;
		nbr /= base;
	}
	if (len == 0)
		str[len] = '-';
	if (value == 0)
		str[len] = '0';
	return (str);
}
