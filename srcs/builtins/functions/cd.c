/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 22:40:09 by lfrederi          #+#    #+#             */
/*   Updated: 2022/09/07 22:29:12 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "env.h"
#include "ft_string.h"
#include "error.h"

#include <unistd.h>
#include <stdlib.h>

static char	*home(t_list *my_envp)
{
	int		i;

	i = 0;
	while (my_envp)
	{
		if (ft_strncmp("HOME", ((t_env *) my_envp->content)->var, 4) == 0)
		{
			while ((((t_env *) my_envp->content)->var)[i] != '=')
				i++;
			return (((t_env *) my_envp->content)->var + i + 1);
		}
		my_envp = my_envp->next;
	}
	return (NULL);
}

int	built_cd(t_list *args, t_list **my_envp)
{
	char	*dir;
	int		lenargs;

	lenargs = ft_lstsize(args);
	if (lenargs > 2)
		return (puterror(2, "cd: too many arguments"));
	if (lenargs == 1 || ft_strcmp((char *) args->next->content, "~") == 0)
	{
		dir = home(*my_envp);
		if (dir == NULL)
			return (puterror(2, "cd: HOME not set"));
	}
	else
		dir = (char *) args->next->content;
	if (chdir(dir) != 0)
		return (ft_perror(2, "chdir"));
	return (0);
}
