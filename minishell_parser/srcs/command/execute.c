/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 19:35:11 by lfrederi          #+#    #+#             */
/*   Updated: 2022/06/20 14:29:57 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "print.h"
#include "ft_string.h"
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>

extern t_list	*envs;

int	ft_check_exe(char *exe)
{
	if (ft_strchr(exe, '/'))
	{
		return (1);
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

int	ft_execute(t_list *command)
{
	int	fd[2];
	int	id;
	int	wstatus;
	char	**arg = NULL;;
	char	**envp = NULL;
	t_command	*cmd;
	t_list *tmp = command;

	int	pos = 0;
	int nb_cmd = ft_lstsize(command);

	if (pipe(fd) == -1)
		return (0);
	envp = ft_lst_to_array(envs);
	while (command)
	{
		cmd = (t_command *) command->content;
		if (ft_check_exe((char *) cmd->args->content) == 0)
			break ;
		arg = ft_lst_to_array(cmd->args);
		id = fork();
		if (id == 0)
		{
			execve(arg[0], arg, envp);
		}
		else
		{
			cmd->id = id;
			printf("fork() id = %d\n", id);
		}
		free(arg);
		pos++;
		command = command->next;
	}
	for (int i = 0; i < nb_cmd; i++)
	{
		cmd = (t_command *) tmp->content;
		int wait = waitpid(-1, &wstatus, 0);
		printf("Child process of parent process %d is terminated and exit status is %d\n", wait, WEXITSTATUS(wstatus));
		tmp = tmp->next;
	}
	free(envp);
	close(fd[0]);
	close(fd[1]);
	return (1);
}
