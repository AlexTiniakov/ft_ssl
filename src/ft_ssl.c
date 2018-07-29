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

void			ft_usage(t_ssl *ssl)
{
	(void)ssl;
	ft_printf("usage: ft_ssl command [-p] [-q] [-r] %s%s",\
	"[file_name]\n       ft_ssl command [-p] [-q] [-r] [-s] ",\
	"[\"string\"]\n");
}

int				ft_usage_i(void)
{
	ft_usage(NULL);
	return (1);
}

int				ft_error(char *str)
{
	return (ft_printf("ft_ssl: Error: '%s' is an invalid command.%s%s",\
		str, "\n\nStandard commands:\n\nMessage Digest commands:\nmd5\nsh",\
		"a256\n\nCipher commands:\n"));
}

static int		ft_check_flags_ssl(int ac, char **av, t_ssl *ssl, int i)
{
	if (ac > 0 && !ft_strcmp("-p", *av) && (ssl->p = 1))
		return (ft_check_flags_ssl(ac - 1, av + 1, ssl, i + 1));
	if (ac > 0 && !ft_strcmp("-q", *av) && (ssl->q = 1))
		return (ft_check_flags_ssl(ac - 1, av + 1, ssl, i + 1));
	if (ac > 0 && !ft_strcmp("-r", *av) && (ssl->r = 1))
		return (ft_check_flags_ssl(ac - 1, av + 1, ssl, i + 1));
	if (ac > 0 && !ft_strcmp("-s", *av) && (ssl->s = 1))
		return (ft_check_flags_ssl(ac - 1, av + 1, ssl, i + 1));
	else
		return (i);
}

int				main(int ac, char **av)
{
	t_ssl	ssl;
	int		c;

	if (ac < 2)
		return (ft_usage_i());
	if (!(ssl.func = ft_get_command(av[1], ft_init_list())))
		return (ft_error(av[1]));
	c = ft_check_flags_ssl(ac - 2, av + 2, &ssl, 0);
	ssl.ac = ac - 2 - c;
	ssl.av = av + 2 + c;
	ssl.func(&ssl);
	return (0);
}
