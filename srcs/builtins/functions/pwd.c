/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 21:27:07 by lfrederi          #+#    #+#             */
/*   Updated: 2022/09/12 22:13:09 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "init.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	built_pwd(t_list *args, t_list **my_envp)
{
	char	*pwd;

	(void) my_envp;
	(void) args;
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		perror("getcwd");
		return (set_status(2), FAILED);
	}
	printf("%s\n", pwd);
	free(pwd);
	return (set_status(0), SUCCESS);
}
