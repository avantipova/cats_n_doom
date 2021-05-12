/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetrell <npetrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 18:27:42 by chorange          #+#    #+#             */
/*   Updated: 2021/05/12 23:29:43 by mjoss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
** return element with equal fd or create new, if it is missing
*/

static t_list	*get_struct(t_list **file, int fd)
{
	t_list	*tmp;

	tmp = *file;
	while (tmp)
	{
		if ((int)tmp->content_size == fd)
			return (tmp);
		tmp = tmp->next;
	}
	if (fd == 0)
	{
		tmp = ft_lstnew(NULL, fd);
		tmp->content = malloc(1);
		if (tmp->content == NULL)
		{
			free(tmp);
			return (NULL);
		}
		ft_memcpy(tmp->content, "", 1);
	}
	else
		tmp = ft_lstnew("", fd);
	ft_lstadd(file, tmp);
	*file = tmp;
	return (*file);
}

/*
** ft_strplus - create fresh string with size = old_size + add
*/

/*
** copy_to_chr -	add read the characters in destination
**					until we find the value of c
** 70-73 search c-char in src
** 79-80 add every character in destination
*/

static int	copy_to_chr(char **dst, char **src, char c)
{
	int		i;
	int		count;
	int		pos;
	char	*tmp;

	i = -1;
	tmp = *src;
	count = 0;
	while (tmp[++i])
		if (tmp[i] == c)
			break ;
	pos = i;
	*dst = ft_strnew(i + 1);
	if (!dst)
		return (0);
	while (tmp[count] && count < i)
	{
		ft_strncat(*dst, tmp + count, 1);
		count++;
	}
	return (pos);
}

/*
** ft_strsupersub - analogue of ft_strsub, but delete input string
*/

char	*ft_strsupersub(char *s, unsigned int start, size_t len)
{
	char	*str;
	int		i;
	char	*s_for_del;

	if (s == NULL || start > ft_strlen(s))
		return (NULL);
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	s_for_del = s;
	i = -1;
	while (start != 0)
	{
		s++;
		start--;
	}
	while (len != '\0')
	{
		*(str + ++i) = *s;
		s++;
		len--;
	}
	free(s_for_del);
	*(str + i) = '\0';
	return (str);
}

/*
** get_next_line -	reads from a file one line in line
**					return 1 if line is read successfully
** 					return 0 if reading complete
**					return -1 if error
**	142: check input
**	143: obtain a structure with handle
**	144-150: until we don't find \n, continue reading
**	152: if we have reached end of file we exit of function
**	154: coping line in line
**	155-159:: if we wrote in line last characters, clear content in current
**		 structure
*/

int	get_next_line(const int fd, char **line)
{
	char			buf[BUFF_SIZE + 1];
	static t_list	*fd_lst;
	t_list			*curr;
	int				ret;

	ret = read(fd, buf, 0);
	if (val_file(fd, line, ret) == -1)
		return (-1);
	curr = get_struct(&fd_lst, fd);
	curr->read_bytes = read(fd, buf, BUFF_SIZE);
	ret = loop(curr, buf, fd);
	if (ret == -1)
		return (-1);
	if (curr->read_bytes < BUFF_SIZE && !ft_strlen((char *)curr->content))
		return (0);
	curr->read_bytes = copy_to_chr(line, (char **)&curr->content, '\n');
	if (curr->read_bytes < (int)ft_strlen(curr->content))
		curr->content = ft_strsupersub(curr->content, curr->read_bytes + 1, \
							ft_strlen(curr->content + curr->read_bytes));
	else
		ft_strclr(curr->content);
	return (1);
}
