/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 16:55:27 by lfrederi          #+#    #+#             */
/*   Updated: 2022/08/18 19:07:07 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "ft_string.h"
#include "execution.h"
#include "error.h"

#include <stddef.h>
#include <unistd.h>

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

t_built	*ft_isbuiltins(t_list *cmd_args, t_built *builts)
{
	int	i;

	if (cmd_args == NULL)
		return (NULL);
	i = 0;
	while (builts[i].func)
	{
		if (ft_strcmp(builts[i].func, (char *) cmd_args->content) == 0)
			return (&builts[i]);
		i++;
	}
	return (NULL);
}
