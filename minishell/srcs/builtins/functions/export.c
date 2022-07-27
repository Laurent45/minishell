/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 09:25:57 by lfrederi          #+#    #+#             */
/*   Updated: 2022/07/27 17:03:26 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "env.h"
#include "ft_string.h"
#include "ft_ctype.h"
#include "error.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern t_list	*g_envs;

static void	ft_sort(t_list *l)
{
	t_list	*begin;
	void	*tmp;
	int		size;
	int		i;

	begin = l;
	size = ft_lstsize(l);
	while (size > 1)
	{
		i = 0;
		l = begin;
		while (i < size - 1)
		{
			if (ft_strcmp((char *) l->content, (char *) l->next->content) < 0)
			{
				tmp = l->content;
				l->content = l->next->content;
				l->next->content = tmp;
			}
			i++;
			l = l->next;
		}
		size--;
	}
}

static int	ft_curr_lst(char r, t_list **lst)
{
	t_list		*envs;
	t_list		*curr;
	t_env		*env_var;

	envs = g_envs;
	while (envs)
	{
		env_var = (t_env *) envs->content;
		if ((env_var->var)[0] == r && env_var->globale)
		{
			curr = ft_lstnew(env_var->var);
			if (!curr)
			{
				ft_lstclear(lst, NULL);
				return (0);
			}
			ft_lstadd_back(lst, curr);
		}
		envs = envs->next;
	}
	if (*lst)
		ft_sort(*lst);
	return (1);
}

static void	ft_print_env(t_list *lst)
{
	int		i;
	int		j;

	while (lst)
	{
		i = 0;
		while (((char *) lst->content)[i] != '=' && ((char *) lst->content)[i])
			i++;
		write(1, "declare -x ", 11);
		write(1, lst->content, i + 1);
		if (((char *) lst->content)[i])
		{
			write(1, "\"", 1);
			j = ++i;
			while (((char *) lst->content)[j])
				j++;
			write(1, lst->content + i, j - i);
			write(1, "\"", 1);
		}
		write(1, "\n", 1);
		lst = lst->next;
	}
}

static int	ft_export_envvar(t_list *envvar)
{
	char	*curr_envvar;

	while (envvar)
	{
		curr_envvar = (char *) envvar->content;
		if (curr_envvar[0] != '_' && ft_isalpha(curr_envvar[0]) == 0)
			ft_puterror(2, "export: not a valid identifier");
		else
			if (ft_add_envvar(curr_envvar, 1) == 0)
				ft_puterror(2, "export failed");
		envvar = envvar->next;
	}
	return (0);
}

int	ft_export(t_list *args)
{
	char	c;
	t_list	*lst;

	if (ft_lstsize(args) > 1)
		return (ft_export_envvar(args->next));
	lst = NULL;
	c = 'A';
	while (c <= 'z')
	{
		if (ft_curr_lst(c, &lst) == 0)
			return (0);
		if (lst)
		{
			ft_print_env(lst);
			ft_lstclear(&lst, NULL);
		}
		c++;
	}
	return (0);
}
