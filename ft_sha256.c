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

void	ft_print_sha(t_h *sha)
{
	ft_printf("%.8x%.8x%.8x%.8x%.8x%.8x%.8x%.8x\n",
    sha->h0,
    sha->h1,
    sha->h2,
    sha->h3,
    sha->h4,
    sha->h5,
    sha->h6,
    sha->h7);
}

void	ft_sha256(t_h *h)
{
	ft_get_hash_sha(h);
	ft_print_sha(h);
}