/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdany <bdany@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 11:51:42 by bdany             #+#    #+#             */
/*   Updated: 2023/11/17 16:16:27 by bdany            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_nbr(int nb)
{
	int	i;

	i = 0;
	if (nb < 0)
	{
		nb = -nb;
		i++;
	}
	if (nb == 0)
		i++;
	while (nb != 0)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char		*tab;
	int			count;
	int			i;
	long int	nb;

	nb = n;
	count = count_nbr(nb);
	tab = malloc(sizeof(char) * count + 1);
	if (!tab)
		return (NULL);
	i = 0;
	tab[count] = '\0';
	if (nb < 0)
	{
		nb *= -1;
		tab[0] = '-';
		i++;
	}
	while (count > i)
	{
		count--;
		tab[count] = (nb % 10) + '0';
		nb /= 10;
	}
	return (tab);
}
