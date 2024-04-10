/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 12:57:11 by Jskehan           #+#    #+#             */
/*   Updated: 2024/04/11 00:32:33 by Jskehan          ###   ########.fr       */
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

typedef enum e_fd
{
	IN,
	OUT
}			t_fd;

typedef enum e_cmd_string
{
	PARTS,
	SINGLE_QUOTES,
	DOUBLE_QUOTES
}			t_cmd_string;

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
}			t_parser;

// Command parsing
void		process_character(char c, t_parser *parser);
char		**split_cmd_into_parts(char *cmd);
size_t		count_words(char *str, char c);

// Command execution
void		exec(char *cmd, char **env);
int			parse_and_execute_command(char *cmd, char **envp);
void		pipe_process(char *cmds, char **envp);

// Input handling
void		handle_here_doc(int argc, char **argv, int *fd);
void		handle_reg_input(int argc, char **argv, int *fd, int *p_fd);

// Utility functions
void		print_usage_and_exit(int n_exit);
int			open_file_with_mode(char *file, int n);
char		*get_env_variable(char *name, char **env);
char		*find_command_path(char *cmd, char **env);
void		free_string_array(char **tab);
char		**split_command(char *cmd, char **envp);
void		ft_check_args(int argc, char **argv);

#endif
