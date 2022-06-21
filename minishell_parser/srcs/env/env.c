/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 10:49:50 by lfrederi          #+#    #+#             */
/*   Updated: 2022/06/18 17:25:13 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "ft_string.h"
#include <stdlib.h>

int	ft_clone_env(t_list **envs, char *envp[])
{
	t_list		*node;
	t_env		*env;
	char		*var;
	int			globale;
	int			i;

	i = 0;
	while (envp[i])
	{
		var = ft_strdup(envp[i]);
		if (!var)
			return (ft_clear_env(envs, 0));
		globale = 1;
		if (var[0] == '_')
			globale = 0;
		if (ft_new_env(&env, var, globale) == 0)
			return (ft_clear_env(envs, 0));
		node = ft_lstnew((void *) env);
		if (!node)
			return (ft_clear_env(envs, 0));
		ft_lstadd_back(envs, node);
		i++;
	}
	return (1);
}

t_list	*ft_get_by_name(t_list *env, const char *varname)
{
	int	len;

	len = ft_strlen(varname);
	while (env)
	{
		if (ft_strncmp(((t_env *) env->content)->var, varname, len) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

int	ft_set_value(t_list *envs, const char *varname, const char *value)
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
}
