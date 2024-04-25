/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 13:56:12 by Jskehan           #+#    #+#             */
/*   Updated: 2024/04/25 11:24:54 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	exec(char *cmd, char **env)
{
	char	**s_cmd;
	char	*path;

	if (!cmd || !*cmd)
	{
		ft_putstr_fd("pipex: empty command", 2);
		exit(1);
	}
	s_cmd = split_cmd_into_parts(cmd);
	path = get_path(s_cmd[0], env);
	if (execve(path, s_cmd, env) == -1)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putendl_fd(s_cmd[0], 2);
		ft_free_tab(s_cmd);
		exit(127);
	}
}

void	here_doc_put_in(char **argv, int *p_fd)
{
	char	*line;

	close(p_fd[0]);
	while (1)
	{
		line = get_next_line(0, argv[2]);
		if (ft_strncmp(line, argv[2], ft_strlen(argv[2])) == 0)
		{
			free(line);
			close(p_fd[1]);
			exit(0);
		}
		ft_putstr_fd(line, p_fd[1]);
		free(line);
	}
}

void	here_doc(char **argv)
{
	int		p_fd[2];
	pid_t	pid;

	if (pipe(p_fd) == -1)
		exit(0);
	pid = fork();
	if (pid == -1)
		exit(0);
	if (!pid)
		here_doc_put_in(argv, p_fd);
	else
	{
		close(p_fd[1]);
		dup2(p_fd[0], 0);
		close(p_fd[0]);
		wait(NULL);
	}
}

void	do_pipe(char *cmd, char **env)
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
}

int	main(int argc, char **argv, char **env)
{
	int	i;
	int	fd_in;
	int	fd_out;

	ft_check_args(argc, argv);
	if (ft_strcmp(argv[1], "here_doc") == 0)
	{
		i = 3;
		here_doc(argv);
	}
	else
		handle_input_file(argv, &i, &fd_in);
	while (i < argc - 2)
		do_pipe(argv[i++], env);
	open_fd_out(argc, argv, &fd_out);
	dup2(fd_out, 1);
	close(fd_out);
	exec(argv[argc - 2], env);
	if (access(argv[argc - 1], F_OK) != -1 
		&& access(argv[argc - 1], R_OK) == -1)
	{
		ft_error();
		return (1);
	}
	return (0);
}
