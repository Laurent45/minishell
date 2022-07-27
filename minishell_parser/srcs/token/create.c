/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 12:27:14 by lfrederi          #+#    #+#             */
/*   Updated: 2022/07/13 09:44:47 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "error.h"
#include <stdlib.h>

int	ft_new_token(t_list **tokens, int code, char *word)
{
	t_token		*token;
	t_list		*node;

	token = (t_token *) malloc(sizeof(t_token));
	if (!token)
		return (ft_allocated_err(TOK_FAILED, "t_token * in ft_new_token"));
	token->code = code;
	token->word = word;
	node = ft_lstnew((void *) token);
	if (!node)
	{
		ft_del_token((void *) token);
		return (ft_allocated_err(TOK_FAILED, "node in ft_new_token"));
	}
	ft_lstadd_back(tokens, node);
	return (TOK_SUCCESS);
}
