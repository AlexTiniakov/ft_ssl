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
# include "libft.h"

typedef struct		s_hesh
{
	unsigned int	str[16];
	struct s_hesh	*next;
}					t_hesh;

typedef struct		s_md5
{
	int				p : 1;
	int				q : 1;
	int				r : 1;
	int				s : 1;
	unsigned int	A;
	unsigned int	B;
	unsigned int	C;
	unsigned int	D;
	char			*str;
	t_hesh			*hesh;
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

#endif
