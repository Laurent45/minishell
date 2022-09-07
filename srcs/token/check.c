/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 16:46:02 by lfrederi          #+#    #+#             */
/*   Updated: 2022/09/07 12:25:20 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "error.h"

#include <stddef.h>

static int	is_valid_pair(int code, int next_code)
{
	if (next_code == WORD ||\
		(code == PIPE && (next_code != -1 && next_code != PIPE)))
		return (1);
	return (0);
}

int	check_tokens(t_list **tokens)
{
	t_list	*token;
	int		code;
	int		next_code;

	token = *tokens;
	code = ((t_token *) token->content)->code;
	if (code == PIPE)
		return (clear_tokens(tokens, puterror(FAILED, SYNTAX_ERROR)));
	while (token)
	{
		code = ((t_token *) token->content)->code;
		if (token->next == NULL)
			next_code = -1;
		else
			next_code = ((t_token *) token->next->content)->code;
		if (code != WORD && is_valid_pair(code, next_code) == 0)
			return (clear_tokens(tokens, puterror(FAILED, SYNTAX_ERROR)));
		token = token->next;
	}
	return (SUCCESS);
}
