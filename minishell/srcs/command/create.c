/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 12:42:21 by lfrederi          #+#    #+#             */
/*   Updated: 2022/07/22 18:05:30 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "error.h"
#include <stdlib.h>

int	ft_new_command(t_command **command, int num)
{
	*command = (t_command *) malloc(sizeof(t_command));
	if (!(*command))
		return (ft_allocated_err(CMD_FAILED, "t_command * in ft_new_command"));
	(*command)->pid = 0;
	(*command)->num = num;
	(*command)->cmd_args = NULL;
	(*command)->redir = NULL;
	(*command)->env_var = NULL;
	return (CMD_SUCCESS);
}
