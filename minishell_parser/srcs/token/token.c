/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 15:39:47 by lfrederi          #+#    #+#             */
/*   Updated: 2022/06/14 17:12:11 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "struct.h"
#include "error.h"
#include <stdlib.h>

static int	ft_char_type(char c)
{
	if (c == '|')
		return (PIPE);
	if (c == '<')
		return (LESS);
	if (c == '>')
		return (GREAT);
	if (c == '\'')
		return (S_QUOTE);
	if (c == '"')
		return (D_QUOTE);
	if (c == ' ' || c == '\t')
		return (ESCAPE_TAB);
	return (0);
}

static int	ft_token_word(t_list **tokens, char *line, int len, int quote)
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
	return (ft_new_token(tokens, WORD, dup, quote));
}

static int	ft_token_meta(t_list **tokens, int code)
{
	t_list	*last;

	if (code == ESCAPE_TAB || code == S_QUOTE || code == D_QUOTE)
		return (1);
	last = ft_lstlast(*tokens);
	if (last)
	{
		if (((t_token *) last->content)->code == GREAT && code == GREAT)
		{
			((t_token *) last->content)->code = GREATGREAT;
			return (1);
		}
		if (((t_token *) last->content)->code == LESS && code == LESS)
		{
			((t_token *) last->content)->code = LESSLESS;
			return (1);
		}
	}
	return (ft_new_token(tokens, code, NULL, 0));
}

int	ft_token_quote(t_list **tokens, char *line, int quote, int *ind)
{
	int	i;

	i = 0;
	while (line[i] && ft_char_type(line[i]) != quote)
		i++;
	if (!line[i])
		return (ft_puterror(0, "minishell: syntax error quote unclosed\n"));
	*ind += (i + 1);
	return (ft_token_word(tokens, line, i, quote));
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
		code = ft_char_type(line[i]);
		if (code != 0)
		{
			if (r < i && ft_token_word(tokens, line + r, i - r, 0) == 0)
				return (ft_clear_tokens(tokens, 0));
			if ((code == S_QUOTE || code == D_QUOTE)
				&& ft_token_quote(tokens, line + i + 1, code, &i) == 0)
				return (ft_clear_tokens(tokens, 0));
			if (ft_token_meta(tokens, code) == 0)
				return (ft_clear_tokens(tokens, 0));
			r = i + 1;
		}
		i++;
	}
	if (r < i && ft_token_word(tokens, line + r, i - r, 0) == 0)
		return (ft_clear_tokens(tokens, 0));
	return (1);
}
