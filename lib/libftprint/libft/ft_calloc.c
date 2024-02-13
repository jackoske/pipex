/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 09:36:49 by Jskehan           #+#    #+#             */
/*   Updated: 2023/11/22 17:51:54 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*allocation;

	allocation = malloc(nmemb * size);
	if (allocation == NULL)
		return (NULL);
	ft_bzero(allocation, nmemb * size);
	return (allocation);
}
