/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_hash_sha.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otiniako <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 21:38:59 by otiniako          #+#    #+#             */
/*   Updated: 2018/07/06 21:39:00 by otiniako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>

const uint32_t g_t1[] = {0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
	0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01,
	0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
	0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa,
	0x5cb0a9dc, 0x76f988da, 0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
	0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138,
	0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
	0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624,
	0xf40e3585, 0x106aa070, 0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
	0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3, 0x748f82ee, 0x78a5636f,
	0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};

uint32_t	ft_rev_32(uint32_t x)
{
	return ((x >> 24) | ((x & 0xff0000) >> 8) |
		((x & 0xff00) << 8) | (x << 24));
}

void		ft_make_arr(t_h *h)
{
	int j;

	h->hash = (uint32_t *)malloc(512);
	ft_bzero(h->hash, 512);
	ft_memcpy(h->hash, &h->msg_uint[h->i * 16], 512);
	j = 15;
	while (++j < 64)
	{
		h->tmp4 = _ROT_R(h->hash[j - 15], 7) ^ _ROT_R(h->hash[j - 15], 18)
		^ (h->hash[j - 15] >> 3);
		h->tmp = _ROT_R(h->hash[j - 2], 17) ^
		_ROT_R(h->hash[j - 2], 19) ^ (h->hash[j - 2] >> 10);
		h->hash[j] = h->hash[j - 16] + h->tmp4 + h->hash[j - 7] + h->tmp;
	}
	h->a = h->h0;
	h->b = h->h1;
	h->c = h->h2;
	h->d = h->h3;
	h->e = h->h4;
	h->f = h->h5;
	h->g = h->h6;
	h->h = h->h7;
}

void		ft_sha_alg(t_h *h)
{
	h->tmp = _ROT_R(h->e, 6) ^ _ROT_R(h->e, 11) ^ _ROT_R(h->e, 25);
	h->tmp2 = (h->e & h->f) ^ ((~h->e) & h->g);
	h->tmp3 = h->h + h->tmp + h->tmp2 + g_t1[h->j] + h->hash[h->j];
	h->tmp4 = _ROT_R(h->a, 2) ^ _ROT_R(h->a, 13) ^ _ROT_R(h->a, 22);
	h->tmp5 = (h->a & h->b) ^ (h->a & h->c) ^ (h->b & h->c);
	h->tmp6 = h->tmp4 + h->tmp5;
	h->h = h->g;
	h->g = h->f;
	h->f = h->e;
	h->e = h->d + h->tmp3;
	h->d = h->c;
	h->c = h->b;
	h->b = h->a;
	h->a = h->tmp3 + h->tmp6;
}

void		ft_get_sha(t_h *h)
{
	h->i = -1;
	while ((uint32_t)++h->i < h->count)
	{
		ft_make_arr(h);
		h->j = -1;
		while (++h->j < 64)
			ft_sha_alg(h);
		h->h0 += h->a;
		h->h1 += h->b;
		h->h2 += h->c;
		h->h3 += h->d;
		h->h4 += h->e;
		h->h5 += h->f;
		h->h6 += h->g;
		h->h7 += h->h;
		free(h->hash);
	}
	free(h->msg_uint);
}

int			ft_get_hash_sha(t_h *h)
{
	int i;

	h->h0 = 0x6a09e667;
	h->h1 = 0xbb67ae85;
	h->h2 = 0x3c6ef372;
	h->h3 = 0xa54ff53a;
	h->h4 = 0x510e527f;
	h->h5 = 0x9b05688c;
	h->h6 = 0x1f83d9ab;
	h->h7 = 0x5be0cd19;
	h->len_buf = h->len_msg * 8;
	h->count = 1 + ((h->len_buf + 80) / 512);
	if (!(h->msg_uint = (uint32_t *)malloc(h->count * 64)))
		return (write(1, "Error\n", 6));
	ft_bzero(h->msg_uint, h->count * 64);
	ft_strcpy((char *)h->msg_uint, h->msg);
	((char *)h->msg_uint)[ft_strlen(h->msg)] = 0x80;
	i = -1;
	while (++i < ((int)h->count * 16) - 1)
		h->msg_uint[i] = ft_rev_32(h->msg_uint[i]);
	i = ((h->count * 512 - 64) / 32) + 1;
	h->msg_uint[i] = h->len_buf;
	ft_get_sha(h);
	return (0);
}
