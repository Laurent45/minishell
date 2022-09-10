/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 15:54:42 by lfrederi          #+#    #+#             */
/*   Updated: 2022/09/10 10:53:56 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "error.h"
#include "ft_string.h"
#include "env.h"
#include "builtins.h"
#include "expansion.h"
#include "command.h"

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>

void	exit_clear(t_list **commands, t_list **my_envp, int ret)
{
	clear_env(my_envp, 0);
	clear_cmds(commands, 0);
	rl_clear_history();
	exit(ret);
}

int	child_std(t_list *node_cmd, int pipe[2], int tmpin)
{
	t_command	*cmd;

	cmd = (t_command *) node_cmd->content;
	if (cmd->num != 0 && dup2(tmpin, 0) == -1)
		return (FAILED);
	if (node_cmd->next && dup2(pipe[1], 1) == -1)
		return (FAILED);
	close(pipe[0]);
	close(pipe[1]);
	return (SUCCESS);
}

void	child_pipeline(t_list **commands, t_command *cmd, t_built *builts\
		, t_list **my_envp)
{
	t_built	*built;

	if (expand_cmdargs(&cmd->cmd_args, *my_envp) == FAILED)
		exit_clear(commands, my_envp, FAILED);
	if (redirection(cmd, *my_envp) == FAILED)
		exit_clear(commands, my_envp, FAILED);
	if (assignement(my_envp, cmd->env_var, 1) == FAILED)
		exit_clear(commands, my_envp, FAILED);
	if (cmd->cmd_args == NULL)
		exit_clear(commands, my_envp, FAILED);
	built = isbuiltins(cmd->cmd_args, builts);
	if (built)
		exit_clear(commands, my_envp, run_builtins(built, cmd, my_envp));
	exit_clear(commands, my_envp, run_executable(cmd, my_envp));
}

void	child_simple_cmd(t_list **commands, t_list **my_envp)
{
	t_command	*cmd;

	cmd = (t_command *)(*commands)->content;
	if (redirection(cmd, *my_envp) == FAILED)
		exit_clear(commands, my_envp, FAILED);
	if (cmd->cmd_args == NULL)
		exit_clear(commands, my_envp, SUCCESS);
	if (cmd->cmd_args && assignement(my_envp, cmd->env_var, 1) == FAILED)
		exit_clear(commands, my_envp, FAILED);
	exit_clear(commands, my_envp, run_executable(cmd, my_envp));
}
