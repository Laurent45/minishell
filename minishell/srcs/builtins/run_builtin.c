/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 19:03:01 by lfrederi          #+#    #+#             */
/*   Updated: 2022/08/18 19:07:07 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "execution.h"
#include "error.h"

#include <unistd.h>

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
	if (ft_redirection(command) == 0)
	{
		dup2(tmp_stdin, 0);
		dup2(tmp_stdout, 1);
		return (close(tmp_stdin), close(tmp_stdout), REDIR_FAILED);
	}
	status = built->f(command->cmd_args);
	dup2(tmp_stdin, 0);
	dup2(tmp_stdout, 1);
	return (close(tmp_stdin), close(tmp_stdout), status);
}
