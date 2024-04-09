/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 12:10:17 by Jskehan           #+#    #+#             */
/*   Updated: 2024/04/09 17:34:46 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	parse_and_execute_command(char *cmd, char **envp)
{
	char	**s_cmd;
	char	*path;

	s_cmd = split_command(cmd, envp);
	path = find_command_path(s_cmd[0], envp);
	if (strcmp(s_cmd[0], "sleep") == 0)
		sleep(ft_atoi(s_cmd[1]));
	else
	{
		if (execve(path, s_cmd, envp) == -1)
		{
			ft_putstr_fd("pipex: command not found: ", 2);
			ft_putendl_fd(s_cmd[0], 2);
			free_string_array(s_cmd);
			exit(EXIT_FAILURE);
		}
	}
}

void	process_here_doc_input(char **argv, int *p_fd)
{
	char	*ret;

	close(p_fd[0]);
	while (1)
	{
		ret = get_next_line(0);
		if (ft_strncmp(ret, argv[2], ft_strlen(argv[2])) == 0)
		{
			free(ret);
			exit(EXIT_FAILURE);
		}
		ft_putstr_fd(ret, p_fd[1]);
		free(ret);
	}
}

void	setup_here_doc(char **argv)
{
	int		p_fd[2];
	pid_t	pid;

	if (pipe(p_fd) == -1)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (!pid)
		process_here_doc_input(argv, p_fd);
	else
	{
		close(p_fd[1]);
		dup2(p_fd[0], 0);
		wait(NULL);
	}
}

void	ft_check_args(int argc, char **argv)
{
	if (argc < 5)
	{
		ft_putstr_fd("pipex: too few arguments\n", 2);
		exit(EXIT_FAILURE);
	}
	if (ft_strcmp(argv[1], "here_doc") == 0 && argc < 6)
	{
		ft_putstr_fd("pipex: too few arguments\n", 2);
		exit(EXIT_FAILURE);
	}
}
