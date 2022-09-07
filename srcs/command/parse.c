/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 11:05:04 by lfrederi          #+#    #+#             */
/*   Updated: 2022/09/07 22:14:13 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "token.h"
#include "error.h"
#include "ft_string.h"
#include "ft_ctype.h"

#include <stdlib.h>

static int	tokword(t_command *cmd, char *token_str)
{
	char	*dup_token_str;
	t_list	*node_str;

	node_str = NULL;
	dup_token_str = ft_strdup(token_str);
	if (!dup_token_str)
		return (puterror(FAILED, "char * in word"));
	if (new_node(&node_str, (void *) dup_token_str) == FAILED)
	{
		free(dup_token_str);
		return (puterror(FAILED, "node in word"));
	}
	if (ft_strchr(dup_token_str, '=') && cmd->cmd_args == NULL \
			&& (dup_token_str[0] == '_' || ft_isalpha(dup_token_str[0]) != 0))
		ft_lstadd_back(&cmd->env_var, node_str);
	else
		ft_lstadd_back(&cmd->cmd_args, node_str);
	return (SUCCESS);
}

static int	tokredir(t_command *cmd, int code, char *token_str, t_list *my_envp)
{
	char	*dup_token_str;
	t_redir	*redir;
	t_list	*node_redir;

	redir = NULL;
	node_redir = NULL;
	dup_token_str = ft_strdup(token_str);
	if (!dup_token_str)
		return (puterror(FAILED, "char * in t_redir"));
	if (set_redir(&redir, code, dup_token_str, my_envp) == FAILED)
		return (del_redir(redir), FAILED);
	if (new_node(&node_redir, (void *) redir) == FAILED)
	{
		ft_lstclear(&cmd->redir, &del_redir);
		return (puterror(FAILED, "node in redir"));
	}
	ft_lstadd_back(&cmd->redir, node_redir);
	return (SUCCESS);
}

static int	set_command(t_list **tokens, t_command *cmd, t_list *my_envp)
{
	t_list	*node_token;
	int		code;

	node_token = *tokens;
	code = ((t_token *) node_token->content)->code;
	if (code == WORD)
		return (tokword(cmd, (((t_token *) node_token->content)->str)));
	*tokens = (*tokens)->next;
	node_token = *tokens;
	return (tokredir(cmd, code, ((t_token *) node_token->content)->str, my_envp));
}

int	parse_to_command(t_list **cmds, t_list *tokens, int i, t_list *my_envp)
{
	t_command	*cmd;
	t_list		*node_cmd;

	while (tokens)
	{
		if (new_command(&cmd, i) == FAILED)
			return (clear_cmds(cmds, FAILED));
		i++;
		if (new_node(&node_cmd, (void *) cmd) == FAILED)
		{
			puterror(FAILED, "error new node in create_command");
			return (del_cmd((void *) cmd), clear_cmds(cmds, FAILED));
		}
		ft_lstadd_back(cmds, node_cmd);
		while (tokens && ((t_token *) tokens->content)->code != PIPE)
		{
			if (set_command(&tokens, cmd, my_envp) == FAILED)
				return (clear_cmds(cmds, FAILED));
			tokens = tokens->next;
		}
		if (tokens)
			tokens = tokens->next;
	}
	return (SUCCESS);
}
