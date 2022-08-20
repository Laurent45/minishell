/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 16:46:02 by lfrederi          #+#    #+#             */
/*   Updated: 2022/07/23 16:56:54 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "error.h"
#include <stddef.h>

int	ft_check_tokens(t_list **tokens)
{
	t_list	*token;

	token = *tokens;
	if (((t_token *) token->content)->code == PIPE)
	{
		ft_puterror(0, "minishell: syntax error\n");
		return (ft_clear_tokens(tokens, 0));
	}
	while (token)
	{
		if (((t_token *) token->content)->code != WORD)
		{
			if (token->next == NULL || \
				((t_token *) token->next->content)->code != WORD)
			{
				ft_puterror(0, "minishell: syntax error\n");
				return (ft_clear_tokens(tokens, 0));
			}
		}
		token = token->next;
	}
	return (1);
}