/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stream.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 17:14:02 by lfrederi          #+#    #+#             */
/*   Updated: 2022/06/22 21:34:25 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "error.h"
#include <unistd.h>
#include <fcntl.h>

int	 ft_init_stream(int fd_saved[2])
{
	if (dup2(0, fd_saved[0]) == -1)
		return (0);
	close(fd_saved[0]);
	if (dup2(1, fd_saved[1]) == -1)
		return (0);
	close(fd_saved[1]);
	return (1);
}

int	ft_saved_std(int std_saved[2])
{
	std_saved[0] = dup(STDIN_FILENO);
	std_saved[1] = dup(STDOUT_FILENO);
	if (std_saved[0] == -1 || std_saved[1] == -1)
		return (ft_perror(0, "dup"));
	return (1);
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
	int			fd_pipe[2];

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
