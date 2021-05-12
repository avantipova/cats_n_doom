/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baylak <baylak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 21:01:00 by chorange          #+#    #+#             */
/*   Updated: 2021/05/07 04:58:19 by baylak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include "../libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# define BUFF_SIZE 21

int	get_next_line(const int fd, char **line);
int	val_file(int f, char **line, int ret);
int	loop(t_list *curr, char *buf, int fd);

#endif
