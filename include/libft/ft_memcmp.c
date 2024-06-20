/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdany <bdany@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:42:41 by bdany             #+#    #+#             */
/*   Updated: 2023/11/17 16:23:49 by bdany            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	unsigned const char	*str;
	unsigned const char	*chr;

	str = s1;
	chr = s2;
	i = 0;
	while (i < n)
	{
		if (str[i] != chr[i])
			return (str[i] - chr[i]);
		i++;
	}
	return (0);
}
