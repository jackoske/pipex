/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 13:56:12 by Jskehan           #+#    #+#             */
/*   Updated: 2024/04/25 15:03:17 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	handle_piping(int argc, char **argv, int i, char **env)
{
	int		j;
	pid_t	pids[100];

	ft_memset(pids, 0, sizeof(pids));
	j = i;
	while (j < argc - 2)
	{
		pids[j - 2] = do_pipe(argv[j], env);
		j++;
	}
	j = i;
	while (j < argc - 2)
	{
		waitpid(pids[j], NULL, 0);
		j++;
	}
}

int	main(int argc, char **argv, char **env)
{
	int	i;
	int	fd_in;
	int	fd_out;
	int	last_cmd_status;

	ft_check_args(argc, argv);
	i = 2;
	if (ft_strcmp(argv[1], "here_doc") == 0)
	{
		i = 3;
		here_doc(argv);
	}
	else
		handle_input_file(argv, &i, &fd_in);
	handle_piping(argc, argv, i, env);
	open_fd_out(argc, argv, &fd_out);
	dup2(fd_out, 1);
	close(fd_out);
	check_access(argc, argv);
	last_cmd_status = execute_last_cmd(argc, argv, env);
	return (last_cmd_status);
}
