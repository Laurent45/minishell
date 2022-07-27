/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 15:54:42 by lfrederi          #+#    #+#             */
/*   Updated: 2022/07/19 10:59:15 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "execution.h"
#include "error.h"
#include "ft_string.h"
#include "env.h"
#include "builtins.h"

#include <stdio.h>

extern t_list	*envs;

void	ft_run_exe(t_list **commands, t_command *cmd, t_built *builts)
{
	char	**args;
	char	**envp;
	t_built	*built;

	built = ft_isbuiltins((char *) cmd->cmd_args->content, builts);
	if (built)
		ft_exit(commands, NULL, NULL, ft_exe_builtins(built, cmd));
	if (ft_search_exe(cmd->cmd_args) == 1)
	{
		args = ft_args_to_array(cmd->cmd_args);
		envp = ft_envs_to_array(envs);
		if (!args || !envp)
			ft_exit(commands, envp, args, -1);
		if (!args[0])
			ft_exit(commands, envp, args, 0);
		execve(args[0], args, envp);
		ft_perror(-1, "execve");
	}
	ft_exit(commands, envp, args, 127);
}

void	ft_child(t_list **commands, t_list *node_cmd, int pipe[2], int tmpin)
{
	t_command	*cmd;

	cmd = (t_command *) node_cmd->content;
	if (cmd->num != 0 && dup2(tmpin, 0) == -1)
		ft_exit(commands, NULL, NULL, 1);
	if (node_cmd->next && dup2(pipe[1], 1) == -1)
		ft_exit(commands, NULL, NULL, 1);
	close(pipe[0]);
	close(pipe[1]);
	if (ft_redirection(cmd) == 0)
		ft_exit(commands, NULL, NULL, 1);
}
