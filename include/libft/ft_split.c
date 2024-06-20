/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdany <bdany@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:10:31 by bdany             #+#    #+#             */
/*   Updated: 2023/11/22 16:26:04 by bdany            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	ft_count_word(const char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (*s != '\0' && *s == c)
		s++;
	while (s[i])
	{
		if ((s[i] == c && s[i - 1] != c) || (s[i + 1] == 0 && s[i] != c))
			count ++;
		i++;
	}
	return (count);
}

static char	**free_word(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
	return (NULL);
}

static char	**malloc_tab(char **tab, const char *s, char c)
{
	int	i;
	int	m;
	int	t;

	t = 0;
	i = 0;
	while (t < ft_count_word(s, c) && s[i])
	{
		m = 0;
		while (s[i] == c)
			i++;
		while (s[i] != c && s[i])
		{
			i++;
			m++;
		}
		tab[t] = ft_substr(s, i - m, m);
		if (!tab[t])
			return (free_word(tab));
		t++;
	}
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;

	if (!s)
		return (NULL);
	tab = ft_calloc(sizeof(char *), ft_count_word(s, c) + 1);
	if (!tab)
		return (NULL);
	tab = malloc_tab(tab, s, c);
	if (!tab)
		return (NULL);
	return (tab);
}
