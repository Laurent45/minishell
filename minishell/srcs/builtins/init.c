/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 16:55:27 by lfrederi          #+#    #+#             */
/*   Updated: 2022/07/27 16:59:07 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "ft_string.h"
#include "execution.h"
#include "error.h"

#include <stddef.h>
#include <unistd.h>

void	ft_init_built(t_built *builts)
{
	builts[0].func = "echo";
	builts[0].f = &ft_echo;
	builts[1].func = "cd";
	builts[1].f = &ft_cd;
	builts[2].func = "pwd";
	builts[2].f = &ft_pwd;
	builts[3].func = "export";
	builts[3].f = &ft_export;
	builts[4].func = "unset";
	builts[4].f = &ft_unset;
	builts[5].func = "env";
	builts[5].f = &ft_env;
	builts[6].func = "exit";
	builts[6].f = &ft_exit_built;
	builts[7].func = NULL;
	builts[7].f = NULL;
}

t_built	*ft_isbuiltins(t_list *cmd_args, t_built *builts)
{
	int	i;

	if (cmd_args == NULL)
		return (NULL);
	i = 0;
	while (builts[i].func)
	{
		if (ft_strcmp(builts[i].func, (char *) cmd_args->content) == 0)
			return (&builts[i]);
		i++;
	}
	return (NULL);
}

int	ft_run_builtins(t_built *built, t_command *command)
{
	int	tmp_stdin;
	int	tmp_stdout;
	int	status;

	tmp_stdin = dup(STDIN_FILENO);
	if (tmp_stdin == -1)
		return (ft_perror(REDIR_FAILED, "dup"));
	tmp_stdout = dup(STDOUT_FILENO);
	if (tmp_stdout == -1)
	{
		close(tmp_stdin);
		return (ft_perror(REDIR_FAILED, "dup"));
	}
	if (ft_redirection(command) == REDIR_FAILED)
	{
		dup2(tmp_stdin, 0);
		dup2(tmp_stdout, 1);
		return (REDIR_FAILED);
	}
	status = built->f(command->cmd_args);
	dup2(tmp_stdin, 0);
	dup2(tmp_stdout, 1);
	return (status);
}
