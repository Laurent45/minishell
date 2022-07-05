/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 10:37:30 by lfrederi          #+#    #+#             */
/*   Updated: 2022/07/05 15:15:07 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "command.h"
#include "ft_string.h"
#include "ft_stdio.h"
#include "token.h"
#include "error.h"

int	ft_new_node(t_list **node, void *content)
{
	*node = ft_lstnew(content);
	if (!(*node))
		return (0);
	return (1);
}

static int	ft_heredoc(t_list **heredoc, char *end)
{
	char	*line;
	t_list	*node_str;

	write(1, "> ", 2);
	line = get_next_line(0);
	if (!line)
		return (ft_allocated_err(0, "get_next_line in ft_heredoc"));
	while (line)
	{
		if (ft_strncmp(line, end, ft_strlen(end)) == 0)
		{
			free(line);
			return (1);
		}
		if (ft_new_node(&node_str, line) == 0)
		{
			free(line);
			ft_lstclear(heredoc, &ft_del_str);
			return (ft_allocated_err(0, "node in ft_heredoc"));
		}
		ft_lstadd_back(heredoc, node_str);
		write(1, "> ", 2);
		line = get_next_line(0);
	}
	return (1);
}

int	ft_new_redir(t_redir **redir, int code, char *str)
{
	int	ret;

	*redir = (t_redir *) malloc(sizeof(t_redir));
	if (!(*redir))
		return (0);
	(*redir)->file = NULL;
	(*redir)->heredoc = NULL;
	if (code == LESSLESS)
	{
		(*redir)->code = HEREDOC;
		ret = ft_heredoc(&(*redir)->heredoc, str);
		free(str);
		return (ret);
	}
	if (code == LESS)
		(*redir)->code = INFILE;
	else if (code == GREAT)
		(*redir)->code = OUTFILE;
	else if (code == GREATGREAT)
		(*redir)->code = APPENDFILE;
	(*redir)->file = str;
	return (1);
}
