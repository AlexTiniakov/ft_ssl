/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_hash_md5.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otiniako <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/03 22:23:07 by otiniako          #+#    #+#             */
/*   Updated: 2018/07/03 22:23:08 by otiniako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>

const uint32_t g_t[] = {
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee, 0xf57c0faf, 0x4787c62a,
	0xa8304613, 0xfd469501, 0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821, 0xf61e2562, 0xc040b340,
	0x265e5a51, 0xe9b6c7aa, 0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed, 0xa9e3e905, 0xfcefa3f8,
	0x676f02d9, 0x8d2a4c8a, 0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70, 0x289b7ec6, 0xeaa127fa,
	0xd4ef3085, 0x04881d05, 0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039, 0x655b59c3, 0x8f0ccc92,
	0xffeff47d, 0x85845dd1, 0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};

const uint32_t g_s[] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17,
	22, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 4, 11, 16, 23,
	4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 6, 10, 15, 21, 6, 10, 15, 21,
	6, 10, 15, 21, 6, 10, 15, 21};

void		ft_md5_hashing(t_h *md5, int i, int j)
{
	if (i < 16)
		md5->fghi = _F(md5->b, md5->c, md5->d);
	else if (i < 32)
	{
		md5->fghi = _G(md5->b, md5->c, md5->d);
		j = (5 * i + 1) % 16;
	}
	else if (i < 48)
	{
		md5->fghi = _H(md5->b, md5->c, md5->d);
		j = (3 * i + 5) % 16;
	}
	else
	{
		md5->fghi = _I(md5->b, md5->c, md5->d);
		j = (7 * i) % 16;
	}
	md5->tmp = md5->d;
	md5->d = md5->c;
	md5->c = md5->b;
	md5->b = md5->b + _ROT_L((md5->a + md5->fghi + g_t[i] + md5->hash[j]),
	g_s[i]);
	md5->a = md5->tmp;
}

int			ft_h_first(t_h *h)
{
	h->h0 = 0x67452301;
	h->h1 = 0xefcdab89;
	h->h2 = 0x98badcfe;
	h->h3 = 0x10325476;
	h->len_buf = h->len_msg + 1;
	while (h->len_buf % 64 != 56)
		h->len_buf++;
	if (!(h->buf = (char *)malloc(h->len_buf + 64)))
		return (write(1, "Error\n", 6));
	ft_bzero(h->buf, h->len_buf + 64);
	h->buf = (char *)ft_strcpy((char *)h->buf, h->msg);
	*(uint32_t *)(h->buf + h->len_msg) = 0x80;
	*(uint64_t *)(h->buf + h->len_buf) = (uint64_t)(8 * h->len_msg);
	h->count = 0;
	return (0);
}

int			ft_get_hash_md5(t_h *h)
{
	int i;

	if ((i = ft_h_first(h)) != 0)
		return (i);
	while (h->count < h->len_buf)
	{
		h->hash = (uint32_t *)(h->buf + h->count);
		h->a = h->h0;
		h->b = h->h1;
		h->c = h->h2;
		h->d = h->h3;
		i = -1;
		while (++i < 64)
			ft_md5_hashing(h, i, i);
		h->h0 += h->a;
		h->h1 += h->b;
		h->h2 += h->c;
		h->h3 += h->d;
		h->count += 64;
	}
	ft_memdel((void **)&h->buf);
	return (0);
}
