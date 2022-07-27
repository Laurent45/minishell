/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 10:49:50 by lfrederi          #+#    #+#             */
/*   Updated: 2022/07/17 16:51:52 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "env.h"
#include "ft_string.h"

extern	t_list *envs;

static int	ft_strlenvar(char *var)
{
	int i;

	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	return (i);
}

int	ft_get_envvar(char *varname, char **value)
{
	t_list	*tmp_envs;
	int		lenvarname;
	char	*env_var;

	tmp_envs = envs;
	while (tmp_envs)
	{
		env_var = (char *) ((t_env *) tmp_envs->content)->var;
		lenvarname = ft_strlenvar(env_var);
		if ((int) ft_strlen(varname) > lenvarname)
			lenvarname = ft_strlen(varname);
		if (ft_strncmp(env_var, varname, lenvarname) == 0)
		{
			*value = ft_strdup(env_var + lenvarname + 1);
			if (!(*value))
				return (0);
			return (1);
		}
		tmp_envs = tmp_envs->next;
	}
	*value = (char *) malloc(sizeof(char));
	if (!(*value))
		return (0);
	*value[0] = '\0';
	return (1);
}

/*int	ft_set_value(const char *varname, const char *value)
{
	t_list		*node;
	t_env		*env;
	int			len_var;
	int			len_val;

	node = ft_get_by_name(envs, varname);
	if (!node)
		return (0);
	env = (t_env *) node->content;
	len_var = ft_strlen(varname);
	len_val = ft_strlen(value);
	free(env->var);
	env->var = (char *) malloc(sizeof(char) * (len_var + len_val + 2));
	if (!env->var)
		return (0);
	(env->var)[0] = '\0';
	ft_strlcat(env->var, varname, len_var);
	ft_strlcat(env->var, "=", 1);
	ft_strlcat(env->var, value, len_val);
	return (1);
}*/
