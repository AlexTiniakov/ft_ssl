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

int		ft_check(int ac, char **av)
{
	if (ac < 2)
	{
		return (ft_printf("usage: ft_ssl command [-p] [-q] [-r] %s%s",\
		"[file_name]\n       ft_ssl command [-p] [-q] [-r] [-s] ",\
		"[\"string\"]\n"));
	}
	if (ft_strcmp("md5", av[1]) && ft_strcmp("sha256", av[1]))
	{
		return (ft_printf("ft_ssl: Error: '%s' is an invalid command.%s%s",\
		av[1], "\n\nStandard commands:\n\nMessage Digest commands:\nmd5\nsh",\
		"a256\n\nCipher commands:\n"));
	}
	return (0);
}

int		ft_print_sha(t_h *h)
{
	ft_printf("%.8x%.8x%.8x%.8x%.8x%.8x%.8x%.8x",
	h->h0,
	h->h1,
	h->h2,
	h->h3,
	h->h4,
	h->h5,
	h->h6,
	h->h7);
	return (0);
}

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

void	ft_print_else(t_h *h)
{
	char *str;

	str = ft_str_toupper(h->alg);
	ft_printf("%s (", str);
	ft_memdel((void **)&str);
	h->s ? ft_printf("\"%s\") = ", h->msg) : ft_printf("%s) = ", h->file_name);
	h->print(h);
	h->s = 0;
}

void	ft_sha256(t_h *h)
{
	if (h->func(h))
		return ;
	if (h->p)
	{
		h->p = 0;
		ft_printf("%s", h->msg);
		h->print(h);
	}
	else if (h->q || h->std)
	{
		h->s = h->std ? h->s : 0;
		h->std = 0;
		h->print(h);
	}
	else if (h->r)
	{
		h->print(h);
		ft_printf(" %c%s%c", h->s ? '\"' : '\0', h->s ? h->msg :
		h->file_name, h->s ? '\"' : '\0');
		h->s = 0;
	}
	else
		ft_print_else(h);
	ft_printf("\n");
}
