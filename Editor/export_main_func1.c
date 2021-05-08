/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_main_func1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreicher <sreicher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 19:46:44 by sreicher          #+#    #+#             */
/*   Updated: 2021/05/08 20:14:31 by sreicher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	put_vt_trs_count(int fd, int i, t_bsp *node)
{
	while (i < node->vt_trs_count)
	{
		ft_putstr_fd("f ", fd);
		ft_putnbr_fd(node->vt_trs[i].ids[0] + 1, fd);
		ft_putstr_fd("/", fd);
		ft_putnbr_fd(node->vt_trs[i].uv_ids[0] + 1, fd);
		ft_putstr_fd("/", fd);
		ft_putnbr_fd(node->vt_trs[i].n_ids[0] + 1, fd);
		ft_putstr_fd(" ", fd);
		ft_putnbr_fd(node->vt_trs[i].ids[1] + 1, fd);
		ft_putstr_fd("/", fd);
		ft_putnbr_fd(node->vt_trs[i].uv_ids[1] + 1, fd);
		ft_putstr_fd("/", fd);
		ft_putnbr_fd(node->vt_trs[i].n_ids[1] + 1, fd);
		ft_putstr_fd(" ", fd);
		ft_putnbr_fd(node->vt_trs[i].ids[2] + 1, fd);
		ft_putstr_fd("/", fd);
		ft_putnbr_fd(node->vt_trs[i].uv_ids[2] + 1, fd);
		ft_putstr_fd("/", fd);
		ft_putnbr_fd(node->vt_trs[i].n_ids[2] + 1, fd);
		ft_putstr_fd("\n", fd);
		i++;
	}
	ft_putendl_fd("", fd);
}

void	write_vt_trs_to_file(t_bsp *node, int fd)
{
	int		i;

	i = 0;
	if (!node->is_leaf)
		return ;
	put_vt_trs_count(fd, i, node);
	ft_putendl_fd("", fd);
}
