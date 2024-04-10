/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 16:45:52 by Jskehan           #+#    #+#             */
/*   Updated: 2024/04/10 20:19:52 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

// static void	add_part_to_list(t_list **parts, char *part)
// {
// 	ft_lstadd_back(parts, ft_lstnew(part));
// }

// static void	update_part(char **part, char c)
// {
// 	char	*temp;

// 	temp = *part;
// 	*part = ft_strjoin(*part, (char []){c, '\0'});
// 	free(temp);
// }

void	update_quotes(int in_double_quotes, int in_single_quotes, char c)
{
	if (c == '\'' && !in_double_quotes)
		in_single_quotes = !in_single_quotes;
	else if (c == '\"' && !in_single_quotes)
		in_double_quotes = !in_double_quotes;
}

void	initilise_parser(t_parser *parser)
{
	parser->parts = NULL;
	parser->part = ft_strnew(0);
	parser->in_single_quotes = 0;
	parser->in_double_quotes = 0;
}

// char	**split_cmd_into_parts(char *cmd)
// {
// 	t_parser	parser;
// 	int			i;

// 	i = -1;
// 	initilise_parser(&parser);
// 	while (cmd[++i] != '\0')
// 	{
// 		if (cmd[i] == '\'' && !parser.in_double_quotes)
// 			parser.in_single_quotes = !parser.in_single_quotes;
// 		else if (cmd[i] == '\"' && !parser.in_single_quotes)
// 			parser.in_double_quotes = !parser.in_double_quotes;
// 		else if (cmd[i] == ' ' && !parser.in_single_quotes
// 			&& !parser.in_double_quotes)
// 		{
// 			add_part_to_list(&parser.parts, parser.part);
// 			parser.part = ft_strnew(0);
// 		}
// 		else
// 		{
// 			update_part(&parser.part, cmd[i]);
// 			ft_lstclear(&parser.parts, free);
// 			free(parser.part);
// 		}
// 	}
// 	if (ft_strlen(parser.part) > 0)
// 		add_part_to_list(&parser.parts, parser.part);
// 	return (ft_lsttoarr(parser.parts));
// }

char	**split_cmd_into_parts(char *cmd)
{
	char	**parts;
	char	*part;
	int		i;
	int		num_parts;
	char	*temp;

	i = -1;
	num_parts = 0;
	part = ft_strnew(0);
	parts = malloc(sizeof(char *) * (num_parts + 1));
	while (cmd[++i] != '\0')
	{
		if (cmd[i] == ' ')
		{
			parts[num_parts++] = part;
			part = ft_strnew(0);
			parts = realloc(parts, sizeof(char *) * (num_parts + 1));
		}
		else
		{
			temp = part;
			part = ft_strjoin(part, (char[]){cmd[i], '\0'});
			free(temp);
		}
	}
	if (ft_strlen(part) > 0)
		parts[num_parts++] = part;
	parts[num_parts] = NULL; // Null-terminate the array
	return (parts);
}
