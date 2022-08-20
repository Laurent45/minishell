/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 11:05:04 by lfrederi          #+#    #+#             */
/*   Updated: 2022/07/31 16:11:57 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "token.h"
#include "error.h"
#include "ft_string.h"
#include "ft_ctype.h"

#include <stdlib.h>

static int	ft_tokword(t_command *t_cmd, char *tok_word)
{
	char	*dup_tok_word;
	t_list	*node_str;

	dup_tok_word = ft_strdup(tok_word);
	if (!dup_tok_word)
		return (ft_puterror(CMD_FAILED, "char * in ft_word"));
	if (ft_new_node(&node_str, (void *) dup_tok_word) == CMD_FAILED)
	{
		free(dup_tok_word);
		return (ft_puterror(CMD_FAILED, "node in ft_word"));
	}
	if (ft_strchr(dup_tok_word, '=') && t_cmd->cmd_args == NULL \
			&& (dup_tok_word[0] == '_' || ft_isalpha(dup_tok_word[0]) != 0))
		ft_lstadd_back(&t_cmd->env_var, node_str);
	else
		ft_lstadd_back(&t_cmd->cmd_args, node_str);
	return (CMD_SUCCESS);
}

static int	ft_tokredir(t_command *command, int code, char *tok_word)
{
	char	*dup_tok_word;
	t_redir	*redir;
	t_list	*node_redir;

	redir = NULL;
	node_redir = NULL;
	dup_tok_word = ft_strdup(tok_word);
	if (!dup_tok_word)
		return (ft_puterror(CMD_FAILED, "char * in t_redir"));
	if (ft_redir(&redir, code, dup_tok_word) == 0)
		return (ft_del_redir(redir), CMD_FAILED);
	if (ft_new_node(&node_redir, (void *) redir) == CMD_FAILED)
	{
		ft_lstclear(&command->redir, &ft_del_redir);
		return (ft_puterror(CMD_FAILED, "node in ft_redir"));
	}
	ft_lstadd_back(&command->redir, node_redir);
	return (CMD_SUCCESS);
}

static int	ft_set_command(t_list **tokens, t_command *t_cmd)
{
	t_list	*node_token;
	int		code;

	node_token = *tokens;
	code = ((t_token *) node_token->content)->code;
	if (code == WORD)
		return (ft_tokword(t_cmd, (((t_token *) node_token->content)->str)));
	*tokens = (*tokens)->next;
	node_token = *tokens;
	return (ft_tokredir(t_cmd, code, ((t_token *) node_token->content)->str));
}

int	ft_parse_to_command(t_list **cmds, t_list *tokens, int i)
{
	t_command	*t_cmd;
	t_list		*node_cmd;

	while (tokens)
	{
		if (ft_new_command(&t_cmd, i) == CMD_FAILED)
			return (ft_clear_cmds(cmds, CMD_FAILED));
		i++;
		if (ft_new_node(&node_cmd, (void *) t_cmd) == CMD_FAILED)
		{
			ft_puterror(CMD_FAILED, "error new node in ft_create_command");
			return (ft_del_cmd((void *) t_cmd), ft_clear_cmds(cmds, 0));
		}
		ft_lstadd_back(cmds, node_cmd);
		while (tokens && ((t_token *) tokens->content)->code != PIPE)
		{
			if (ft_set_command(&tokens, t_cmd) == CMD_FAILED)
				return (ft_clear_cmds(cmds, CMD_FAILED));
			tokens = tokens->next;
		}
		if (tokens)
			tokens = tokens->next;
	}
	return (CMD_SUCCESS);
}
