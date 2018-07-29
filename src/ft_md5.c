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

void	ft_paste_md5(char *str, int i, uint32_t nbr)
{
	str[i + 0] = _HEXL[((nbr / 16) % 16)];
	str[i + 1] = _HEXL[(nbr % 16)];
	str[i + 2] = _HEXL[((nbr / 4096) % 16)];
	str[i + 3] = _HEXL[((nbr / 256) % 16)];
	str[i + 4] = _HEXL[((nbr / 1048576) % 16)];
	str[i + 5] = _HEXL[((nbr / 65536) % 16)];
	str[i + 6] = _HEXL[(nbr / 268435456)];
	str[i + 7] = _HEXL[((nbr / 16777216) % 16)];
	str[i + 8] = '\0';
}

int		ft_print_md5(t_h *h)
{
	ft_paste_md5((char *)h->rez, 0, h->h0);
	ft_paste_md5((char *)h->rez, 8, h->h1);
	ft_paste_md5((char *)h->rez, 16, h->h2);
	ft_paste_md5((char *)h->rez, 24, h->h3);
	return (0);
}

void	ft_ssl_md5(t_h *h, t_ssl *ssl)
{
	if (ft_get_hash_md5(h) || ft_print_md5(h))
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
		ft_printf("MD5 (%s%s%s) = %s", _PRINT, (char *)h->rez);
		ssl->s = 0;
	}
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
