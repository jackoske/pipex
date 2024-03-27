/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 13:20:50 by Jskehan           #+#    #+#             */
/*   Updated: 2024/03/27 17:44:57 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <ctype.h>

char **split_command(const char *cmd) {
    char **result = NULL;
    int count = 0;
    int capacity = 10;
    char buffer[256];
    int buf_index = 0;
    char quote_char = '\0';

    result = malloc(capacity * sizeof(char *));
    if (!result) return NULL;

    while (1) {
        char c = *cmd++;
        if ((c == ' ' && quote_char == '\0') || c == '\0') {
            if (buf_index != 0) {
                buffer[buf_index] = '\0';
                if (count == capacity) {
                    capacity *= 2;
                    result = realloc(result, capacity * sizeof(char *));
                    if (!result) return NULL;
                }
                result[count++] = strdup(buffer);
                buf_index = 0;
            }
            if (c == '\0') break;
        } else if (c == '"' || c == '\'') {
            if (quote_char == '\0') quote_char = c;
            else if (quote_char == c) quote_char = '\0';
        } else if (!isspace(c) || quote_char != '\0') {
            buffer[buf_index++] = c;
        }
    }

    result[count] = NULL;
    return result;
}

void	execute_command(char *cmd, char **envp)
{
	char	**s_cmd;
	char	*path;

	printf("Executing command: %s\n", cmd);
	s_cmd = split_command(cmd);
	path = find_command_path(s_cmd[0], envp);
	if (execve(path, s_cmd, envp) == -1)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putendl_fd(s_cmd[0], 2);
		free_string_array(s_cmd);
		exit(EXIT_FAILURE);
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

void	create_and_exec_pipe_process(char *cmd, char **envp)
{
	pid_t	pid;
	int		p_fd[2];

	if (pipe(p_fd) == -1)
	{
		perror("pipe failed");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork failed");
		exit(EXIT_FAILURE);
	}
	if (!pid)
	{
		close(p_fd[0]);
		dup2(p_fd[1], 1);
		execute_command(cmd, envp);
	}
	else
	{
		close(p_fd[1]);
		dup2(p_fd[0], 0);
	}
}
void	ft_check_args(int argc, char **argv)
{
	if (argc < 5)
	{
		perror("pipex: too few arguments");
		exit(EXIT_FAILURE);
	}
	else if (access(argv[1], F_OK) == -1)
	{
		perror("pipex: input file");
		exit(EXIT_FAILURE);
	}
	else if (access(argv[1], R_OK) == -1)
	{
		perror("pipex: cannot read input file");
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, char **argv, char **envp)
{
	int	i;
	int	fd_in;
	int	fd_out;

	ft_check_args(argc, argv);
	if (ft_strcmp(argv[1], "here_doc") == 0)
	{
		if (argc < 6)
			print_usage_and_exit(1);
		i = 3;
		fd_out = open_file_with_mode(argv[argc - 1], 2);
		setup_here_doc(argv);
	}
	else
	{
		i = 2;
		fd_in = open_file_with_mode(argv[1], 0);
		fd_out = open_file_with_mode(argv[argc - 1], 1);
		dup2(fd_in, 0);
	}
	while (i < argc - 2)
		create_and_exec_pipe_process(argv[i++], envp);
	dup2(fd_out, 1);
	execute_command(argv[argc - 2], envp);
	return (0);
}
