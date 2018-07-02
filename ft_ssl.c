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

int		main(int ac, char **av)
{
	if (ac < 2 || !av)
		return (ft_printf("usage: ft_ssl command [command opts] %s",
		"[command args]\n"));
	if (ft_strcmp("md5", av[1]) && ft_strcmp("sha256", av[1]))
		return (ft_printf("ft_ssl: Error: '%s' is an invalid command.%s%s",
		av[1], "\n\nStandard commands:\n\nMessage Digest commands:\nmd5\nsh",
		"a256\n\nCipher commands:\n"));
	!ft_strcmp("md5", av[1]) ? ft_md5() : ft_sha256();
	return (0);
}
