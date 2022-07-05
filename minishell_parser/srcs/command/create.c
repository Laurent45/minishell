/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 12:42:21 by lfrederi          #+#    #+#             */
/*   Updated: 2022/07/05 14:43:05 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "error.h"
#include <stdlib.h>

int	ft_new_command(t_command **command)
{
	*command = (t_command *) malloc(sizeof(t_command));
	if (!(*command))
		return (ft_allocated_err(0, "t_command * in ft_new_command"));
	(*command)->id = 0;
	(*command)->cmd_args = NULL;
	(*command)->redir = NULL;
	(*command)->env_var = NULL;
	return (1);
}
