/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_execute.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 11:51:51 by Jskehan           #+#    #+#             */
/*   Updated: 2024/04/11 11:08:02 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	parse_and_execute_command(char *cmd, char **envp)
{
	char	**s_cmd;
	char	*path;

	if (ft_strcmp(cmd, "") == 0)
		return (0);
	s_cmd = split_cmd_into_parts(cmd);
	path = find_command_path(s_cmd[0], envp);
	if (execve(path, s_cmd, envp) == -1)
	{
		
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(s_cmd[0], 2);
		ft_putendl_fd(": command not found", 2);
		free_string_array(s_cmd);
		return (127);
	}
	return (0);
}
