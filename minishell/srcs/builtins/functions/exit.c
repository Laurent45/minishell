/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 22:36:17 by lfrederi          #+#    #+#             */
/*   Updated: 2022/08/20 11:05:27 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "error.h"
#include "env.h"

#include <stdio.h>

static int	ft_islong(char *str)
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

int	ft_exit_built(t_list *args)
{
	printf("exit\n");
	if (args->next == NULL)
	{
		ft_add_existatus(0);
		return (EXIT_BUILT);
	}
	if (ft_islong((char *) args->next->content) == 0)
	{
		ft_add_existatus(2);
		return (ft_puterror(EXIT_BUILT, "exit: numeric argument required"));
	}
	if (ft_lstsize(args) > 2)
		return (ft_puterror(1, "exit: too many args"));
	ft_add_existatus(123);
	return (EXIT_BUILT);
}
