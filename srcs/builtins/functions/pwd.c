/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 21:27:07 by lfrederi          #+#    #+#             */
/*   Updated: 2022/07/27 17:05:37 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	ft_pwd(t_list *args)
{
	char	*pwd;

	(void) args;
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		perror("getcwd");
		return (2);
	}
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}
