/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 11:05:04 by lfrederi          #+#    #+#             */
/*   Updated: 2022/09/12 22:08:16 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "token.h"
#include "error.h"
#include "ft_string.h"
#include "ft_ctype.h"

#include <stdlib.h>

static	int	is_assignement(char *str)
{
	int	i;

	i = 0;
	if (str[i] != '_' && ft_isalpha(str[i]) == 0)
		return (FAILED);
	i++;
	while (str[i] != '=')
	{
		if (str[i] != '_' && ft_isalnum(str[i]) == 0)
		{
			if (str[i] == '+' && str[i + 1] == '=')
				return (SUCCESS);
			return (FAILED);
		}
		i++;
	}
	return (SUCCESS);
}

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
	if (cmd->cmd_args == NULL && ft_strchr(dup_token_str, '=') \
			&& is_assignement(dup_token_str) == SUCCESS)
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
	if (set_heredoc_file(redir, cmd->num) == FAILED)
		return (del_redir(redir), FAILED);
	if (new_node(&node_redir, (void *) redir) == FAILED)
	{
		ft_lstclear(&cmd->redir, &del_redir);
		return (puterror(FAILED, "node in redir"));
	}
	ft_lstadd_back(&cmd->redir, node_redir);
	return (SUCCESS);
}

static int	set_command(t_list **tokens, t_command *cmd, t_list *env)
{
	t_list	*node_token;
	int		code;

	node_token = *tokens;
	code = ((t_token *) node_token->content)->code;
	if (code == WORD)
		return (tokword(cmd, (((t_token *) node_token->content)->str)));
	*tokens = (*tokens)->next;
	node_token = *tokens;
	return (tokredir(cmd, code, ((t_token *) node_token->content)->str, env));
}

int	parse_to_command(t_list **cmds, t_list *tokens, t_list *my_envp)
{
	int			num_cmd;
	t_command	*cmd;
	t_list		*node_cmd;

	num_cmd = 0;
	while (tokens)
	{
		if (new_command(&cmd, num_cmd) == FAILED)
			return (clear_cmds(cmds, FAILED));
		num_cmd++;
		if (new_node(&node_cmd, (void *) cmd) == FAILED)
			return (del_cmd((void *) cmd), clear_cmds(cmds, FAILED));
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
