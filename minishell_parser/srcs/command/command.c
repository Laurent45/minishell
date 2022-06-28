/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 11:05:04 by lfrederi          #+#    #+#             */
/*   Updated: 2022/06/26 17:27:58 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "token.h"
#include "error.h"
#include "ft_string.h"
#include <stdlib.h>

static int	ft_word(t_command *command, char *args)
{
	char	*dup;
	int		has_equal;
	t_list	*node;

	has_equal = 0;
	dup = ft_strdup(args);
	if (!dup)
		return (ft_allocated_err(0, "char * in ft_add_args"));
	if (ft_strchr(dup, '='))
		has_equal = 1;
	if (has_equal == 0 && command->cmd == NULL)
	{
		command->cmd = dup;
		return (1);
	}
	if (ft_new_node(&node, (void *) dup) == 0)
	{
		free(dup);
		return (ft_allocated_err(0, "node in ft_add_args"));
	}
	if (has_equal && command->cmd == NULL)
		ft_lstadd_back(&command->env_var, node);
	else
		ft_lstadd_back(&command->args, node);
	return (1);
}

int	ft_redir(t_command *command, int code, char *word)
{
	char	*dup;
	t_redir	*redir;
	t_list	*node_redir;

	dup = ft_strdup(word);
	if (!dup)
		return (0);
	if (ft_new_redir(&redir, code, dup) == 0)
	{
		free(dup);
		return (0);
	}
	if (!ft_new_node(&node_redir, (void *) redir))
		return (0);
	ft_lstadd_back(&command->redir, node_redir);
	return (1);
}

int	ft_set_command(t_list **tokens, t_command *command)
{
	t_list	*node_token;
	int		code;

	node_token = *tokens;
	code = ((t_token *) node_token->content)->code;
	if (code == WORD)
		return (ft_word(command, (((t_token *) node_token->content)->word)));
	*tokens = (*tokens)->next;
	node_token = *tokens;
	return (ft_redir(command, code, ((t_token *) node_token->content)->word));
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
