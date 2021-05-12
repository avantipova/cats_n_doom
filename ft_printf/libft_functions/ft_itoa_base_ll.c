/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base_ll.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreicher <sreicher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 15:32:25 by aagrivan          #+#    #+#             */
/*   Updated: 2021/05/12 22:10:19 by sreicher         ###   ########.fr       */
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

static unsigned long	get_length_num(long long nbr, int base, long long num)
{
	unsigned long		l;
	int					sign;

	if (num == 0)
		l = 1;
	else
		l = 0;
	if (num < 0)
		sign = 1;
	else
		sign = 0;
	while (nbr)
	{
		l++;
		nbr /= base;
	}
	return (l + sign);
}

int	ft_itoa_plus_minus_nbr_ll(long long num)
{
	long	nbr;

	if (num < 0)
		nbr = -num;
	else
		nbr = num;
	return (nbr);
}

char	*ft_itoa_base_ll(long long num, int base)
{
	char				*str;
	unsigned long		len;
	long long			prod;
	long long			nbr;

	if (base < 2 || base > 36)
		return (NULL);
	nbr = ft_itoa_plus_minus_nbr_ll(num);
	len = get_length_num(nbr, base, num);
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
	if (len == 0)
		str[len] = '-';
	if (num == 0)
		str[len] = '0';
	return (str);
}
