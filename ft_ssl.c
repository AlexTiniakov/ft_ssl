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

int		main(int ac, char **av)
{
	if (ft_check(ac, av))
		return (1);
	if (!ft_strcmp("md5", av[1]))
		ft_md5(ac - 2, av);
	else if (!ft_strcmp("sha256", av[1]))
		ft_sha256(ac - 2, av);
//	system("leaks ft_ssl");
	return (0);
}
