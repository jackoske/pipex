/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 16:45:52 by Jskehan           #+#    #+#             */
/*   Updated: 2024/04/10 20:46:00 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	handle_space(char **parts, char **part, int *num_parts)
{
	parts[(*num_parts)++] = *part;
	*part = ft_strnew(0);
}

void	handle_char(char **part, char c)
{
	char	*temp;

	temp = *part;
	*part = ft_strjoin(*part, (char []){c, '\0'});
	free(temp);
}

char	**split_cmd_into_parts(char *cmd)
{
	char	**parts;
	char	*part;
	int		i;
	int		num_parts;

	i = -1;
	num_parts = 0;
	part = ft_strnew(0);
	parts = malloc(sizeof(char *) * (count_words(cmd, ' ') + 1));
	while (cmd[++i] != '\0')
	{
		if (cmd[i] == ' ')
			handle_space(parts, &part, &num_parts);
		else
			handle_char(&part, cmd[i]);
	}
	if (ft_strlen(part) > 0)
		parts[num_parts++] = part;
	parts[num_parts] = NULL;
	return (parts);
}
