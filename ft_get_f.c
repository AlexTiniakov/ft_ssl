/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_f.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otiniako <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/25 19:49:58 by otiniako          #+#    #+#             */
/*   Updated: 2018/07/25 19:50:00 by otiniako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>

void	ft_get(char *str, t_h *h)
{
	h->alg = str;
	h->func = ft_get_f(str[0]);
	h->print = ft_get_p(str[0]);
}

t_f		ft_get_f(char c)
{
	static t_f *fun = NULL;

	if (fun == NULL)
		if ((fun = ft_memalloc(sizeof(*fun) * 256)) != NULL)
		{
			fun['m'] = &ft_get_hash_md5;
			fun['s'] = &ft_get_hash_sha;
		}
	return (fun[(int)c]);
}

t_f		ft_get_p(char c)
{
	static t_f *fun = NULL;

	if (fun == NULL)
		if ((fun = ft_memalloc(sizeof(*fun) * 256)) != NULL)
		{
			fun['m'] = &ft_print_md5;
			fun['s'] = &ft_print_sha;
		}
	return (fun[(int)c]);
}
