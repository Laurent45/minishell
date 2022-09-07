/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 21:27:07 by lfrederi          #+#    #+#             */
/*   Updated: 2022/09/07 22:31:36 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern int	g_exit_status;

int	built_pwd(t_list *args, t_list **my_envp)
{
	(void) my_envp;
	(void) args;

	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		perror("getcwd");
		g_exit_status = 2;
		return (0);
	}
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}
