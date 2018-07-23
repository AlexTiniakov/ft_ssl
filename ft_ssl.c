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

int		ft_check(int ac, char **av)
{
	if (ac < 2)
		return (ft_printf("usage: ft_ssl command [-p] [-q] [-r] %s%s",
		"[file_name]\n       ft_ssl command [-p] [-q] [-r] [-s] ",
		 "[\"string\"]\n"));
	if (ft_strcmp("md5", av[1]) && ft_strcmp("sha256", av[1]))
		return (ft_printf("ft_ssl: Error: '%s' is an invalid command.%s%s",
		av[1], "\n\nStandard commands:\n\nMessage Digest commands:\nmd5\nsh",
		"a256\n\nCipher commands:\n"));
	return (0);
}

int		msg_str(t_h *h, char *str)
{
	h->msg = ft_strcpy(ft_strnew(ft_strlen(str) + 1), str);
	h->len_msg = ft_strlen(h->msg);
	h->s = 0;
	h->o = 1;
	return (1);
}

int		msg_file(t_h *h, char *name)
{
	int		fd;
	char	*buf;
	int		ret;

	h->o = 1;
	if ((fd = open(name, O_RDONLY)) == -1)
		return (ft_printf("ft_ssl: %s: %s: No such file or directory", h->md5 ?
		"md5" : "sha256", name));
	else
	{
		h->msg = ft_strnew(1);
		while ((ret = read(fd, buf = ft_strnew(2), 1)))
			h->msg = ft_strjoin_clean(h->msg, buf);
		return (1);
	}
}

int		read_from_stdin(t_h *h)
{
	char	*buf;
	int		len;
	int		ret;

	h->msg = ft_strnew(1);
	while ((ret = read(0, buf = ft_strnew(2), 1)))
		h->msg = ft_strjoin_clean(h->msg, buf);
	h->std = (len = ft_strlen(h->msg)) > 0 ? 1 : 0;
	return (len);
}

int		ft_check_flags_ssl(int *ac, char ***av, t_h *h)
{
	if (*ac && !h->o && !ft_strcmp("-p", **av) && (h->p = 1))
		return (ft_check_flags_ssl(&(*ac--), &(*av++), h));
	else if (*ac && !h->o && !ft_strcmp("-q", **av) && (h->q = 1))
		return (ft_check_flags_ssl(&(*ac--), &(*av++), h));
	else if (*ac && !h->o && !ft_strcmp("-r", **av) && (h->r = 1))
		return (ft_check_flags_ssl(&(*ac--), &(*av++), h));
	else if (*ac && !h->o && !ft_strcmp("-s", **av) && (h->s = 1))
		return (ft_check_flags_ssl(&(*ac--), &(*av++), h));
	else if (*ac)
		return (h->s ? msg_str(h, **av) : msg_file(h, **av));
	else if (h->std == 0 && read_from_stdin(h) > 0)
		return (1);
	else
		return (-1);
}

int		main(int ac, char **av)
{
	t_h	h;

	if (ft_check(ac, av))
		return (1);
	h.md5 = ft_strcmp("md5", av[1]) ? 1 : 0;
	h.std = 0;
//	if (read_from_stdin(&h) > 0)
//		h.md5 == 1 ? ft_md5(&h) : ft_sha256(&h);
	h.o = 0;
	ac -= 2;
	av += 2;
	while (ft_check_flags_ssl(&ac, &av, &h) > 0)
		h.md5 == 1 ? ft_md5(&h) : ft_sha256(&h);
	system("leaks ft_ssl");
	return (0);
}
