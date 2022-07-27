/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 12:44:22 by lfrederi          #+#    #+#             */
/*   Updated: 2022/07/22 16:07:08 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include <stdlib.h>

void	ft_del_str(void	*content)
{
	free(content);
}

void	ft_del_redir(void *redir)
{
	t_redir	*rd;

	rd = (t_redir *) redir;
	if (rd->file)
		free(rd->file);
	if (rd->heredoc)
		ft_lstclear(&rd->heredoc, &ft_del_str);
	rd->file = NULL;
	rd->heredoc = NULL;
	free(rd);
}

void	ft_del_command(void	*command)
{
	t_command	*cmd;

	cmd = (t_command *) command;
	if (cmd->cmd_args)
		ft_lstclear(&cmd->cmd_args, &ft_del_str);
	if (cmd->redir)
		ft_lstclear(&cmd->redir, &ft_del_redir);
	if (cmd->env_var)
		ft_lstclear(&cmd->env_var, &ft_del_str);
	cmd->cmd_args = NULL;
	cmd->redir = NULL;
	cmd->env_var = NULL;
	free(command);
}

int	ft_clear_commands(t_list **commands, int ret)
{
	ft_lstclear(commands, &ft_del_command);
	return (ret);
}
