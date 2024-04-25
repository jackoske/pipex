/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 17:59:43 by Jskehan           #+#    #+#             */
/*   Updated: 2024/04/25 11:25:57 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	handle_input_file(char **av, int *i, int *fd_in)
{
	*i = 2;
	*fd_in = open_file(av[1], 0);
	dup2(*fd_in, 0);
	close(*fd_in);
}

void	ft_error(void)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
}

void	open_fd_out(int argc, char **argv, int *fd_out)
{
	if (ft_strcmp(argv[1], "here_doc") == 0)
		*fd_out = open_file(argv[argc - 1], 2);
	else
		*fd_out = open_file(argv[argc - 1], 1);
	if (*fd_out == -1)
	{
		*fd_out = open("/dev/null", O_WRONLY);
		if (*fd_out == -1)
			perror("Error opening /dev/null");
	}
}
