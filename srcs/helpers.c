/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoss <mjoss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 21:04:02 by mjoss             #+#    #+#             */
/*   Updated: 2021/04/03 19:44:31 by mjoss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	get_i_plus_1(int i, int max)
{
	return ((i + 1) % max);
}

int	get_i_minus_1(int i, int max)
{
	if (i != 0)
		return (i - 1);
	return (max - 1);
}

int	get_i_plus_2(int i, int max)
{
	return ((i + 2) % max);
}
