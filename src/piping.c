/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 17:59:43 by Jskehan           #+#    #+#             */
/*   Updated: 2024/04/25 14:54:28 by Jskehan          ###   ########.fr       */
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
	ft_putstr_fd("pipex :", 2);
	ft_putendl_fd(strerror(errno), 2);
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

pid_t	do_pipe(char *cmd, char **env)
{
	pid_t	pid;
	int		p_fd[2];

	if (pipe(p_fd) == -1)
		exit(0);
	pid = fork();
	if (pid == -1)
		exit(0);
	if (!pid)
	{
		close(p_fd[0]);
		dup2(p_fd[1], 1);
		close(p_fd[1]);
		exec(cmd, env);
	}
	else
	{
		close(p_fd[1]);
		dup2(p_fd[0], 0);
		close(p_fd[0]);
	}
	return (pid);
}

void	check_access(int argc, char **argv)
{
	if (access(argv[argc - 1], F_OK) != -1 
		&& access(argv[argc - 1], R_OK) == -1)
	{
		ft_putstr_fd("pipex :", 2);
		ft_putendl_fd(strerror(errno), 2);
		exit(1);
	}
}
