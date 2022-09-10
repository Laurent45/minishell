/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 22:40:09 by lfrederi          #+#    #+#             */
/*   Updated: 2022/09/10 15:08:27 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "env.h"
#include "ft_string.h"
#include "error.h"
#include "init.h"

#include <unistd.h>
#include <stdlib.h>

static char	*home(t_list *my_envp)
{
	t_env	*env_var;

	while (my_envp)
	{
		env_var = (t_env *) my_envp->content;
		if (ft_strncmp("HOME", env_var->varname, 4) == 0)
			return (env_var->value);
		my_envp = my_envp->next;
	}
	return (NULL);
}

static int set_env_pwd(t_list **my_envp, char *oldpwd)
{
	char	*pwd;
	char	*env_oldpwd;
	char	*env_pwd;

	pwd = getcwd(NULL, 0);
	if (!oldpwd || !pwd)
		return (free(oldpwd), free(pwd), FAILED);
	env_oldpwd = ft_strjoin("OLDPWD=", oldpwd);
	env_pwd = ft_strjoin("PWD=", pwd);
	free(oldpwd);
	free(pwd);
	if (!env_oldpwd || !env_pwd)
		return (free(env_oldpwd), free(env_pwd), FAILED);
	if (add_envvar(my_envp, env_oldpwd, 1) == FAILED\
		|| add_envvar(my_envp, env_pwd, 1) == FAILED)
		return (free(env_oldpwd), free(env_pwd), FAILED);
	return (free(env_oldpwd), free(env_pwd), SUCCESS);
}

int	built_cd(t_list *args, t_list **my_envp)
{
	char	*dir;
	int		lenargs;
	char	*oldpwd;

	oldpwd = getcwd(NULL, 0);
	lenargs = ft_lstsize(args);
	if (lenargs > 2)
		return (set_status(2), free(oldpwd),\
				puterror(FAILED, "cd: too many arguments"));
	if (lenargs == 1 || ft_strcmp((char *) args->next->content, "~") == 0)
	{
		dir = home(*my_envp);
		if (dir == NULL)
			return (free(oldpwd),\
					set_status(2), puterror(FAILED, "cd: HOME not set"));
	}
	else
		dir = (char *) args->next->content;
	if (chdir(dir) != 0)
		return (free(oldpwd), set_status(2), ft_perror(FAILED, "chdir"));
	if (set_env_pwd(my_envp, oldpwd) == FAILED)
		return (set_status(2), FAILED);
	return (set_status(0), SUCCESS);
}
