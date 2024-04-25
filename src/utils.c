/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 13:20:58 by Jskehan           #+#    #+#             */
/*   Updated: 2024/04/25 10:56:47 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	ft_check_args(int argc, char **argv)
{
	int	here_doc;

	here_doc = (ft_strcmp(argv[1], "here_doc") == 0);
	if ((argc < 5) || (here_doc && argc < 6))
	{
		ft_putstr_fd("pipex: too few arguments\n", 2);
		exit(EXIT_FAILURE);
	}
	if (!here_doc 
		&& ((access(argv[1], F_OK) == -1) || (access(argv[1], R_OK) == -1)))
		ft_error();
}

int	open_file(char *file, int in_or_out)
{
	int	ret;

	ret = 0;
	if (in_or_out == 0)
	{
		ret = open(file, O_RDONLY, 0777);
		if (ret == -1)
			ret = open("/dev/null", O_RDONLY, 0777);
	}
	if (in_or_out == 1)
		ret = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (in_or_out == 2)
		ret = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	return (ret);
}

void	ft_free_tab(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	*my_getenv(char *name, char **env)
{
	int		i;
	int		j;
	char	*sub;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		sub = ft_substr(env[i], 0, j);
		if (ft_strcmp(sub, name) == 0)
		{
			free(sub);
			return (env[i] + j + 1);
		}
		free(sub);
		i++;
	}
	return (NULL);
}

char	*get_path(char *cmd, char **env)
{
	int		i;
	char	*exec;
	char	**allpath;
	char	*path_part;
	char	**s_cmd;

	i = -1;
	allpath = ft_split(my_getenv("PATH", env), ':');
	s_cmd = ft_split(cmd, ' ');
	while (allpath[++i])
	{
		path_part = ft_strjoin(allpath[i], "/");
		exec = ft_strjoin(path_part, s_cmd[0]);
		free(path_part);
		if (access(exec, F_OK | X_OK) == 0)
		{
			ft_free_tab(s_cmd);
			return (exec);
		}
		free(exec);
	}
	ft_free_tab(allpath);
	ft_free_tab(s_cmd);
	return (cmd);
}
