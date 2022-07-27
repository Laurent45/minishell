/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 10:37:30 by lfrederi          #+#    #+#             */
/*   Updated: 2022/07/25 10:37:00 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "ft_string.h"
#include "ft_stdio.h"
#include "expansion.h"
#include "token.h"
#include "error.h"
#include "signal_handler.h"

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

static char	*ft_line(void)
{
	char	*line;

	write(1, "> ", 2);
	signal(SIGINT, &handler_heredoc);
	line = get_next_line(0);
	signal(SIGINT, SIG_IGN);
	return (line);
}

int	ft_new_node(t_list **node, void *content)
{
	*node = ft_lstnew(content);
	if (!(*node))
		return (0);
	return (1);
}

static int	ft_heredoc(t_list **heredoc, char *end, int quote)
{
	char	*line;
	char	*expand;
	t_list	*node_str;

	line = ft_line();
	while (line)
	{
		if (ft_strncmp(line, end, ft_strlen(end)) == 0)
			return (free(line), 1);
		if (quote == 0)
		{
			expand = ft_expand(line, 1, 0);
			free(line);
			if (expand == NULL)
				return (ft_puterror(0, "expand in heredoc failed\n"));
			line = expand;
		}
		if (ft_new_node(&node_str, line) == 0)
			return (free(line), ft_allocated_err(0, "node in ft_heredoc"));
		ft_lstadd_back(heredoc, node_str);
		line = ft_line();
	}
	return (0);
}

static void	ft_set_code_file(t_redir *redir, int code, char *file)
{
	if (code == LESS)
		redir->code = INFILE;
	else if (code == GREAT)
		redir->code = OUTFILE;
	else if (code == GREATGREAT)
		redir->code = APPENDFILE;
	redir->file = file;
}

int	ft_new_redir(t_redir **redir, int code, char *str)
{
	int		ret;
	char	*trim;
	int		quote;

	*redir = (t_redir *) malloc(sizeof(t_redir));
	if (!(*redir))
		return (0);
	(*redir)->file = NULL;
	(*redir)->heredoc = NULL;
	if (code == LESSLESS)
	{
		quote = 0;
		(*redir)->code = HEREDOC;
		if (ft_strchr(str, '\'') || ft_strchr(str, '\"'))
			quote = 1;
		trim = ft_trim_quote(str);
		if (trim == NULL)
			return (ft_puterror(0, "trim in heredoc failed\n"));
		ret = ft_heredoc(&(*redir)->heredoc, trim, quote);
		return (free(trim), ret);
	}
	else
		ft_set_code_file(*redir, code, str);
	return (1);
}
