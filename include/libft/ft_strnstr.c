/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdany <bdany@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 09:58:35 by bdany             #+#    #+#             */
/*   Updated: 2023/11/22 10:42:55 by bdany            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *tofind, size_t len)
{
	size_t	i;
	size_t	count_len;
	size_t	j;

	i = 0;
	count_len = (size_t)ft_strlen((char *)tofind);
	if (tofind[0] == '\0')
		return ((char *)str);
	if (len == 0)
		return (NULL);
	while (str[i])
	{
		j = 0;
		while (tofind[j] == str[i + j]
			&& str[i + j] && i + j < len && tofind[j])
		{
			j++;
			if ((j == len || j == count_len) && (count_len <= len))
				return ((char *)&str[i]);
		}
		i++;
	}
	return (NULL);
}
