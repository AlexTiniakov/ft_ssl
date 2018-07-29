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
# define _PS ssl->s ? "\"" : ""
# define _PRINT _PS, ssl->s ? h->msg : h->file_name, _PS
# define _F(x, y, z) ((x & y) | ((~x) & z))
# define _G(x, y, z) ((x & z) | (y & (~z)))
# define _H(x, y, z) (x ^ y ^ z)
# define _I(x, y, z) (y ^ (x | (~z)))
# define _ROT_L(x, y) (((x) << (y)) | ((x) >> (32 - (y))))
# define _ROT_R(x, y) ((((unsigned int)(x) >> (y))) | ((x) << (32 - (y))))
# include "libft.h"

typedef void		(*t_f)();

typedef struct		s_l
{
	char			*key;
	t_f				value;
	struct s_l		*next;
}					t_l;

typedef struct		s_ssl
{
	int				std : 1;
	int				p : 1;
	int				q : 1;
	int				r : 1;
	int				s : 1;
	int				ac;
	char			**av;
	t_f				func;
}					t_ssl;

typedef struct		s_h
{
	int				i;
	int				j;
	uint32_t		h0;
	uint32_t		h1;
	uint32_t		h2;
	uint32_t		h3;
	uint32_t		h4;
	uint32_t		h5;
	uint32_t		h6;
	uint32_t		h7;
	uint32_t		len_msg;
	uint32_t		len_buf;
	uint32_t		count;
	int				set;
	char			*buf;
	char			*file_name;
	char			*msg;
	char			*alg;
	char			rez[100];
	uint32_t		*hash;
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
	t_f				func;
	t_f				print;
}					t_h;

char				*ft_read_from_stdin(char *str, char *buf, int ret);
int					read_from_stdin(t_h *h, t_ssl *ssl);
int					msg_file(t_h *h, char *name);
int					msg_str(t_h *h, char *str);
t_f					ft_get_command(char *str, t_l *list);
t_l					*ft_init_list();
t_l					*ft_init_node(char *key, t_f value, t_l *list);
void				ft_md5(t_ssl *ssl);
int					ft_get_hash_md5(t_h *h);
void				ft_sha256(t_ssl *ssl);
int					ft_get_hash_sha(t_h *h);
void				ft_usage(t_ssl *ssl);

#endif
