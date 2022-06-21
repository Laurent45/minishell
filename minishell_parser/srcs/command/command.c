/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 11:05:04 by lfrederi          #+#    #+#             */
/*   Updated: 2022/06/14 16:45:46 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "token.h"
#include "error.h"
#include "ft_string.h"
#include <stdlib.h>

static int	ft_add_args(t_command *command, char *args)
{
	char	*dup;
	t_list	*node;

	dup = ft_strdup(args);
	if (!dup)
		return (ft_allocated_err(0, "char * in ft_add_args"));
	if (ft_new_node(&node, (void *) dup) == 0)
	{
		free(dup);
		return (ft_allocated_err(0, "node in ft_add_args"));
	}
	ft_lstadd_back(&command->args, node);
	return (1);
}

int	ft_set_command(t_list **tokens, t_command *command)
{
	t_list	*n;
	int		code;

	n = *tokens;
	code = ((t_token *) n->content)->code;
	if (code == WORD)
		return (ft_add_args(command, (((t_token *) n->content)->word)));
	else if (code == LESS || code == LESSLESS)
	{
		*tokens = (*tokens)->next;
		n = *tokens;
		return (ft_input(command, code, ((t_token *) n->content)->word));
	}
	else if (code == GREAT || code == GREATGREAT)
	{
		*tokens = (*tokens)->next;
		n = *tokens;
		return (ft_output(command, code, ((t_token *) n->content)->word));
	}
	else
		return (0);
}

int	ft_create_command(t_list **commands, t_list *tokens)
{
	t_command	*command;
	t_list		*node;

	while (tokens)
	{
		if (ft_new_command(&command) == 0)
			return (0);
		if (ft_new_node(&node, (void *) command) == 0)
		{
			ft_del_command((void *) command);
			ft_allocated_err(0, "node in ft_create_command");
			return (ft_clear_commands(commands, 0));
		}
		ft_lstadd_back(commands, node);
		while (tokens && ((t_token *) tokens->content)->code != PIPE)
		{
			if (ft_set_command(&tokens, command) == 0)
				return (ft_clear_commands(commands, 0));
			tokens = tokens->next;
		}
		if (tokens)
			tokens = tokens->next;
	}
	return (1);
}
