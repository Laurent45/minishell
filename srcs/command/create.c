/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 12:42:21 by lfrederi          #+#    #+#             */
/*   Updated: 2022/07/31 14:55:10 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "error.h"
#include <stdlib.h>

int	ft_new_command(t_command **command, int num)
{
	*command = (t_command *) malloc(sizeof(t_command));
	if (!(*command))
		return (ft_puterror(CMD_FAILED, "t_command * in ft_new_command"));
	(*command)->pid = 0;
	(*command)->num = num;
	(*command)->cmd_args = NULL;
	(*command)->redir = NULL;
	(*command)->env_var = NULL;
	return (CMD_SUCCESS);
}

int	ft_new_redir(t_redir **redir)
{
	*redir = (t_redir *) malloc(sizeof(t_redir));
	if (!(*redir))
		return (ft_puterror(0, "t_redir * in ft_new_redir"));
	(*redir)->file = NULL;
	(*redir)->heredoc = NULL;
	return (1);
}
