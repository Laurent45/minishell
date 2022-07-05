/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 19:35:11 by lfrederi          #+#    #+#             */
/*   Updated: 2022/07/05 16:02:49 by lfrederi         ###   ########.fr       */
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

#include <fcntl.h>

extern t_list	*envs;

int	ft_check_exe(char *exe)
{
	if (ft_strchr(exe, '/'))
	{		return (1);
	}
	else
	{
		return (1);
	}
}

char **ft_lst_to_array(t_list *lst)
{
	int		size;
	int		i;
	char	**ret;

	size = ft_lstsize(lst);
	ret = (char **) malloc(sizeof(char *) * (size + 1));
	if (!ret)
		return (NULL);
	i = 0;
	while (i < size)
	{
		ret[i] = (char *) lst->content;
		lst = lst->next;
		i++;
	}
	ret[i] = NULL;
	return (ret);
}


void	ft_run_child(t_list **commands, t_command *curr_cmd)
{
	char **args;
	char **envp;

	args = ft_lst_to_array(curr_cmd->cmd_args);
	envp = ft_lst_to_array(envs);
	execve(args[0], args, envp);
	ft_perror(-1, "execve");
	ft_exit(commands, envp, args, -1);
}

//TODO: Check return if pipe failed or dup
int	ft_execute(t_list **commands)
{
	t_list		*cmd;
	int			pipe_fd[2];
	int			pid;

	cmd = *commands;
	while (cmd)
	{
		if (pipe(pipe_fd) == -1)
			return (ft_perror(-1, "pipe"));
		pid = fork();
		if (pid == -1)
			return (ft_perror(-1, "fork"));
		if (ft_set_stream(commands, pid, pipe_fd, cmd) == 0)
			return (0);
		if (pid == 0)
			ft_run_child(commands, (t_command *) cmd->content);
		cmd = cmd->next;
	}

	waitpid(-1, NULL, 0);
	return (1);
	
}
