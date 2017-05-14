/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdalha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/05 05:11:45 by oabdalha          #+#    #+#             */
/*   Updated: 2017/04/21 01:08:38 by oabdalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char		*loc_pointer_chr(const char *s, int c)
{
	while (*s != (char)c && *s != '\0')
		s++;
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}

static int			ft_check_bucket(char **bucket, char **line)
{
	char			*a;

	a = NULL;
	if (*bucket)
	{
		if ((a = loc_pointer_chr((const char*)*bucket, '\n')))
		{
			*line = ft_strsub((char const*)*bucket, 0, a - *bucket);
			ft_memmove(*bucket, a + 1, ft_strlen(a));
			return (1);
		}
	}
	return (0);
}

static	int			cpy_fd_in_bucket(int fd, char **bucket, char **line)
{
	char			buf[BUFF_SIZE + 1];
	int				ret;
	char			*a;

	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		if (ret == -1)
			return (-1);
		buf[ret] = '\0';
		a = *bucket;
		if (*bucket)
		{
			*bucket = ft_strjoin((char const*)a, (char const*)buf);
			free(a);
		}
		else
			*bucket = ft_strdup((const char*)buf);
		if (ft_check_bucket(bucket, line))
			return (1);
	}
	return (0);
}

int					get_next_line(int const fd, char **line)
{
	static	char	*ret[2147483647];
	int				result;

	if (!line || fd < 0)
		return (-1);
	if (ret[fd] && ft_check_bucket(&ret[fd], line))
		return (1);
	result = cpy_fd_in_bucket(fd, &ret[fd], line);
	if (result != 0)
		return (result);
	if (ret[fd] == NULL || ret[fd][0] == '\0')
		return (0);
	*line = ret[fd];
	ret[fd] = NULL;
	return (1);
}
