/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sha256.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otiniako <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/02 17:31:36 by otiniako          #+#    #+#             */
/*   Updated: 2018/07/02 17:31:37 by otiniako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>

void	ft_sha256(int ac, char **av)
{
	t_h	sha;

	sha.msg = ft_strcpy(ft_strnew(ft_strlen(av[3]) + 1), av[3]);
	sha.len_msg = ft_strlen(sha.msg);
	ft_get_hash_sha(&sha);
	free(sha.msg);
	free(sha.buf);
}