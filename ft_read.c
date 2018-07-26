/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otiniako <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 20:55:39 by otiniako          #+#    #+#             */
/*   Updated: 2018/07/26 20:55:40 by otiniako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>

int		msg_str(t_h *h, char *str)
{
	h->msg = ft_strcpy(ft_strnew(ft_strlen(str) + 1), str);
	h->len_msg = ft_strlen(h->msg);
	return (1);
}

int		msg_file(t_h *h, char *name)
{
	int		fd;
	char	*buf;
	int		ret;

	h->msg = ft_strnew(1);
	if ((fd = open(name, O_RDONLY)) == -1)
		return (ft_printf("ft_ssl: %s: %s: No such file or directory\n",
		h->alg, name));
	else
	{
		buf = ft_strnew(2);
		while ((ret = read(fd, buf, 1)))
		{
			h->msg = ft_strjoin_clean(h->msg, buf);
			buf = ft_strnew(2);
		}
		free(buf);
		h->len_msg = ft_strlen(h->msg);
		h->file_name = name;
		return (1);
	}
}

int		read_from_stdin(t_h *h, t_ssl *ssl)
{
	char	*buf;
	int		ret;

	ssl->std = ssl->p ? 0 : 1;
	h->msg = ft_strnew(2);
	buf = ft_strnew(2);
	while ((ret = read(0, buf, 1)))
	{
		h->msg = ft_strjoin_clean(h->msg, buf);
		buf = ft_strnew(2);
	}
	free(buf);
	return ((h->len_msg = ft_strlen(h->msg)));
}

char	*ft_read_from_stdin(char *str, char *buf, int ret)
{
	str = ft_strnew(2);
	buf = ft_strnew(2);
	while ((ret = read(0, buf, 1)))
	{
		str = ft_strjoin_clean(str, buf);
		buf = ft_strnew(2);
	}
	free(buf);
	return (str);
}
