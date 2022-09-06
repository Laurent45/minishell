/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 22:40:09 by lfrederi          #+#    #+#             */
/*   Updated: 2022/07/27 16:59:54 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "env.h"
#include "ft_string.h"
#include "error.h"

#include <unistd.h>
#include <stdlib.h>

extern t_list	*g_envs;

static char	*ft_home(void)
{
	int		i;
	t_list	*envs;

	envs = g_envs;
	i = 0;
	while (envs)
	{
		if (ft_strncmp("HOME", ((t_env *) envs->content)->var, 4) == 0)
		{
			while ((((t_env *) envs->content)->var)[i] != '=')
				i++;
			return (((t_env *) envs->content)->var + i + 1);
		}
		envs = envs->next;
	}
	return (NULL);
}

int	ft_cd(t_list *args)
{
	char	*dir;
	int		lenargs;

	lenargs = ft_lstsize(args);
	if (lenargs > 2)
		return (ft_puterror(2, "cd: too many arguments"));
	if (lenargs == 1 || ft_strcmp((char *) args->next->content, "~") == 0)
	{
		dir = ft_home();
		if (dir == NULL)
			return (ft_puterror(2, "cd: HOME not set"));
	}
	else
		dir = (char *) args->next->content;
	if (chdir(dir) != 0)
		return (ft_perror(2, "chdir"));
	return (0);
}
