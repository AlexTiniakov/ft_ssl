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

int		ft_print_sha256(t_h *h)
{
	ft_printf("%.8x%.8x%.8x%.8x%.8x%.8x%.8x%.8x", h->h0, h->h1, h->h2, h->h3,
	h->h4, h->h5, h->h6, h->h7);
	return (0);
}

void	ft_print_else_sha256(t_h *h, t_ssl *ssl)
{
	ft_printf("SHA256 (");
	ssl->s ? ft_printf("\"%s\") = ", h->msg) :
	ft_printf("%s) = ", h->file_name);
	ft_print_sha256(h);
	ssl->s = 0;
}

void	ft_ssl_sha256(t_h *h, t_ssl *ssl)
{
	if (ft_get_hash_sha(h))
		return ;
	if (ssl->p)
	{
		ssl->p = 0;
		ft_printf("%s", h->msg);
		ft_print_sha256(h);
	}
	else if (ssl->q || ssl->std)
	{
		ssl->s = ssl->std ? ssl->s : 0;
		ssl->std = 0;
		ft_print_sha256(h);
	}
	else if (ssl->r)
	{
		ft_print_sha256(h);
		ft_printf(" %c%s%c", ssl->s ? '\"' : '\0', ssl->s ? h->msg :
		h->file_name, ssl->s ? '\"' : '\0');
		ssl->s = 0;
	}
	else
		ft_print_else_sha256(h, ssl);
	ft_printf("\n");
}

void	ft_sha256(t_ssl *ssl)
{
	t_h h;
	int c;

	h.alg = "sha256";
	if (ssl->p || !ssl->ac)
	{
		read_from_stdin(&h, ssl);
		ft_ssl_sha256(&h, ssl);
		ft_memdel((void **)&h.msg);
	}
	while (ssl->ac)
	{
		c = ssl->s ? msg_str(&h, *ssl->av) : msg_file(&h, *ssl->av);
		if (c == 1)
			ft_ssl_sha256(&h, ssl);
		ft_memdel((void **)&h.msg);
		ssl->ac--;
		ssl->av++;
	}
}
