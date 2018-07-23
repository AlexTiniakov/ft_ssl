/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otiniako <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/02 17:06:20 by otiniako          #+#    #+#             */
/*   Updated: 2018/07/02 17:06:21 by otiniako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H
# define _F(x, y, z) ((x & y) | ((~x) & z))
# define _G(x, y, z) ((x & z) | (y & (~z)))
# define _H(x, y, z) (x ^ y ^ z)
# define _I(x, y, z) (y ^ (x | (~z)))
# define _ROT_L(x, y) (((x) << (y)) | ((x) >> (32 - (y))))
# define _ROT_R(x, y) ((((unsigned int)(x) >> (y))) | ((x) << (32 - (y))))
# include "libft.h"

typedef union		u_md
{
	uint32_t		h;
	char			i[4];
}					t_md;

typedef struct		s_h
{
	int				std : 1;
	int				o : 1;
	int				p : 1;
	int				q : 1;
	int				r : 1;
	int				s : 1;
	int				md5 : 1;
	int				i;
	int				j;
	t_md			aa;
	t_md			bb;
	t_md			cc;
	t_md			dd;
	t_md			ee;
	t_md			ff;
	t_md			gg;
	t_md			hh;
	uint32_t		h0;
	uint32_t		h1;
	uint32_t		h2;
	uint32_t		h3;
	uint32_t		h4;
	uint32_t		h5;
	uint32_t		h6;
	uint32_t		h7;
	uint32_t		len_msg;//
	uint32_t		len_buf;//newlen
	uint32_t		count;//ofset
	int				set;//
	char			*msg;
	char			*buf;
	uint32_t		*hash;//w
	uint32_t		*msg_uint;
	uint32_t		fghi;
	uint32_t		tmp;
	uint32_t		tmp1;
	uint32_t		tmp2;
	uint32_t		tmp3;
	uint32_t		tmp4;
	uint32_t		tmp5;
	uint32_t		tmp6;
	uint32_t		a;
	uint32_t		b;
	uint32_t		c;
	uint32_t		d;
	uint32_t		e;
	uint32_t		f;
	uint32_t		g;
	uint32_t		h;
}					t_h;

void				ft_md5(t_h *h);
void				ft_sha256(t_h *h);
void				ft_get_hash_md5(t_h *md5);
void				ft_get_hash_sha(t_h *sha);
void				go_sha256(t_h *g);

#endif