/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 22:38:42 by lfrederi          #+#    #+#             */
/*   Updated: 2022/09/08 16:29:39 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "ft_stdio.h"
#include "init.h"

static int	check_newline(t_list **args)
{
	int		newline;
	char	*args_str;
	int		i;

	newline = 1;
	while (*args)
	{
		*args = (*args)->next;
		args_str = (char *) (*args)->content;
		i = 0;
		if (args_str[i] == '-')
		{
			i++;
			while (args_str[i] == 'n')
				i++;
			if (args_str[i] == '\0')
				newline = 0;
			else
				break ;
		}
		else
			break ;
	}
	return (newline);
}

int	built_echo(t_list *args, t_list **my_envp)
{
	(void) my_envp;
	int		newline;

	newline = check_newline(&args);
	while (args)
	{
		ft_putstr_fd((char *) args->content, 1);
		ft_putstr_fd(" ", 1);
		args = args->next;
	}
	if (newline)
		ft_putstr_fd("\n", 1);
	return (set_status(0), SUCCESS);
}
