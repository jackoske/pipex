/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 16:45:52 by Jskehan           #+#    #+#             */
/*   Updated: 2024/04/25 16:16:26 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	add_part_to_list(t_list **parts, char *part)
{
	ft_lstadd_back(parts, ft_lstnew(part));
}

void	update_part(char **part, char c)
{
	char	*temp;

	temp = *part;
	*part = ft_strjoin(*part, (char []){c, '\0'});
	free(temp);
}

void	initilise_parser(t_parser *parser)
{
	parser->parts = NULL;
	parser->part = ft_strnew(0);
	parser->in_single_quotes = 0;
	parser->in_double_quotes = 0;
}

void	parse_cmd(t_parser *parser, char *cmd)
{
	int	i;

	i = -1;
	while (cmd[++i] != '\0')
	{
		if (cmd[i] == '\'' && !parser->in_double_quotes)
			parser->in_single_quotes = !parser->in_single_quotes;
		else if (cmd[i] == '\"' && !parser->in_single_quotes)
			parser->in_double_quotes = !parser->in_double_quotes;
		else if (cmd[i] == ' ' && !parser->in_single_quotes
			&& !parser->in_double_quotes)
		{
			add_part_to_list(&parser->parts, parser->part);
			parser->part = ft_strnew(0);
		}
		else
			update_part(&parser->part, cmd[i]);
	}
}

char	**split_cmd_into_parts(char *cmd)
{
	t_parser	parser;
	char		**parts;

	initilise_parser(&parser);
	parse_cmd(&parser, cmd);
	if (ft_strlen(parser.part) > 0)
		add_part_to_list(&parser.parts, parser.part);
	parts = ft_lsttoarr(parser.parts);
	ft_lstclear(&parser.parts, free);
	return (parts);
}
