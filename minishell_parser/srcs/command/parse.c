/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 11:05:04 by lfrederi          #+#    #+#             */
/*   Updated: 2022/07/13 10:37:03 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "token.h"
#include "error.h"
#include "ft_string.h"
#include <stdlib.h>

static int	ft_word(t_command *command, char *word)
{
	char	*dup;
	t_list	*node_str;

	dup = ft_strdup(word);
	if (!dup)
		return (ft_allocated_err(CMD_FAILED, "char * in ft_word"));
	if (ft_new_node(&node_str, (void *) dup) == CMD_FAILED)
	{
		free(dup);
		return (ft_allocated_err(CMD_FAILED, "node in ft_word"));
	}
	if (ft_strchr(dup, '=') && command->cmd_args == NULL)
		ft_lstadd_back(&command->env_var, node_str);
	else
		ft_lstadd_back(&command->cmd_args, node_str);
	return (CMD_SUCCESS);
}

static int	ft_redir(t_command *command, int code, char *word)
{
	char	*dup;
	t_redir	*redir;
	t_list	*node_redir;

	redir = NULL;
	node_redir = NULL;
	dup = ft_strdup(word);
	if (!dup)
		return (ft_allocated_err(CMD_FAILED, "char * in t_redir"));
	if (ft_new_redir(&redir, code, dup) == CMD_FAILED)
	{
		if (redir)
			free(redir);
		free(dup);
		return (ft_allocated_err(CMD_FAILED, "redir in ft_redir"));
	}
	if (ft_new_node(&node_redir, (void *) redir) == CMD_FAILED)
	{
		ft_lstclear(&command->redir, &ft_del_redir);
		return (ft_allocated_err(CMD_FAILED, "node in ft_redir"));
	}
	ft_lstadd_back(&command->redir, node_redir);
	return (CMD_SUCCESS);
}

static int	ft_set_command(t_list **tokens, t_command *command)
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

int	ft_parse_to_command(t_list **commands, t_list *tokens, int i)
{
	t_command	*command;
	t_list		*node_command;

	while (tokens)
	{
		if (ft_new_command(&command, i) == CMD_FAILED)
			return (ft_clear_commands(commands, CMD_FAILED));
		i++;
		if (ft_new_node(&node_command, (void *) command) == CMD_FAILED)
		{
			ft_del_command((void *) command);
			ft_allocated_err(CMD_FAILED, "node in ft_create_command");
			return (ft_clear_commands(commands, CMD_FAILED));
		}
		ft_lstadd_back(commands, node_command);
		while (tokens && ((t_token *) tokens->content)->code != PIPE)
		{
			if (ft_set_command(&tokens, command) == CMD_FAILED)
				return (ft_clear_commands(commands, CMD_FAILED));
			tokens = tokens->next;
		}
		if (tokens)
			tokens = tokens->next;
	}
	return (CMD_SUCCESS);
}
