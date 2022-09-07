/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 22:36:17 by lfrederi          #+#    #+#             */
/*   Updated: 2022/09/07 22:29:44 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "error.h"
#include "env.h"
#include "ft_string.h"

#include <stdio.h>

extern int g_exit_status;

static int	islong(char *str)
{
	int		i;
	long	res;

	i = 0;
	res = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		res = (res * 10) + (str[i] - '0');
		if (str[0] == '-')
		{
			if (str[i + 1] && (-res < -(res * 10 + (str[i + 1] - '0'))))
				return (0);
		}
		else
		{
			if (str[i + 1] && (res > (res * 10 + (str[i + 1] - '0'))))
				return (0);
		}
		i++;
	}
	return (1);
}

int	built_exit(t_list *args, t_list **my_envp)
{
	(void) my_envp;

	long	status;

	printf("exit\n");
	if (args->next == NULL)
	{
		g_exit_status = 0;
		return (EXIT_BUILT);
	}
	if (islong((char *) args->next->content) == 0)
	{
		g_exit_status = 2;
		return (puterror(EXIT_BUILT, "exit: numeric argument required"));
	}
	if (ft_lstsize(args) > 2)
		return (puterror(FAILED, "exit: too many args"));
	status = (unsigned long) ft_atol((char *) args->next->content);
	g_exit_status = status % 256;
	return (EXIT_BUILT);
}
