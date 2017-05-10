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

static int			ft_check_stock(char **stock, char **line)
{
	char			*var;

	var = NULL;
	if (*stock)
	{
		if ((var = ft_strchr((const char*)*stock, '\n')))
		{
			*line = ft_strsub((char const*)*stock, 0, var - *stock);
			ft_memmove(*stock, var + 1, ft_strlen(var));
			return (1);
		}
	}
	return (0);
}

static	int			cpy_fd_in_stock(int fd, char **stock, char **line)
{
	char			buf[BUFF_SIZE + 1];
	int				ret;
	char			*var;

	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		if (ret == -1)
			return (-1);
		buf[ret] = '\0';
		var = *stock;
		if (*stock)
		{
			*stock = ft_strjoin((char const*)var, (char const*)buf);
			free(var);
		}
		else
			*stock = ft_strdup((const char*)buf);
		if (ft_check_stock(stock, line))
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
	if (ret[fd] && ft_check_stock(&ret[fd], line))
		return (1);
	result = cpy_fd_in_stock(fd, &ret[fd], line);
	if (result != 0)
		return (result);
	if (ret[fd] == NULL || ret[fd][0] == '\0')
		return (0);
	*line = ret[fd];
	ret[fd] = NULL;
	return (1);
}
