/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 19:10:00 by lfrederi          #+#    #+#             */
/*   Updated: 2022/08/18 18:57:18 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "expansion.h"
#include "error.h"
#include "signal_handler.h"
#include "ft_string.h"

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <readline/readline.h>

static int	ft_issigint(void)
{
	struct stat	statbuf;

	if (fstat(0, &statbuf) != 0)
		return (0);
	return (1);
}

static char	*ft_read(void)
{
	char	*line;

	signal(SIGINT, &handler_heredoc);
	line = readline("> ");
	signal(SIGINT, SIG_IGN);
	return (line);
}

static int	ft_get_line(t_list **heredoc, char *end, int quote)
{
	char	*line;
	char	*expand;
	t_list	*node_str;

	line = ft_read();
	while (line)
	{
		if (ft_strcmp(line, end) == 0)
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
			return (free(line), ft_puterror(0, "node in ft_heredoc"));
		ft_lstadd_back(heredoc, node_str);
		line = ft_read();
	}
	printf("\n");
	return (ft_issigint());
}

int	ft_heredoc(t_redir *redir, char *tok_word)
{
	int		quote;
	char	*endword;
	int		tmp_stdin;
	int		ret;

	quote = 0;
	redir->code = HEREDOC;
	if (ft_strchr(tok_word, '\'') || ft_strchr(tok_word, '\"'))
		quote = 1;
	endword = ft_trim_quote(tok_word);
	if (endword == NULL)
		return (ft_puterror(0, "trim in heredoc failed\n"));
	tmp_stdin = dup(0);
	ret = ft_get_line(&(redir->heredoc), endword, quote);
	dup2(tmp_stdin, 0);
	close(tmp_stdin);
	return (free(endword), ret);
}
