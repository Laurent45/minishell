/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 18:18:46 by lfrederi          #+#    #+#             */
/*   Updated: 2022/07/19 11:08:05 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include <stdlib.h>
#include <unistd.h>
#include "env.h"
#include "ft_string.h"

char **ft_args_to_array(t_list *lst)
{
	int		size;
	int		i;
	char	**ret;

	size = ft_lstsize(lst);
	ret = (char **) malloc(sizeof(char *) * (size + 1));
	if (!ret)
		return (NULL);
	i = 0;
	while (i < size)
	{
		ret[i] = (char *) lst->content;
		lst = lst->next;
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

char **ft_envs_to_array(t_list *lst)
{
	t_env	*env;
	int		size;
	int		i;
	char	**ret;

	size = ft_lstsize(lst);
	ret = (char **) malloc(sizeof(char *) * (size + 1));
	if (!ret)
		return (NULL);
	i = 0;
	while (i < size)
	{
		env = (t_env *) lst->content;
		ret[i] = env->var;
		lst = lst->next;
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

int	ft_search_exe(t_list *cmd)
{
	char	*path;
	char	*tmp;
	char	**split;
	int		i;

	if (ft_strchr((char *) cmd->content, '/') == 0)
	{
		if (ft_get_envvar("PATH", &path) == 0)
			return (127);
		split = ft_split(path, ':');
		free(path);
		if (split == NULL)
			return (127);
		i = 0;
		while (split[i])
		{
			tmp = ft_strjoin(split[i], "/");
			path = ft_strjoin(tmp, (char *) cmd->content);
			if (access(path, X_OK) == 0)
			{
				free((char *) cmd->content);
				cmd->content = path;
				return (1);
			}
			i++;
		}
	}
	return (1);
}
