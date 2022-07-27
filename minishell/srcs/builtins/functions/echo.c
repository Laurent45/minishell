/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 22:38:42 by lfrederi          #+#    #+#             */
/*   Updated: 2022/07/23 22:00:09 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "error.h"
#include "expansion.h"
#include "ft_string.h"
#include "ft_stdio.h"

int	ft_echo(t_list *args)
{
	int		newline;

	newline = 1;
	if (args->next && ft_strcmp((char *) args->next->content, "-n") == 0)
	{
		newline = 0;
		args = args->next;
	}
	args = args->next;
	while (args)
	{
		ft_putstr_fd((char *) args->content, 1);
		ft_putstr_fd(" ", 1);
		args = args->next;
	}
	if (newline)
		ft_putstr_fd("\n", 1);
	return (0);
}
