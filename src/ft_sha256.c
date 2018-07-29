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

void	ft_paste_sha256(char *str, int i, uint32_t nbr)
{
	str[i + 0] = _HEXL[(nbr / 268435456)];
	str[i + 1] = _HEXL[((nbr / 16777216) % 16)];
	str[i + 2] = _HEXL[((nbr / 1048576) % 16)];
	str[i + 3] = _HEXL[((nbr / 65536) % 16)];
	str[i + 4] = _HEXL[((nbr / 4096) % 16)];
	str[i + 5] = _HEXL[((nbr / 256) % 16)];
	str[i + 6] = _HEXL[((nbr / 16) % 16)];
	str[i + 7] = _HEXL[(nbr % 16)];
	str[i + 8] = '\0';
}

int		ft_print_sha256(t_h *h)
{
	ft_paste_sha256((char *)h->rez, 0, h->h0);
	ft_paste_sha256((char *)h->rez, 8 * 1, h->h1);
	ft_paste_sha256((char *)h->rez, 8 * 2, h->h2);
	ft_paste_sha256((char *)h->rez, 8 * 3, h->h3);
	ft_paste_sha256((char *)h->rez, 8 * 4, h->h4);
	ft_paste_sha256((char *)h->rez, 8 * 5, h->h5);
	ft_paste_sha256((char *)h->rez, 8 * 6, h->h6);
	ft_paste_sha256((char *)h->rez, 8 * 7, h->h7);
	return (0);
}

void	ft_ssl_sha256(t_h *h, t_ssl *ssl)
{
	if (ft_get_hash_sha(h) || ft_print_sha256(h))
		return ;
	if (ssl->p && !(ssl->p = 0))
		ft_printf("%s%s", h->msg, (char *)h->rez);
	else if (ssl->q || ssl->std)
	{
		ssl->s = ssl->std ? ssl->s : 0;
		ssl->std = 0;
		ft_printf("%s", (char *)h->rez);
	}
	else if (ssl->r)
	{
		ft_printf("%s %s%s%s", (char *)h->rez, _PRINT);
		ssl->s = 0;
	}
	else
	{
		ft_printf("SHA256 (%s%s%s) = %s", _PRINT, (char *)h->rez);
		ssl->s = 0;
	}
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
