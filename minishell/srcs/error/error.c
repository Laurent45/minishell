/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 15:15:45 by lfrederi          #+#    #+#             */
/*   Updated: 2022/07/30 19:54:21 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_stdio.h"

int	ft_puterror(int ret, char *message)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	return (ret);
}

int	ft_perror(int ret, char *message)
{
	ft_putstr_fd("minishell: ", 2);
	perror(message);
	return (ret);
}
