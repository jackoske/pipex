/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 13:20:50 by Jskehan           #+#    #+#             */
/*   Updated: 2024/04/09 15:52:32 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

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
	parse_and_execute_command(argv[argc - 2], envp);
	return (0);
}
