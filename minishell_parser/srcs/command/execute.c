/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 19:35:11 by lfrederi          #+#    #+#             */
/*   Updated: 2022/06/22 21:58:35 by lfrederi         ###   ########.fr       */
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

int	ft_exec_cmd(t_command *cmd, char **args, char **envp)
{
	int		id;

	if (cmd->redirect_failed || cmd->args == NULL)
		return (1);
	id = fork();
	if (id == -1)
		return (ft_perror(0, "fork"));
	if (id == 0)
	{
		//ft_set_path_exe(cmd);
		execve(args[0], args, envp);
		return (ft_perror(127, "execve"));
	}
	return (1);
}

int	ft_run_cmd(t_list *command, int fd_in_out[2], int tmpout, char **envp)
{
	t_command	*cmd;
	t_list		*first;
	char		**args;
	int			ret_exec;

	first = command;
	while (command)
	{
		cmd = (t_command *) command->content;
		if (ft_set_input(cmd, fd_in_out[0]) == 0)
			ft_exit(first, envp, NULL, -1);
		if (ft_set_output(command, fd_in_out, tmpout) == 0)
			ft_exit(first, envp, NULL, -1);
		args = ft_lst_to_array(cmd->args);
		if (!args)
		{
			ft_allocated_err(0, "char ** in ft_execute");
			ft_exit(first, envp, NULL, -1);
		}
		ret_exec = ft_exec_cmd(cmd, args, envp);
		if (ret_exec == 0 || ret_exec == 127)
			ft_exit(first, envp, args, ret_exec);
		free(args);
		command = command->next;
	}
	return (1);
}

void	ft_wait_process(t_list *command)
{
	int	wstatus;
	int	ret;

	while (command)
	{
		ret = waitpid(-1, &wstatus, 0);
		printf("Waitting terminated, process (%d) and exit status = %d\n", ret, WEXITSTATUS(wstatus));
		command = command->next;
	}
}

int	ft_execute(t_list *command)
{
	int			std_saved[2];
	int			fd_in_out[2];
	int			tmpout;
	char		**envp;

	envp = ft_lst_to_array(envs);
	if (ft_saved_std(std_saved) == 0)
		ft_exit(command, envp, NULL, -1);

	tmpout = dup(1);
	fd_in_out[0] = dup(0);
	if (tmpout == -1 || fd_in_out[0] == -1)
	{
		ft_perror(0, "dup");
		ft_exit(command, envp, NULL, -1);
	}
	fd_in_out[1] = STDOUT_FILENO;

	if (ft_run_cmd(command, fd_in_out, tmpout, envp) == 0)
		return (0);
//	if (ft_init_stream(std_saved) == 0)
//		ft_exit(command, envp, NULL, -1);
	ft_wait_process(command);
	free(envp);
	return (1);
}
