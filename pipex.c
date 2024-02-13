/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 13:09:30 by Jskehan           #+#    #+#             */
/*   Updated: 2024/02/12 12:52:47 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child(char **argv, char **envp, t_pipex *pipex)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid > 0)
	{
		waitpid(pid, &status, 0);
		close(pipex->out_fd);
	}
	else
	{
		dup2(pipex->out_fd, STDOUT_FILENO);
		close(pipex->out_fd);
		dup2(pipex->in_fd, STDIN_FILENO);
		close(pipex->in_fd);
		execve(pipex->cmd_paths[1], pipex->cmd_args[1], envp);
		perror("execve");
		exit(EXIT_FAILURE);
	}
}

void	parent(char **argv, char **envp, t_pipex *pipex)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid > 0)
	{
		waitpid(pid, &status, 0);
		close(pipex->in_fd);
	}
	else
	{
		dup2(pipex->in_fd, STDIN_FILENO);
		close(pipex->in_fd);
		dup2(pipex->out_fd, STDOUT_FILENO);
		close(pipex->out_fd);
		execve(pipex->cmd_paths[0], pipex->cmd_args[0], envp);
		perror("execve");
		exit(EXIT_FAILURE);
	}
}

void	init_pipex(t_pipex *pipex)
{
	pipex->in_fd = 0;
	pipex->out_fd = 0;
	pipex->here_doc = 0;
	pipex->is_invalid_infile = 0;
	pipex->cmd_paths = NULL;
	pipex->cmd_args = NULL;
	pipex->cmd_count = 0;
}

void	ft_check_args(int argc, char **argv, t_pipex *pipex)
{
	if (argc < 5)
	{
		ft_putstr_fd("Error: Invalid number of arguments.\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	if (strcmp(argv[1], "here_doc") == 0)
	{
		pipex->here_doc = 1;
	}
	else
	{
		if (access(argv[1], F_OK) == -1)
		{
			ft_putstr_fd("Error: I file does not exist.\n", STDERR_FILENO);
			exit(EXIT_FAILURE);
		}
		if (access(argv[1], R_OK) == -1)
		{
			ft_putstr_fd("Error: I file is not readable.\n", STDERR_FILENO);
			exit(EXIT_FAILURE);
		}
		if (access(argv[argc - 1], F_OK) == -1)
		{
			ft_putstr_fd("Error: O file does not exist.\n", STDERR_FILENO);
			exit(EXIT_FAILURE);
		}
		if (access(argv[argc - 1], W_OK) == -1)
		{
			ft_putstr_fd("Error: O file is not writable.\n", STDERR_FILENO);
			exit(EXIT_FAILURE);
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	char	*args[3];
	char	**allpath;
	int		i;

	i = -1;
	init_pipex(&pipex);
	ft_check_args(argc, argv, &pipex);
	allpath = ft_split(my_getenv("PATH", envp), ':');
	while (allpath[++i])
		ft_printf("%s \n", allpath[i]);
	return (0);
}
