/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 15:28:02 by lfrederi          #+#    #+#             */
/*   Updated: 2022/09/10 10:15:51 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "init.h"
#include "ft_stdio.h"

#include <sys/wait.h>

int	wait_child(t_list *command)
{
	int	wstatus;
	int	exitstatus;
	int	pid_last_cmd;

	exitstatus = 0;
	pid_last_cmd = ((t_command *) ft_lstlast(command)->content)->pid;
	while (command)
	{
		if (waitpid(-1, &wstatus, 0) == pid_last_cmd)
		{	
			if (WIFSIGNALED(wstatus))
				exitstatus = 128 + WTERMSIG(wstatus);
			else
				exitstatus = WEXITSTATUS(wstatus);
		}
		command = command->next;
	}
	set_status(exitstatus);
	if (exitstatus == 131)
		ft_putstr_fd("Quit (core dumped)\n", 2);
	return (SUCCESS);
}
