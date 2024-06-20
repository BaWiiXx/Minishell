/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdany <bdany@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 16:35:46 by bdany             #+#    #+#             */
/*   Updated: 2023/11/17 16:35:40 by bdany            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		first;
	int		last;
	char	*result;

	first = 0;
	last = 0;
	if (!s1)
		return (NULL);
	while (s1[first] && ft_strchr(set, s1[first]))
		first++;
	last = ft_strlen(s1);
	while (last > 0 && ft_strchr(set, s1[last - 1]))
		last--;
	result = ft_substr(s1, first, last - first);
	return (result);
}
