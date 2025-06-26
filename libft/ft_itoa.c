/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalizio <jgalizio@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 12:06:14 by jgalizio          #+#    #+#             */
/*   Updated: 2024/09/19 16:12:24 by jgalizio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_numlen(int nb)
{
	size_t	len;

	len = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
		len++;
	while (nb)
	{
		nb /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*str;
	size_t	len;
	int		sign;

	len = ft_numlen(n);
	str = ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (NULL);
	sign = 1;
	if (n < 0)
	{
		str[0] = '-';
		sign = -1;
	}
	if (n == 0)
		str[0] = '0';
	while (n)
	{
		str[--len] = (n % 10) * sign + '0';
		n /= 10;
	}
	return (str);
}
