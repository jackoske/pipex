/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 12:57:11 by Jskehan           #+#    #+#             */
/*   Updated: 2024/03/26 19:08:18 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "lib/gnl/get_next_line.h"
# include "lib/libftprint/ft_printf.h"
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

void		print_usage_and_exit(int n_exit);
int			open_file_with_mode(char *file, int n);
char		*get_env_variable(char *name, char **env);
char		*find_command_path(char *cmd, char **env);
void		exec(char *cmd, char **env);
void		free_string_array(char **tab);

#endif
