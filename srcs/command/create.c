/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 12:42:21 by lfrederi          #+#    #+#             */
/*   Updated: 2022/09/08 14:13:17 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "error.h"
#include <stdlib.h>

int	new_node(t_list **node, void *content)
{
	*node = ft_lstnew(content);
	if (!(*node))
		return (FAILED);
	return (SUCCESS);
}

int	new_command(t_command **command, int num)
{
	*command = (t_command *) malloc(sizeof(t_command));
	if (!(*command))
		return (puterror(FAILED, "t_command * in new_command"));
	(*command)->pid = 0;
	(*command)->num = num;
	(*command)->cmd_args = NULL;
	(*command)->redir = NULL;
	(*command)->env_var = NULL;
	return (SUCCESS);
}

int	new_redir(t_redir **redir)
{
	*redir = (t_redir *) malloc(sizeof(t_redir));
	if (!(*redir))
		return (puterror(FAILED, "t_redir * in new_redir"));
	(*redir)->file = NULL;
	(*redir)->heredoc = NULL;
	(*redir)->file_heredoc = NULL;
	return (SUCCESS);
}
