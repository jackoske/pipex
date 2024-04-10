/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 13:20:50 by Jskehan           #+#    #+#             */
/*   Updated: 2024/04/10 20:43:45 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int	i;
	int	fd[2];
	int	p_fd[2];

	i = 1;
	ft_check_args(argc, argv);
	if (ft_strcmp(argv[1], "here_doc") == 0)
	{
		handle_here_doc(argc, argv, fd);
		i++;
	}
	else
		handle_reg_input(argc, argv, fd, p_fd);
	while (++i < argc - 2)
		pipe_process(argv[i], envp);
	dup2(fd[OUT], 1);
	return (parse_and_execute_command(argv[argc - 2], envp));
}
