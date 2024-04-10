/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 16:53:39 by Jskehan           #+#    #+#             */
/*   Updated: 2024/04/10 22:22:14 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

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

void	handle_here_doc(int argc, char **argv, int *fd)
{
	fd[OUT] = open_file_with_mode(argv[argc - 1], 2);
	setup_here_doc(argv);
}

void	handle_reg_input(int argc, char **argv, int *fd, int *p_fd)
{
	fd[IN] = open_file_with_mode(argv[1], 0);
	if (fd[IN] == -1)
	{
		if (pipe(p_fd) == -1)
			exit(EXIT_FAILURE);
		fd[IN] = p_fd[1];
	}
	fd[OUT] = open_file_with_mode(argv[argc - 1], 1);
	if (fd[OUT] == -1)
		exit(EXIT_FAILURE);
	dup2(fd[IN], 0);
}
