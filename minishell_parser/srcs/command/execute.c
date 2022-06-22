/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 19:35:11 by lfrederi          #+#    #+#             */
/*   Updated: 2022/06/22 15:17:41 by lfrederi         ###   ########.fr       */
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
#include <fcntl.h>

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

int	ft_set_input(t_command *cmd, int fdin)
{
	int	file;

	if (dup2(fdin, 0) == -1)
		return (ft_perror(0, "dup2"));
	close(fdin);
	if (cmd->input == NULL)
		return (1);
	if (cmd->input->keyboard == 0)
	{
		file = open(cmd->input->filename, O_RDONLY);
		if (file == -1)
		{
			cmd->redirect_failed = 1;
			return (ft_perror(1, "open"));
		}
	}
	//else
	//{
		// heredoc
	//}
	if (dup2(file, 0) == -1)
		return (ft_perror(0, "dup2"));
	close(file);
	return (1);
}

int	ft_set_output(t_list *command, int fd_in_out[2], int tmpout)
{
	//t_command	*cmd;
	int			fd_pipe[2];

	//cmd = (t_command *) command->content;
	if (command->next != NULL)
	{
		if (pipe(fd_pipe) == -1)
			return (ft_perror(0, "pipe"));
		fd_in_out[0] = fd_pipe[0];
		fd_in_out[1] = fd_pipe[1];
	}
	//else if (cmd->output)
	//{
	//}
	else
		fd_in_out[1] = tmpout;
	if (dup2(fd_in_out[1], 1) == -1)
		return (ft_perror(0, "dup2"));
	close(fd_in_out[1]);
	return (1);
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
		return (ft_perror(0, "execve 127"));
	}
	return (1);
}

int	ft_test(t_list *command, int fd_in_out[2], int tmpout, char **envp)
{
	t_command	*cmd;
	char		**args;

	while (command)
	{
		cmd = (t_command *) command->content;
		if (ft_set_input(cmd, fd_in_out[0]) == 0)
			return (0);
		if (ft_set_output(command, fd_in_out, tmpout) == 0)
			return (0);
		args = ft_lst_to_array(cmd->args);
		if (!args)
			return (ft_allocated_err(0, "char ** in ft_execute"));
		if (ft_exec_cmd(cmd, args, envp) == 0) // Run cmd in child process
		{
			free(envp);
			free(args);
			return (0);
		}
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

void	ft_init_std_stream(int fd_saved[2])
{
	if (dup2(0, fd_saved[0]) != -1)
		close(fd_saved[0]);
	if (dup2(1, fd_saved[1]) != -1)
		close(fd_saved[1]);
}

int	ft_saved_std_stream(int std_saved[2])
{
	std_saved[0] = dup(STDIN_FILENO);
	std_saved[1] = dup(STDOUT_FILENO);
	if (std_saved[0] == -1 || std_saved[1] == -1)
		return (ft_perror(0, "dup"));
	return (1);
}

int	ft_execute(t_list *command)
{
	int			std_saved[2];
	int			fd_in_out[2];
	int			tmpout;
	char		**envp;

	envp = ft_lst_to_array(envs);
	if (ft_saved_std_stream(std_saved) == 0)
		return (0);
	tmpout = dup(1);
	if (tmpout == -1)
		ft_perror(0, "dup");
	fd_in_out[0] = dup(0);
	if (fd_in_out[0] == -1)
		return (ft_perror(0, "dup"));
	fd_in_out[1] = STDOUT_FILENO;
	if (ft_test(command, fd_in_out, tmpout, envp) == 0)
		return (0);
	ft_init_std_stream(std_saved);
	ft_wait_process(command);
	free(envp);
	return (1);
}
