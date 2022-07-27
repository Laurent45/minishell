/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 15:24:38 by lfrederi          #+#    #+#             */
/*   Updated: 2022/07/12 16:07:10 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h`"



int	ft_search_exe(t_list *commands, int (*bult[3])(char *))
{
	t_command	*command;

	while (commands)
	{
		command = (t_command *) commands->content;
		if (command->cmd_args)
		{
			ft_is_bultin(command, command->cmd_args);
		}
			
		commands = commands->next;
	}
}
