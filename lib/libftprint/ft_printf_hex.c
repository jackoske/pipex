/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 13:05:07 by Jskehan           #+#    #+#             */
/*   Updated: 2023/12/04 13:08:13 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	printhexrecursive(unsigned long long number, int uppercase)
{
	char				hexdigit;
	unsigned long long	remainder;
	int					count;

	remainder = number % 16;
	count = 0;
	if (remainder < 10)
		hexdigit = remainder + '0';
	else if (uppercase)
		hexdigit = (remainder - 10 + 'A');
	else
		hexdigit = (remainder - 10 + 'a');
	if (number / 16 > 0)
		count += printhexrecursive(number / 16, uppercase);
	ft_putchar(hexdigit);
	count++;
	return (count);
}

int	printpointer(unsigned long long number, int uppercase)
{
	int	print_length;

	print_length = 0;
	if (number)
	{
		print_length += ft_putstr("0x");
		print_length += printhexrecursive(number, uppercase);
	}
	else
		print_length += ft_putstr("(nil)");
	return (print_length);
}
