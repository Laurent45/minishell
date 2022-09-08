/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 12:44:22 by lfrederi          #+#    #+#             */
/*   Updated: 2022/09/08 14:32:22 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

#include <stdlib.h>
#include <unistd.h>

void	del_str(void *content)
{
	free(content);
}

void	del_redir(void *redir)
{
	t_redir	*rd;

	if (!redir)
		return ;
	rd = (t_redir *) redir;
	free(rd->file);
	ft_lstclear(&rd->heredoc, &del_str);
	unlink(rd->file_heredoc);
	free(rd->file_heredoc);
	rd->file = NULL;
	rd->heredoc = NULL;
	rd->file_heredoc = NULL;
	free(rd);
}

void	del_cmd(void *command)
{
	t_command	*cmd;

	cmd = (t_command *) command;
	ft_lstclear(&cmd->cmd_args, &del_str);
	ft_lstclear(&cmd->redir, &del_redir);
	ft_lstclear(&cmd->env_var, &del_str);
	cmd->cmd_args = NULL;
	cmd->redir = NULL;
	cmd->env_var = NULL;
	free(command);
}

int	clear_cmds(t_list **commands, int ret)
{
	ft_lstclear(commands, &del_cmd);
	return (ret);
}
