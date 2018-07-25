/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otiniako <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 20:54:17 by otiniako          #+#    #+#             */
/*   Updated: 2018/06/29 20:54:21 by otiniako         ###   ########.fr       */
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

int		read_from_stdin(t_h *h)
{
	char	*buf;
	int		ret;

	h->std = h->p ? 0 : 1;
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

int		ft_check_flags_ssl(int ac, char **av, t_h *h, int i)
{
	if (ac > 0 && !ft_strcmp("-p", *av) && (h->p = 1))
		return (ft_check_flags_ssl(ac - 1, av + 1, h, i + 1));
	if (ac > 0 && !ft_strcmp("-q", *av) && (h->q = 1))
		return (ft_check_flags_ssl(ac - 1, av + 1, h, i + 1));
	if (ac > 0 && !ft_strcmp("-r", *av) && (h->r = 1))
		return (ft_check_flags_ssl(ac - 1, av + 1, h, i + 1));
	if (ac > 0 && !ft_strcmp("-s", *av) && (h->s = 1))
		return (ft_check_flags_ssl(ac - 1, av + 1, h, i + 1));
	else
		return (i);
}

int		main(int ac, char **av)
{
	t_h	h;
	int c;

	if (ft_check(ac, av))
		return (1);
	ft_get(av[1], &h);
	c = ft_check_flags_ssl(ac - 2, av + 2, &h, 0);
	ac -= (2 + c);
	av += (2 + c);
	if (h.p || !ac)
	{
		read_from_stdin(&h);
		ft_sha256(&h);
		ft_memdel((void **)&h.msg);
	}
	while (ac)
	{
		c = h.s ? msg_str(&h, *av) : msg_file(&h, *av);
		if (c == 1)
			ft_sha256(&h);
		ft_memdel((void **)&h.msg);
		ac--;
		av++;
	}
	return (0);
}
