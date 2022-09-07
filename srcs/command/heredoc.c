/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 19:10:00 by lfrederi          #+#    #+#             */
/*   Updated: 2022/09/07 23:20:17 by lfrederi         ###   ########.fr       */
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

static int	issigint(void)
{
	struct stat	statbuf;

	if (fstat(0, &statbuf) != 0)
		return (FAILED);
	return (SUCCESS);
}

static char	*heredoc_read(void)
{
	char	*line;

	signal(SIGINT, &handler_heredoc);
	line = readline("> ");
	signal(SIGINT, SIG_IGN);
	return (line);
}

static int	get_line(t_list **heredoc, char *end, int quote, t_list *my_envp)
{
	char	*line;
	char	*str_expand;
	t_list	*node_str;

	line = heredoc_read();
	while (line)
	{
		if (ft_strcmp(line, end) == 0)
			return (free(line), SUCCESS);
		if (quote == 0)
		{
			str_expand = expand(my_envp, line, 1, 0);
			free(line);
			if (str_expand == NULL)
				return (puterror(FAILED, "expand in heredoc failed\n"));
			line = str_expand;
		}
		if (new_node(&node_str, line) == FAILED)
			return (free(line), puterror(FAILED, "node in heredoc"));
		ft_lstadd_back(heredoc, node_str);
		line = heredoc_read();
	}
	printf("\n");
	return (issigint());
}

int	heredoc(t_redir *redir, char *tok_word, t_list *my_envp)
{
	int		quote;
	char	*endword;
	int		tmp_stdin;
	int		ret;

	quote = 0;
	redir->code = HEREDOC;
	if (ft_strchr(tok_word, '\'') || ft_strchr(tok_word, '\"'))
		quote = 1;
	endword = trim_quote(tok_word);
	if (endword == NULL)
		return (puterror(FAILED, "trim in heredoc failed\n"));
	tmp_stdin = dup(0);
	ret = get_line(&(redir->heredoc), endword, quote, my_envp);
	dup2(tmp_stdin, 0);
	close(tmp_stdin);
	return (free(endword), ret);
}
