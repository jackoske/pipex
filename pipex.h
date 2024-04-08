/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 12:57:11 by Jskehan           #+#    #+#             */
/*   Updated: 2024/04/08 16:49:08 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "lib/gnl/get_next_line.h"
# include "lib/libftprint/ft_printf.h"
# include <ctype.h>
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_pipex
{
	int		in_fd;
	int		out_fd;
	int		here_doc;
	int		is_invalid_infile;
	char	**cmd_paths;
	char	***cmd_args;
	int		cmd_count;
}			t_pipex;


typedef struct s_parser
{
    t_list	*parts;
    char	*part;
    int		in_single_quotes;
    int		in_double_quotes;
}				t_parser;

void		print_usage_and_exit(int n_exit);
int			open_file_with_mode(char *file, int n);
char		*get_env_variable(char *name, char **env);
char		*find_command_path(char *cmd, char **env);
void		exec(char *cmd, char **env);
void		free_string_array(char **tab);
char		**split_command(char *cmd, char **envp);
void		parse_and_execute_command(char *cmd, char **envp);
void		setup_here_doc(char **argv);
void		create_and_exec_pipe_process(char *cmd, char **envp);
void		ft_check_args(int argc, char **argv);
char	**split_cmd_into_parts(char *cmd);
#endif
