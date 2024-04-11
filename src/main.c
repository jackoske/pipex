/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 13:20:50 by Jskehan           #+#    #+#             */
/*   Updated: 2024/04/11 11:45:03 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int	fd[2];
	int i;
	
	ft_check_args(argc, argv);
	i = 1;
	if (ft_strcmp(argv[1], "here_doc") == 0)
	{
		handle_here_doc(argv, fd);
		dup2(fd[IN], 0);
    	close(fd[IN]);
		i++;
	}
	else
		handle_reg_input(argv, fd);
	pipe_process(argv, argc, envp);
	fd[OUT] = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd[OUT] < 0)
	{
		ft_putstr_fd(strerror(errno), 2);
		exit(EXIT_FAILURE);
	}
	dup2(fd[OUT], 1);
	while(++i < argc - 1)
		parse_and_execute_command(argv[i], envp);
	return (0);
}
