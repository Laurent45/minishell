/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 19:35:11 by lfrederi          #+#    #+#             */
/*   Updated: 2022/07/19 14:53:27 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "print.h"
#include "error.h"
#include "ft_string.h"
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>
#include "execution.h"
#include "expansion.h"
#include "builtins.h"

#include <fcntl.h>

int	ft_wait_child(t_list *command)
{
	int	wstatus;
	int	exitstatus;

	exitstatus = 0;
	while (command)
	{
		waitpid(-1, &wstatus, 0);
		if (exitstatus == 0)
		{	
			if (WIFSIGNALED(wstatus))
				exitstatus = 128 + WTERMSIG(wstatus);
			else
				exitstatus = WEXITSTATUS(wstatus);
		}
		command = command->next;
	}
	return (exitstatus);
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
			return (ft_execute_failed(*commands, "pipe", 0));
		((t_command *) cmd->content)->pid = fork();
		if (((t_command *) cmd->content)->pid == -1)
		{
			close(pipe_fd[0]);
			close(pipe_fd[1]);
			return (ft_execute_failed(*commands, "fork", 0));
		}
		if (((t_command *) cmd->content)->pid != 0)
		{
			if (tmpin != -1)
				close(tmpin);
			tmpin = pipe_fd[0];
			close(pipe_fd[1]);
		}
		else
		{
			ft_child(commands, cmd, pipe_fd, tmpin);
			ft_run_exe(commands, cmd->content, builts);
		}
		cmd = cmd->next;
	}
	close(tmpin);
	return (ft_wait_child(*commands));
}

int	ft_execute(t_list **commands, t_built *builts)
{
	t_built		*built;
	t_command	*cmd;
	int			id;

	if (ft_lstsize(*commands) == 1)
	{
		cmd = (t_command *) (*commands)->content;
		if (ft_expand_cmdargs(&cmd->cmd_args) == 0)
			return (0);
		built = ft_isbuiltins((char *) cmd->cmd_args->content, builts);
		if (built)
			return (ft_exe_builtins(built, cmd));
		else
		{
			id = fork();
			if (id == -1)
				return (0);
			if (id == 0)
				ft_simple_cmd(commands);
			else
				return (ft_wait_child(*commands));
		}
	}
	return (ft_pipeline(commands, builts));
}








/*
//TODO: Check return if pipe failed or dup
int	ft_pipeline(t_list **commands)
{
	t_list		*cmd;
	int			tmpin;
	int			pipe_fd[2];

	cmd = *commands;
	tmpin = -1;
	while (cmd)
	{
		if (pipe(pipe_fd) == -1)
			return (ft_execute_failed(*commands, "pipe", 0));
		((t_command *) cmd->content)->pid = fork();
		if (((t_command *) cmd->content)->pid == -1)
		{
			close(pipe_fd[0]);
			close(pipe_fd[1]);
			return (ft_execute_failed(*commands, "fork", 0));
		}
		if (((t_command *) cmd->content)->pid != 0)
		{
			if (tmpin != -1)
				close(tmpin);
			tmpin = pipe_fd[0];
			close(pipe_fd[1]);
		}
		else
			ft_child(commands, cmd, pipe_fd, tmpin);
		cmd = cmd->next;
	}
	close(tmpin);
	return (ft_wait_child(*commands));
}
*/
