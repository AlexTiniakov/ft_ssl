/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_md5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otiniako <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 20:06:39 by otiniako          #+#    #+#             */
/*   Updated: 2018/07/26 20:06:40 by otiniako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>

int		ft_print_md5(t_h *h)
{
	ft_printf("%2.2x%2.2x%2.2x%2.2x%2.2x%2.2x%2.2x%2.2x%2.2x%2.2x%2.2x%2.2x",
	(uint8_t)h->aa.i[0], (uint8_t)h->aa.i[1], (uint8_t)h->aa.i[2],
	(uint8_t)h->aa.i[3], (uint8_t)h->bb.i[0], (uint8_t)h->bb.i[1],
	(uint8_t)h->bb.i[2], (uint8_t)h->bb.i[3], (uint8_t)h->cc.i[0],
	(uint8_t)h->cc.i[1], (uint8_t)h->cc.i[2], (uint8_t)h->cc.i[3]);
	ft_printf("%2.2x%2.2x%2.2x%2.2x", (uint8_t)h->dd.i[0],
	(uint8_t)h->dd.i[1], (uint8_t)h->dd.i[2], (uint8_t)h->dd.i[3]);
	return (0);
}

void	ft_print_else_md5(t_h *h, t_ssl *ssl)
{
	ft_printf("MD5 (");
	ssl->s ? ft_printf("\"%s\") = ", h->msg) :
	ft_printf("%s) = ", h->file_name);
	ft_print_md5(h);
	ssl->s = 0;
}

void	ft_ssl_md5(t_h *h, t_ssl *ssl)
{
	if (ft_get_hash_md5(h))
		return ;
	if (ssl->p)
	{
		ssl->p = 0;
		ft_printf("%s", h->msg);
		ft_print_md5(h);
	}
	else if (ssl->q || ssl->std)
	{
		ssl->s = ssl->std ? ssl->s : 0;
		ssl->std = 0;
		ft_print_md5(h);
	}
	else if (ssl->r)
	{
		ft_print_md5(h);
		ft_printf(" %c%s%c", ssl->s ? '\"' : '\0', ssl->s ? h->msg :
		h->file_name, ssl->s ? '\"' : '\0');
		ssl->s = 0;
	}
	else
		ft_print_else_md5(h, ssl);
	ft_printf("\n");
}

void	ft_md5(t_ssl *ssl)
{
	t_h h;
	int c;

	h.alg = "md5";
	if (ssl->p || !ssl->ac)
	{
		read_from_stdin(&h, ssl);
		ft_ssl_md5(&h, ssl);
		ft_memdel((void **)&h.msg);
	}
	while (ssl->ac)
	{
		c = ssl->s ? msg_str(&h, *ssl->av) : msg_file(&h, *ssl->av);
		if (c == 1)
			ft_ssl_md5(&h, ssl);
		ft_memdel((void **)&h.msg);
		ssl->ac--;
		ssl->av++;
	}
}
