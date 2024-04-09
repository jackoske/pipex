/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:51:34 by Jskehan           #+#    #+#             */
/*   Updated: 2024/04/09 17:52:39 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void free_parts(t_list *parts)
{
	t_list	*temp;

	while (parts)
	{
		temp = parts;
		parts = parts->next;
		free(temp->content);
		free(temp);
	}
}
