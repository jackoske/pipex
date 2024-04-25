/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 11:59:37 by Jskehan           #+#    #+#             */
/*   Updated: 2024/04/25 14:42:47 by Jskehan          ###   ########.fr       */
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

typedef struct s_parser
{
	t_list	*parts;
	char	*part;
	int		in_single_quotes;
	int		in_double_quotes;
}			t_parser;

void		exit_handler(int n_exit);
int			open_file(char *file, int n);
char		*my_getenv(char *name, char **env);
char		**split_cmd_into_parts(char *cmd);
char		*get_path(char *cmd, char **env);
void		exec(char *cmd, char **env);
void		ft_free_tab(char **tab);
void		handle_here_doc(int ac, char **av, int *i);
void		handle_input_file(char **av, int *i, int *fd_in);
void		ft_check_args(int argc, char **argv);
void		here_doc(char **av);
void		open_fd_out(int argc, char **argv, int *fd_out);
void		ft_error(void);
int			execute_last_cmd(int argc, char **argv, char **env);
pid_t		do_pipe(char *cmd, char **env);
void		check_access(int argc, char **argv);
#endif
