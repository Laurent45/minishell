/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 11:05:04 by lfrederi          #+#    #+#             */
/*   Updated: 2022/06/09 11:24:45 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "token.h"
#include "ft_string.h"
#include <stdlib.h>
#include "struct.h"

/*
 * REDIRECTION OUTPUT
 */

int	ft_set_command(t_command *command, t_list *token, int code)
{
	char	*dup;
	t_list	*node;
	t_list	**tmp;

	dup = ft_strdup(((t_token *) token->content)->word);
	if (!dup)
		return (0);
	node = ft_lstnew((void *) dup);
	if (!node)
	{
		free(dup);
		return (0);
	}
	tmp = &command->args;
	if (code == GREAT || code == GREATGREAT)
		tmp = &command->output;
	if (code == GREATGREAT)
		command->append = 1;
	ft_lstadd_back(tmp, node);
	return (1);
}

int	ft_create_command(t_list **commands, t_list *tokens)
{
	t_command	*command;
	t_list		*node;
	int			code;

	while (tokens)
	{
		command = (t_command *) malloc(sizeof(t_command));
		if (!command)
			return (0);
		command->args = NULL;
		command->output = NULL;
		command->append = 0;
		code = ((t_token *) tokens->content)->code;
		while (tokens && code != PIPE)
		{
			if (code == GREAT || code == GREATGREAT || code == LESS || code == LESSLESS)
			{
				ft_set_command(command, tokens->next, code);
				tokens = tokens->next;
			}
			else
				ft_set_command(command, tokens, code);
			tokens = tokens->next;
			if (tokens)
				code = ((t_token *) tokens->content)->code;
		}
		node = ft_lstnew((void *) command);
		if (!node)
			return (0);
		ft_lstadd_back(commands, node);
		if (tokens)
			tokens = tokens->next;
	}
	return (1);
}
