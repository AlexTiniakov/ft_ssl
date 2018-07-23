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

void	ft_print_md5(t_h *md5)
{
	ft_printf("%2.2x%2.2x%2.2x%2.2x%2.2x%2.2x%2.2x%2.2x%2.2x%2.2x%2.2x%2.2x%2.2x%2.2x%2.2x%2.2x\n",
    (uint8_t)md5->aa.i[0],
    (uint8_t)md5->aa.i[1],
    (uint8_t)md5->aa.i[2],
    (uint8_t)md5->aa.i[3],
    (uint8_t)md5->bb.i[0],
    (uint8_t)md5->bb.i[1],
    (uint8_t)md5->bb.i[2],
    (uint8_t)md5->bb.i[3],
    (uint8_t)md5->cc.i[0],
    (uint8_t)md5->cc.i[1],
    (uint8_t)md5->cc.i[2],
    (uint8_t)md5->cc.i[3],
    (uint8_t)md5->dd.i[0],
    (uint8_t)md5->dd.i[1],
    (uint8_t)md5->dd.i[2],
    (uint8_t)md5->dd.i[3]);
}

void	ft_md5(t_h *h)
{	
	ft_get_hash_md5(h);
	ft_print_md5(h);
}