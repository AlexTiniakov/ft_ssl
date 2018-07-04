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
# define _ROT(x, y) ((x << y) | (x >> (32 - y)))
# include "libft.h"

typedef struct		s_md5
{
	int				p : 1;
	int				q : 1;
	int				r : 1;
	int				s : 1;
	uint32_t		AA;
	uint32_t		BB;
	uint32_t		CC;
	uint32_t		DD;
	uint32_t		A;
	uint32_t		B;
	uint32_t		C;
	uint32_t		D;
	uint32_t		len_msg;
	uint32_t		len_buf;
	uint32_t		count;
	char			*msg;
	char			*buf;
	uint32_t		*hash;
	uint32_t		FGHI;
	uint32_t		tmp;
}					t_md5;

typedef struct		s_sha256
{
	int				p : 1;
	int				q : 1;
	int				r : 1;
	int				s : 1;
}					t_sha256;

void	ft_md5(int ac, char **av);
void	ft_sha256(int ac, char **av);
void    ft_get_hash_md5(t_md5 *md5);

#endif
