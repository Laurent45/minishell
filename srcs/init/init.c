/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 09:27:47 by lfrederi          #+#    #+#             */
/*   Updated: 2022/09/07 22:06:59 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"

#include <stddef.h>

extern int	g_exit_status;

void	init_built(t_built *builts)
{
	builts[0].func = "echo";
	builts[0].f = &built_echo;
	builts[1].func = "cd";
	builts[1].f = &built_cd;
	builts[2].func = "pwd";
	builts[2].f = &built_pwd;
	builts[3].func = "export";
	builts[3].f = &built_export;
	builts[4].func = "unset";
	builts[4].f = &built_unset;
	builts[5].func = "env";
	builts[5].f = &built_env;
	builts[6].func = "exit";
	builts[6].f = &built_exit;
	builts[7].func = NULL;
	builts[7].f = NULL;
}

int	init_shell(char *envp[], t_list **my_envp, t_built *builts)
{
	if (clone_env(my_envp, envp) == FAILED)
		return (FAILED);
	init_built(builts);
	g_exit_status = 0;
	return (SUCCESS);
}
