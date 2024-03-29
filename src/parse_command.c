/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 11:51:51 by Jskehan           #+#    #+#             */
/*   Updated: 2024/03/29 12:28:32 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"
//need to take strings and split them into arrays of strings
//examples below
	//"awk \"'{count++} END {print count}'\""
	//"awk '\"{count++} END {print count}\"'"
	//"awk \"{count++} END {print count}\""
	//"awk '{count++} END {print count}'"
char **split_command(char *cmd, char **envp)
{
	char **s_cmd;
	char *path;

	s_cmd = ft_split(cmd, ' ');
	path = find_command_path(s_cmd[0], envp);
	if (execve(path, s_cmd, envp) == -1)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putendl_fd(s_cmd[0], 2);
		free_string_array(s_cmd);
		exit(EXIT_FAILURE);
	}
	return (s_cmd);
}
