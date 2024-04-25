/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 13:41:44 by Jskehan           #+#    #+#             */
/*   Updated: 2023/12/04 13:06:30 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

int	ft_putstr(char *str)
{
	size_t	i;

	if (str == NULL)
	{
		ft_putstr("(null)");
		return (6);
	}
	i = 0;
	while (*str)
	{
		i += ft_putchar(*str);
		str++;
	}
	return (i);
}

int	ft_putnbr(int n)
{
	int		len;
	char	*num;

	len = 0;
	num = ft_itoa(n);
	len = ft_putstr(num);
	free(num);
	return (len);
}

int	ft_putunsnbr(unsigned int n)
{
	int		len;
	char	*num;

	len = 0;
	num = ft_uitoa(n);
	len = ft_putstr(num);
	free(num);
	return (len);
}
