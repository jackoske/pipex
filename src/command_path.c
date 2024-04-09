/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 11:51:51 by Jskehan           #+#    #+#             */
/*   Updated: 2024/04/09 17:32:13 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	*find_path(char **s_cmd, char **envp)
{
	return (find_command_path(s_cmd[0], envp));
}

void	execute_cmd_with_path(char *path, char **s_cmd, char **envp)
{
	if (execve(path, s_cmd, envp) == -1)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putendl_fd(s_cmd[0], 2);
		free(s_cmd);
		exit(127);
	}
}

char	**split_command(char *cmd, char **envp)
{
	char	**s_cmd;
	char	*path;

	s_cmd = split_cmd_into_parts(cmd);
	path = find_path(s_cmd, envp);
	execute_cmd_with_path(path, s_cmd, envp);
	return (s_cmd);
}
