/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otiniako <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 20:04:06 by otiniako          #+#    #+#             */
/*   Updated: 2018/07/26 20:04:07 by otiniako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>

t_l	*ft_init_node(char *key, t_f value, t_l *list)
{
	if ((list = (t_l *)malloc(sizeof(t_l))) != NULL)
	{
		list->key = ft_strcpy(ft_strnew(ft_strlen(key)), key);
		list->value = value;
		list->next = NULL;
	}
	return (list);
}

t_l	*ft_init_list(void)
{
	static t_l	*list = NULL;

	if (list == NULL)
	{
		list = ft_init_node("md5", &ft_md5, NULL);
		list->next = ft_init_node("sha256", &ft_sha256, NULL);
		list->next->next = ft_init_node("usage", &ft_usage, NULL);
	}
	return (list);
}

t_f	ft_get_command(char *str, t_l *list)
{
	if (!list)
		return (NULL);
	else if (ft_strcmp(str, list->key))
		return (ft_get_command(str, list->next));
	else
		return (list->value);
}
