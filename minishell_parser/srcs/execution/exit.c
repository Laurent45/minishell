/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 17:39:17 by lfrederi          #+#    #+#             */
/*   Updated: 2022/07/05 15:49:03 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "command.h"
#include <signal.h>
#include <stdlib.h>
#include "error.h"

extern t_list *envs;

void ft_exit(t_list **commands, char **envp, char **args, int ret)
{
	if (envp)
		free(envp);
	if (args)
		free(args);
	ft_clear_env(&envs, 0);
	ft_clear_commands(commands, 0);
	exit(ret);
}

