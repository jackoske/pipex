/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:22:57 by Jskehan           #+#    #+#             */
/*   Updated: 2024/04/09 15:25:10 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	create_pipe(int *p_fd)
{
	if (pipe(p_fd) == -1)
	{
		ft_putstr_fd(strerror(errno), 2);
		exit(EXIT_FAILURE);
	}
}

pid_t	fork_process(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		ft_putstr_fd(strerror(errno), 2);
		exit(EXIT_FAILURE);
	}
	return (pid);
}

void	execute_child_process(int *p_fd, char *cmd, char **envp)
{
	close(p_fd[0]);
	dup2(p_fd[1], 1);
	parse_and_execute_command(cmd, envp);
}

void	execute_parent_process(int *p_fd)
{
	close(p_fd[1]);
	dup2(p_fd[0], 0);
	wait(NULL);
}

void	create_and_exec_pipe_process(char *cmd, char **envp)
{
	pid_t	pid;
	int		p_fd[2];

	create_pipe(p_fd);
	pid = fork_process();
	if (!pid)
		execute_child_process(p_fd, cmd, envp);
	else
		execute_parent_process(p_fd);
}
