/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:22:57 by Jskehan           #+#    #+#             */
/*   Updated: 2024/04/11 11:12:15 by Jskehan          ###   ########.fr       */
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
	int	ret;

	close(p_fd[0]);
	dup2(p_fd[1], 1);
	ret = parse_and_execute_command(cmd, envp);
	exit(ret);
}

void	execute_parent_process(int *p_fd)
{
	close(p_fd[1]);
	dup2(p_fd[0], 0);
}

void	pipe_process(char **argv, int argc, char **envp)
{
	pid_t	*pids;
	int		i;
	int		p_fd[2];

	pids = malloc((argc - 3) * sizeof(pid_t));
	if (!pids)
	{
		ft_putstr_fd(strerror(errno), 2);
		exit(EXIT_FAILURE);
	}
	i = 2;
	while (++i < argc - 2)
	{
		create_pipe(p_fd);
		pids[i - 1] = fork_process();
		if (!pids[i - 1])
		{
			execute_child_process(p_fd, argv[i], envp);
			exit(EXIT_FAILURE);
		}
		else
			close(p_fd[1]);
	}
	i = 0;
	while (++i < argc - 2)
		waitpid(pids[i - 1], NULL, 0);
	free(pids);
}
