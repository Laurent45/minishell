/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 19:35:11 by lfrederi          #+#    #+#             */
/*   Updated: 2022/09/12 22:28:52 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "error.h"
#include "execution.h"
#include "expansion.h"
#include "builtins.h"
#include "env.h"

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>

static int	pipefd_parent(int tmpin, int pipe_fd[2])
{
	if (tmpin != -1)
		close(tmpin);
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}

static int	failed(t_list *node_command, char *func, int ret, int pipe[2])
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

int	exe_pipeline(t_list **commands, t_built *builts, t_list **my_envp)
{
	t_list		*cmd;
	int			tmpin;
	int			pipe_fd[2];

	cmd = *commands;
	tmpin = -1;
	while (cmd)
	{
		if (pipe(pipe_fd) == -1)
			return (failed(*commands, "pipe", 1, NULL));
		((t_command *) cmd->content)->pid = fork();
		if (((t_command *) cmd->content)->pid == -1)
			return (failed(*commands, "fork", 1, pipe_fd));
		if (((t_command *) cmd->content)->pid != 0)
			tmpin = pipefd_parent(tmpin, pipe_fd);
		else
		{
			if (child_std(cmd, pipe_fd, tmpin) == FAILED)
				exit_clear(commands, my_envp, 1);
			pipeline(commands, cmd->content, builts, my_envp);
		}
		cmd = cmd->next;
	}
	close(tmpin);
	return (wait_child(*commands));
}

int	exe_simple_cmd(t_list **commands, t_built *builts, t_list **env)
{
	int			id;
	t_command	*cmd;
	t_built		*built;

	cmd = (t_command *)(*commands)->content;
	if (expand_cmdargs(&cmd->cmd_args, *env) == FAILED)
		return (FAILED);
	built = isbuiltins(cmd->cmd_args, builts);
	if (built)
		return (run_builtins(built, cmd, env));
	if (cmd->cmd_args == NULL && assignement(env, cmd->env_var, 0) == FAILED)
		return (FAILED);
	id = fork();
	cmd->pid = id;
	if (id == -1)
		return (ft_perror(FAILED, "fork"));
	if (id == 0)
		child_simple_cmd(commands, env);
	return (wait_child(*commands));
}
