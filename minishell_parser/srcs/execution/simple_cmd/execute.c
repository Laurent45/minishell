/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 10:40:14 by lfrederi          #+#    #+#             */
/*   Updated: 2022/07/19 11:06:21 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "builtins.h"
#include "error.h"

#include <unistd.h>

extern t_list *envs;

void	ft_simple_cmd(t_list **commands)
{
	char	**args;
	char	**envp;
	int		status;
	t_command	*cmd;

	cmd = (t_command *) (*commands)->content;
	if (ft_redirection(cmd) == 0)
		ft_exit(commands, NULL, NULL, 1);
	status = ft_search_exe(cmd->cmd_args);
	if (status == 1)
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
	ft_exit(commands, envp, args, status);
}
