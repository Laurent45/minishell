/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 10:37:30 by lfrederi          #+#    #+#             */
/*   Updated: 2022/07/31 15:29:26 by lfrederi         ###   ########.fr       */
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
#include <stdio.h>

int	ft_new_node(t_list **node, void *content)
{
	*node = ft_lstnew(content);
	if (!(*node))
		return (0);
	return (1);
}

int	ft_redir(t_redir **redir, int tok_code, char *tok_word)
{
	if (ft_new_redir(redir) == 0)
		return (free(tok_word), 0);
	if (tok_code == LESSLESS)
		return (ft_heredoc(*redir, tok_word));
	if (tok_code == LESS)
		(*redir)->code = INFILE;
	else if (tok_code == GREAT)
		(*redir)->code = OUTFILE;
	else if (tok_code == GREATGREAT)
		(*redir)->code = APPENDFILE;
	(*redir)->file = tok_word;
	return (1);
}
