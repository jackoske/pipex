/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 12:10:17 by Jskehan           #+#    #+#             */
/*   Updated: 2024/04/10 20:44:07 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	ft_check_args(int argc, char **argv)
{
	if ((argc < 5) || 
		(ft_strcmp(argv[1], "here_doc") == 0 && argc < 6))
	{
		ft_putstr_fd("pipex: too few arguments\n", 2);
		exit(EXIT_FAILURE);
	}
	else if (access(argv[1], F_OK) == -1)
	{
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
	}
	else if (access(argv[1], R_OK) == -1)
	{
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
	}
}
