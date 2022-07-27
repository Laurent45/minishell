/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 19:35:11 by lfrederi          #+#    #+#             */
/*   Updated: 2022/07/27 16:50:04 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "print.h"
#include "error.h"
#include "ft_string.h"
#include "execution.h"
#include "expansion.h"
#include "builtins.h"
#include "env.h"

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>

static int	ft_pipefd_parent(int tmpin, int pipe_fd[2])
{
	if (tmpin != -1)
		close(tmpin);
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}

static int	ft_failed(t_list *node_command, char *func, int ret, int pipe[2])
{
	t_command	*command;

	while (node_command)
	{
		command = (t_command *) node_command->content;
		if (command->pid == 0)
			break ;
		kill(command->pid, SIGTERM);
		node_command = node_command->next;
	}
	if (pipe)
	{
		close(pipe[0]);
		close(pipe[1]);
	}
	ft_perror(ret, func);
	return (ret);
}

static int	ft_pipeline(t_list **commands, t_built *builts)
{
	t_list		*cmd;
	int			tmpin;
	int			pipe_fd[2];

	cmd = *commands;
	tmpin = -1;
	while (cmd)
	{
		if (pipe(pipe_fd) == -1)
			return (ft_failed(*commands, "pipe", 1, NULL));
		((t_command *) cmd->content)->pid = fork();
		if (((t_command *) cmd->content)->pid == -1)
			return (ft_failed(*commands, "fork", 1, pipe_fd));
		if (((t_command *) cmd->content)->pid != 0)
			tmpin = ft_pipefd_parent(tmpin, pipe_fd);
		else
		{
			ft_child_std(commands, cmd, pipe_fd, tmpin);
			ft_child_pipeline(commands, cmd->content, builts);
		}
		cmd = cmd->next;
	}
	close(tmpin);
	return (ft_wait_child(*commands));
}

static int	ft_simple_cmd(t_list **commands, t_built *builts)
{
	int			id;
	t_command	*cmd;
	t_built		*built;

	cmd = (t_command *)(*commands)->content;
	if (ft_expand_cmdargs(&cmd->cmd_args) == 0)
		return (EXPAND_FAILED);
	built = ft_isbuiltins(cmd->cmd_args, builts);
	if (built)
		return (ft_run_builtins(built, cmd));
	if (cmd->cmd_args == NULL && ft_assignement(cmd->env_var, 0) == 0)
		return (ASSIGNEMENT_FAILED);
	id = fork();
	cmd->pid = id;
	if (id == -1)
		return (ft_perror(1, "fork"));
	if (id == 0)
		ft_child_simple_cmd(commands);
	return (ft_wait_child(*commands));
}

int	ft_execute(t_list **commands, t_built *builts)
{
	if (ft_lstsize(*commands) == 1)
		return (ft_simple_cmd(commands, builts));
	return (ft_pipeline(commands, builts));
}
