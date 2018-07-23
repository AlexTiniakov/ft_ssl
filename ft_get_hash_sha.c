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

const uint32_t t1[] = {0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
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

void	ft_make_arr(t_h *sha)
{
	int j;
	sha->hash = (uint32_t *)malloc(512);
	ft_bzero(sha->hash, 512);
	ft_memcpy(sha->hash, &sha->msg_uint[sha->i * 16], 512);
	j = 15;
	while (++j < 64)
	{
		sha->tmp4 = _ROT_R(sha->hash[j - 15], 7) ^ _ROT_R(sha->hash[j - 15], 18)
		^ (sha->hash[j - 15] >> 3);
		sha->tmp = _ROT_R(sha->hash[j - 2], 17) ^
		_ROT_R(sha->hash[j - 2], 19) ^ (sha->hash[j - 2] >> 10);
		sha->hash[j] = sha->hash[j - 16] + sha->tmp4 + sha->hash[j - 7] + sha->tmp;
	}
	sha->a = sha->h0;
	sha->b = sha->h1;
	sha->c = sha->h2;
	sha->d = sha->h3;
	sha->e = sha->h4;
	sha->f = sha->h5;
	sha->g = sha->h6;
	sha->h = sha->h7;
}

void	ft_sha_alg(t_h *sha)
{
	sha->tmp = _ROT_R(sha->e, 6) ^ _ROT_R(sha->e, 11) ^ _ROT_R(sha->e, 25);
	sha->tmp2 = (sha->e & sha->f) ^ ((~sha->e) & sha->g);
	sha->tmp3 = sha->h + sha->tmp + sha->tmp2 + t1[sha->j] + sha->hash[sha->j];
	sha->tmp4 = _ROT_R(sha->a, 2) ^ _ROT_R(sha->a, 13) ^ _ROT_R(sha->a, 22);
	sha->tmp5 = (sha->a & sha->b) ^ (sha->a & sha->c) ^ (sha->b & sha->c);
	sha->tmp6 = sha->tmp4 + sha->tmp5;
	sha->h = sha->g;
	sha->g = sha->f;
	sha->f = sha->e;
	sha->e = sha->d + sha->tmp3;
	sha->d = sha->c;
	sha->c = sha->b;
	sha->b = sha->a;
	sha->a = sha->tmp3 + sha->tmp6;
}

void	ft_get_sha(t_h *sha)
{
	sha->i = -1;
	while ((uint32_t)++sha->i < sha->count)
	{
		ft_make_arr(sha);
		sha->j = -1;
		while (++sha->j < 64)
			ft_sha_alg(sha);
		sha->h0 += sha->a;
		sha->h1 += sha->b;
		sha->h2 += sha->c;
		sha->h3 += sha->d;
		sha->h4 += sha->e;
		sha->h5 += sha->f;
		sha->h6 += sha->g;
		sha->h7 += sha->h;
		free(sha->hash);
	}
	free(sha->msg_uint);
}

void    ft_get_hash_sha(t_h *sha)
{
	int i;

    sha->h0 = 0x6a09e667;
	sha->h1 = 0xbb67ae85;
	sha->h2 = 0x3c6ef372;
	sha->h3 = 0xa54ff53a;
	sha->h4 = 0x510e527f;
	sha->h5 = 0x9b05688c;
	sha->h6 = 0x1f83d9ab;
	sha->h7 = 0x5be0cd19;
	sha->len_buf = sha->len_msg * 8;
	sha->count = 1 + ((sha->len_buf + 80) / 512);
	sha->msg_uint = (uint32_t *)malloc(sha->count * 64);//protect
	ft_bzero(sha->msg_uint, sha->count * 64);
	ft_strcpy((char *)sha->msg_uint, sha->msg);
	((char *)sha->msg_uint)[ft_strlen(sha->msg)] = 0x80;
	i = -1;
	while (++i < ((int)sha->count * 16) - 1)
		sha->msg_uint[i] = ft_rev_32(sha->msg_uint[i]);
	i = ((sha->count * 512 - 64) / 32) + 1;
	sha->msg_uint[i] = sha->len_buf;
	ft_get_sha(sha);
}
