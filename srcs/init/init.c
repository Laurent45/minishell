/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 09:27:47 by lfrederi          #+#    #+#             */
/*   Updated: 2022/09/07 09:51:17 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"
#include <stddef.h>

void	ft_init_built(t_built *builts)
{
	builts[0].func = "echo";
	builts[0].f = &ft_echo;
	builts[1].func = "cd";
	builts[1].f = &ft_cd;
	builts[2].func = "pwd";
	builts[2].f = &ft_pwd;
	builts[3].func = "export";
	builts[3].f = &ft_export;
	builts[4].func = "unset";
	builts[4].f = &ft_unset;
	builts[5].func = "env";
	builts[5].f = &ft_env;
	builts[6].func = "exit";
	builts[6].f = &ft_exit_built;
	builts[7].func = NULL;
	builts[7].f = NULL;
}

int	init_shell(char *envp[], t_list **clone_env, t_built *builts)
{
	if (ft_clone_env(clone_env, envp) == FAILED)
		return (FAILED);
	ft_init_built(builts);
	return (SUCCESS);
}
