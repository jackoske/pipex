/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lsttoarr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 15:21:14 by Jskehan           #+#    #+#             */
/*   Updated: 2024/04/08 15:27:01 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 Allocates (with malloc(3)) and returns a “fresh”
array of strings ending with NULL,
*/
char	**ft_lsttoarr(t_list *lst)
{
	int		size;
	char	**arr;
	int		i;

	i = -1;
	size = ft_lstsize(lst);
	arr = malloc((size + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	while (++i < size)
	{
		arr[i] = lst->content;
		lst = lst->next;
	}
	arr[size] = NULL;
	return (arr);
}
