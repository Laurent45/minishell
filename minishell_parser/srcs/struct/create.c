/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 18:02:26 by lfrederi          #+#    #+#             */
/*   Updated: 2022/06/26 17:30:57 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "error.h"
#include "token.h"
#include <stdlib.h>

int	ft_new_env(t_env **env, char *var, int globale)
{
	*env = (t_env *) malloc(sizeof(t_env));
	if (!(*env))
	{
		free(var);
		return (ft_allocated_err(0, "t_env * in ft_new_env"));
	}
	(*env)->var = var;
	(*env)->globale = globale;
	return (1);
}

int	ft_new_token(t_list **tokens, int code, char *word)
{
	t_token		*token;
	t_list		*node;

	token = (t_token *) malloc(sizeof(t_token));
	if (!token)
		return (ft_allocated_err(0, "t_token * in ft_new_token"));
	token->code = code;
	token->word = word;
	node = ft_lstnew((void *) token);
	if (!node)
	{
		ft_del_token((void *) token);
		return (ft_allocated_err(0, "node in ft_new_token"));
	}
	ft_lstadd_back(tokens, node);
	return (1);
}

int	ft_new_command(t_command **command)
{
	*command = (t_command *) malloc(sizeof(t_command));
	if (!(*command))
		return (ft_allocated_err(0, "t_command * in ft_new_command"));
	(*command)->id = 0;
	(*command)->args = NULL;
	(*command)->cmd = NULL;
	(*command)->redir = NULL;
	(*command)->env_var = NULL;
	return (1);
}

/*int	ft_new_output(t_output **output)
{
	*output = (t_output *) malloc(sizeof(t_output));
	if (!(*output))
		return (ft_allocated_err(0, "t_output * in ft_new_output"));
	(*output)->filename = NULL;
	(*output)->append = 0;
	return (1);
}

int	ft_new_input(t_input **input)
{
	*input = (t_input *) malloc(sizeof(t_input));
	if (!(*input))
		return (ft_allocated_err(0, "t_input * in ft_new_input"));
	(*input)->keyboard = 0;
	(*input)->filename = NULL;
	(*input)->heredoc = NULL;
	return (1);
}*/

int	ft_new_node(t_list **node, void *content)
{
	*node = ft_lstnew(content);
	if (!(*node))
		return (0);
	return (1);
}

int	ft_new_redir(t_redir **redir, int code, char *str)
{
	*redir = (t_redir *) malloc(sizeof(t_redir));
	if (!(*redir))
		return (0);
	(*redir)->outfile = NULL;
	(*redir)->appendfile = NULL;
	(*redir)->infile = NULL;
	(*redir)->heredoc = NULL;
	if (code == LESS)
		(*redir)->infile = str;
	if (code == LESSLESS)
		(*redir)->heredoc = str;
	if (code == GREAT)
		(*redir)->outfile = str;
	if (code == GREATGREAT)
		(*redir)->appendfile = str;
	return (1);
}
