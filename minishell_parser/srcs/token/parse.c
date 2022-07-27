/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 15:39:47 by lfrederi          #+#    #+#             */
/*   Updated: 2022/07/13 09:46:58 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "struct.h"
#include "error.h"
#include <stdlib.h>

static int	ft_is_metachar(char c)
{
	if (c == '|')
		return (PIPE);
	if (c == '<')
		return (LESS);
	if (c == '>')
		return (GREAT);
	if (c == ' ' || c == '\t')
		return (ESCAPE_TAB);
	return (NOT_META);
}

static int	ft_token_word(t_list **tokens, char *line, int len)
{
	char	*dup;
	int		i;

	dup = (char *) malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (ft_allocated_err(0, "char * in ft_token_word"));
	i = 0;
	while (i < len)
	{
		dup[i] = line[i];
		i++;
	}
	dup[i] = '\0';
	return (ft_new_token(tokens, WORD, dup));
}

static int	ft_token_meta(t_list **tokens, int code)
{
	t_list	*last;

	if (code == ESCAPE_TAB)
		return (TOK_SUCCESS);
	last = ft_lstlast(*tokens);
	if (last)
	{
		if (((t_token *) last->content)->code == GREAT && code == GREAT)
		{
			((t_token *) last->content)->code = GREATGREAT;
			return (TOK_SUCCESS);
		}
		if (((t_token *) last->content)->code == LESS && code == LESS)
		{
			((t_token *) last->content)->code = LESSLESS;
			return (TOK_SUCCESS);
		}
	}
	return (ft_new_token(tokens, code, NULL));
}

int	ft_create_tokens(t_list **tokens, char *line)
{
	int	i;
	int	r;
	int	code;

	i = 0;
	r = 0;
	while (line[i])
	{
		code = ft_is_metachar(line[i]);
		if (code != NOT_META)
		{
			if (r < i && ft_token_word(tokens, line + r, i - r) == TOK_FAILED)
				return (ft_clear_tokens(tokens, TOK_FAILED));
			if (ft_token_meta(tokens, code) == TOK_FAILED)
				return (ft_clear_tokens(tokens, TOK_FAILED));
			r = i + 1;
		}
		i++;
	}
	if (r < i && ft_token_word(tokens, line + r, i - r) == TOK_FAILED)
		return (ft_clear_tokens(tokens, TOK_FAILED));
	return (TOK_SUCCESS);
}
