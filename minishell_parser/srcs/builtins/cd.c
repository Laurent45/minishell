/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 22:40:09 by lfrederi          #+#    #+#             */
/*   Updated: 2022/07/17 12:12:56 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "builtins.h"
#include "env.h"
#include "ft_string.h"
#include "ft_stdio.h"

extern t_list *envs;

char	*ft_home()
{
	int	i;
	t_list	*env;

	env = envs;
	i = 0;
	while (env)
	{
		if (ft_strncmp("HOME", ((t_env *) env->content)->var, 4) == 0)
		{
			while ((((t_env *) env->content)->var)[i] != '=')
				i++;
			return (((t_env *) env->content)->var + i + 1);
		}
		env = env->next;
	}
	ft_putstr_fd("cd: HOME not set\n", 2);
	return (NULL);
}

/*static int	ft_set_pwd(t_list *env, char *pwd)
{

}*/

//TODO: put error message
int	ft_cd(t_list *args)
{
	char	*dir;
	//char	*pwd_curr;
	int		lenargs;

	//pwd_curr = getcwd(NULL, 0);
	lenargs = ft_lstsize(args);
	if (lenargs > 1)
		ft_putstr_fd("cd: too many arguments\n", 2);
	else
	{
		if (lenargs == 0)
			dir = ft_home();
		else
			dir = (char *) args->content;
		if (chdir(dir) != 0)
			perror("chdir");
		/*else
		{
			ft_set_pwd(env, "PWD", getcwd(NULL));
			ft_set_value(env, "PWD");
		}*/
	}
	return (1);
}
