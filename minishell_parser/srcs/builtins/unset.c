/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llepiney <llepiney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 14:38:15 by llepiney          #+#    #+#             */
/*   Updated: 2022/07/17 11:11:10 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*int	ft_tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int	clone_tab(char **tab1, char **tab2)
{
	int	len;
	int	i;

	i = 0;
	len = ft_tablen(tab1);
	while (i < len)
	{
		tab2[i] = ft_strdup(tab1[i]);
		i++;
	}
	tab2[i] = NULL;
	return (1);
}

int	recreate(char **env, char *to_del)
{
	int		len;
	char	**new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = ft_tablen(env) - 1;
	new = malloc(sizeof(char *) * (len + 1));
	if (!new)
		return (0);
	while (env[i])
	{
		if (ft_strncmp(env[i], to_del, ft_strlen(to_del)))
		{
			new[j] = ft_strdup(env[i]);
			j++;
		}
		i++;
	}
	new[j] = NULL;
	clone_tab(new, env);
	free_tab(new);
	return (1);
}

int	ft_unset(char **env, char *str)
{
	int		i;
	int		j;
	char	*to_del;

	i = 0;
	to_del = ft_strjoin(str, "=");
	while (env[i])
	{
		j = 0;
		while (env[i][j])
		{
			if (!ft_strncmp(env[i], to_del, ft_strlen(to_del)))
			{
				recreate(env, to_del);
				free(to_del);
				return (0);
			}
			else if (env[i][0] == '\0')
			{
				free(to_del);
				return (1);
			}
			j++;
		}
		i++;
	}
	return (1);
}*/

#include "builtins.h"
#include <stdio.h>

int	ft_unset(t_list *args)
{
	(void) args;

	printf("You are in ft_unset\n");
	return (0);
}


