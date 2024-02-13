/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 16:50:02 by Jskehan           #+#    #+#             */
/*   Updated: 2023/12/18 11:37:49 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_formatargs(va_list args, const char format)
{
	int	print_length;

	print_length = 0;
	if (format == 'c')
		print_length += ft_putchar(va_arg(args, int));
	else if (format == 's')
		print_length += ft_putstr(va_arg(args, char *));
	else if ((format == 'd') || (format == 'i'))
		print_length += ft_putnbr(va_arg(args, int));
	else if (format == 'u')
		print_length += ft_putunsnbr(va_arg(args, unsigned int));
	else if (format == 'p')
		print_length += printpointer(va_arg(args, uintptr_t), 0);
	else if (format == 'x')
		print_length += printhexrecursive(va_arg(args, unsigned int), 0);
	else if (format == 'X')
		print_length += printhexrecursive(va_arg(args, unsigned int), 1);
	else if (format == '%')
		print_length += ft_putchar('%');
	return (print_length);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	va_list	args;
	int		print_length;

	if (str == NULL)
		return (-1);
	i = 0;
	print_length = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			print_length += ft_formatargs(args, str[i + 1]);
			i++;
		}
		else
			print_length += ft_putchar(str[i]);
		i++;
	}
	va_end(args);
	return (print_length);
}
