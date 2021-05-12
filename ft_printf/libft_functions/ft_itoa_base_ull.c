/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base_ull.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreicher <sreicher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 15:35:57 by aagrivan          #+#    #+#             */
/*   Updated: 2021/05/12 22:14:17 by sreicher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	fill_string(unsigned long long prod, char a)
{
	char				c;

	c = '0';
	if (prod < 10)
		c = prod + '0';
	else if (prod >= 10 && a == 'a')
		c = prod + 'a' - 10;
	else if (prod >= 10 && a == 'A')
		c = prod + 'A' - 10;
	return (c);
}

static unsigned long	get_length_num(unsigned long long num, int base)
{
	unsigned long		l;

	if (num == 0)
		l = 1;
	else
		l = 0;
	while (num)
	{
		l++;
		num /= base;
	}
	return (l);
}

char	*ftbaseull(unsigned long long num, int base, char c)
{
	char				*str;
	unsigned long		len;
	long long			prod;

	if (base < 2 || base > 36)
		return (NULL);
	len = get_length_num(num, base);
	str = ft_strnew(len);
	if (!str)
		return (NULL);
	len--;
	while (num)
	{
		prod = num % base;
		num /= base;
		str[len--] = fill_string(prod, c);
	}
	if (num == 0)
		str[len] = '0';
	return (str);
}
