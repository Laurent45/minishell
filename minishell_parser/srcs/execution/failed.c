/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   failed.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 11:37:48 by lfrederi          #+#    #+#             */
/*   Updated: 2022/07/07 17:52:10 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "error.h"
#include "signal.h"

int	ft_execute_failed(t_list *node_command, char *func, int ret)
{
	t_command	*command;

	while (node_command)
	{
		command = (t_command *) node_command->content;
		if (command->pid == 0)
			break ;
		kill(command->pid, SIGTERM);
		node_command = node_command->next;
	}
	ft_perror(ret, func);
	return (ret);
}
