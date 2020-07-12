/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbolg <dbolg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 03:37:22 by dbolg             #+#    #+#             */
/*   Updated: 2020/07/12 21:23:48 by dbolg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if BUFFER_SIZE < 1
# undef BUFFER_SIZE
#endif

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 50
#endif

#include "get_next_line.h"

int	n_in_tail(char **head, char **tail, char **buf)
{
	int		nl;
	char	*tmp;

	nl = find_n(*tail, ft_strlen(*tail));
	tmp = *tail;
	*(*tail + nl) = '\0';
	if (!(*head = ft_strjoin(*tail, "")))
		return (f_ree(buf, &tmp, &tmp) ? -1 : -1);
	if (ft_strlen(*tail + nl + 1))
	{
		if (!(*tail = ft_strjoin((*tail + nl + 1), "")))
			return (f_ree(buf, &tmp, head) ? -1 : -1);
	}
	else
		*tail = NULL;
	f_ree(buf, &tmp, &tmp);
	return (1);
}

int	n_in_buf(char **head, char **tail, char **buf)
{
	int		nl;
	char	*tmp;

	tmp = NULL;
	nl = find_n(*buf, ft_strlen(*buf));
	if (ft_strlen(*buf + nl + 1))
	{
		if (!(*tail = ft_strjoin((*buf + nl + 1), "")))
		{
			(*head ? f_ree(buf, head, head) :
				f_ree(buf, buf, buf));
			return (-1);
		}
	}
	*(*buf + nl) = '\0';
	tmp = *head;
	if (!(*head = ft_strjoin(*head, *buf)))
	{
		(tmp ? f_ree(buf, tail, &tmp) : f_ree(buf, tail, tail));
		return (-1);
	}
	(tmp ? f_ree(buf, &tmp, &tmp) : f_ree(buf, buf, buf));
	return (1);
}

int	buf_mng(char **head, char **tail, char **buf, int buffsize)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = NULL;
	if ((find_n(*buf, ft_strlen(*buf))) > -1)
		return (n_in_buf(head, tail, buf));
	tmp = *head;
	if (!(*head = ft_strjoin(*head, *buf)))
	{
		(*tmp ? f_ree(buf, &tmp, &tmp) : f_ree(buf, buf, buf));
		return (-1);
	}
	if (tmp)
		f_ree(&tmp, &tmp, &tmp);
	while (i++ < buffsize)
		*(*buf + i) = '\0';
	return (-2);
}

int	end_of_file(char **head, char **buf)
{
	if (!(*head = ft_strjoin(*head, *buf)))
	{
		f_ree(buf, buf, buf);
		return (-1);
	}
	return (f_ree(buf, buf, buf) ? 0 : 0);
}

int	get_next_line(int fd, char **head)
{
	static char	*tail;
	char		*buf;
	int			ret;

	*head = NULL;
	ret = 0;
	if (fd < 0 || !head ||
			!(buf = ft_calloc((BUFFER_SIZE + 1), sizeof(char))))
		return (-1);
	if (tail && (find_n(tail, ft_strlen(tail)) > -1))
		return (n_in_tail(head, &tail, &buf));
	if (tail)
	{
		*head = tail;
		tail = NULL;
	}
	while ((read(fd, buf, BUFFER_SIZE)) > 0)
	{
		if ((ret = buf_mng(head, &tail, &buf, BUFFER_SIZE)) > -2)
			return (ret);
	}
	if (read(fd, buf, 0) == -1)
		return (f_ree(&buf, &buf, &buf) ? -1 : -1);
	return (end_of_file(head, &buf));
}
