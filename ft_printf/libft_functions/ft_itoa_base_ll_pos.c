/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base_ll_pos.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreicher <sreicher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 15:33:44 by aagrivan          #+#    #+#             */
/*   Updated: 2021/05/12 22:12:55 by sreicher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	fill_string(long long prod)
{
	char				c;

	c = '0';
	if (prod < 10)
		c = prod + '0';
	else if (prod >= 10)
		c = prod + 'a' - 10;
	return (c);
}

static unsigned long	get_length_num(long long nbr, int base)
{
	unsigned long		l;

	if (nbr == 0)
		l = 1;
	else
		l = 0;
	while (nbr)
	{
		l++;
		nbr /= base;
	}
	return (l);
}

char	*ft_itoa_base_ll_pos(long long num, int base)
{
	char				*str;
	unsigned long		len;
	long long			prod;
	long long			nbr;

	if (base < 2 || base > 36)
		return (NULL);
	if (num < 0)
		-num;
	len = get_length_num(nbr, base);
	str = ft_strnew(len);
	if (!str)
		return (NULL);
	len--;
	while (nbr)
	{
		prod = nbr % base;
		nbr /= base;
		str[len--] = fill_string(prod);
	}
	if (num == 0)
		str[len] = '0';
	return (str);
}
