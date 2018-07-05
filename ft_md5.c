/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_md5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otiniako <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/02 17:31:23 by otiniako          #+#    #+#             */
/*   Updated: 2018/07/02 17:31:24 by otiniako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>



void	ft_md5(int ac, char **av)
{
	t_md5	*md5;

	md5 = (t_md5 *)malloc(sizeof(t_md5));
	md5->msg = ft_strcpy(ft_strnew(ft_strlen(av[3]) + 1), av[3]);
	md5->len_msg = ft_strlen(md5->msg);
	//ft_printf("md5->msg %s\nmd5->len_msg %i\n", md5->msg, md5->len_msg);
	ft_get_hash_md5(md5);
/*	while (ac)
	{
		md5 = ft_new_md5();
		if (av[ac][0] == '-')
			ft_get_flags(md5, ac, av);
		md5->msg = md5->s ? ft_strcpy(ft_strnew(ft_strlen(av[ac] + 1)), av[ac])
		: ft_get_msg(md5, av[ac]);
		md5->len_msg = ft_strlen(md5->msg);
		ft_get_hash_md5(md5);
		ft_print_hash_md5(md5);
		ft_free_md5(md5);
		ac++;
	}*/
}