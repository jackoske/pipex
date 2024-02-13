/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 21:08:28 by jskehan           #+#    #+#             */
/*   Updated: 2024/02/09 13:58:43 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"
# include <stdarg.h>
# include <stdio.h>
# include <unistd.h>

int		ft_putchar(char c);
int		ft_putstr(char *str);
int		ft_putnbr(int n);
char	*ft_uitoa(unsigned int n);
int		ft_putunsnbr(unsigned int n);
int		printpointer(unsigned long long number, int uppercase);
int		printhexrecursive(unsigned long long number, int uppercase);
int		ft_printf(const char *format, ...);

#endif
