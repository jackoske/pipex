/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_unsigned.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 20:59:24 by jskehan           #+#    #+#             */
/*   Updated: 2023/12/04 13:06:19 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	numberlength(unsigned int n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		count++;
		n /= 10;
	}
	return (count);
}

char	*ft_uitoa(unsigned int n)
{
	int		numlen;
	char	*str;

	numlen = numberlength(n);
	str = (char *)malloc((numlen + 1));
	if (!str)
		return (NULL);
	str[numlen] = '\0';
	while (numlen--)
	{
		str[numlen] = (n % 10) + '0';
		n /= 10;
	}
	return (str);
}
