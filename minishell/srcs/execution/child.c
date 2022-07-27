/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 15:54:42 by lfrederi          #+#    #+#             */
/*   Updated: 2022/07/27 16:47:50 by lfrederi         ###   ########.fr       */
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

extern t_list	*g_envs;

static void	ft_exit(t_list **commands, int ret)
{
	ft_clear_env(&g_envs, 0);
	ft_clear_commands(commands, 0);
	rl_clear_history();
	exit(ret);
}

void	ft_child_std(t_list **cmds, t_list *node_cmd, int pipe[2], int tmpin)
{
	t_command	*cmd;

	cmd = (t_command *) node_cmd->content;
	if (cmd->num != 0 && dup2(tmpin, 0) == -1)
		ft_exit(cmds, 1);
	if (node_cmd->next && dup2(pipe[1], 1) == -1)
		ft_exit(cmds, 1);
	close(pipe[0]);
	close(pipe[1]);
}

void	ft_child_pipeline(t_list **commands, t_command *cmd, t_built *builts)
{
	t_built	*built;

	if (ft_expand_cmdargs(&cmd->cmd_args) == 0)
		ft_exit(commands, EXPAND_FAILED);
	if (ft_redirection(cmd) == 0)
		ft_exit(commands, REDIR_FAILED);
	if (ft_assignement(cmd->env_var, 1) == 0)
		ft_exit(commands, ASSIGNEMENT_FAILED);
	if (cmd->cmd_args == NULL)
		ft_exit(commands, 0);
	built = ft_isbuiltins(cmd->cmd_args, builts);
	if (built)
		ft_exit(commands, ft_run_builtins(built, cmd));
	ft_exit(commands, ft_run_executable(cmd));
}

void	ft_child_simple_cmd(t_list **commands)
{
	t_command	*cmd;

	cmd = (t_command *)(*commands)->content;
	if (ft_redirection(cmd) == 0)
		ft_exit(commands, REDIR_FAILED);
	if (cmd->cmd_args == NULL)
		ft_exit(commands, 0);
	if (cmd->cmd_args && ft_assignement(cmd->env_var, 1) == 0)
		ft_exit(commands, ASSIGNEMENT_FAILED);
	ft_exit(commands, ft_run_executable(cmd));
}
