/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 09:25:57 by lfrederi          #+#    #+#             */
/*   Updated: 2022/07/17 12:51:53 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "env.h"
#include "ft_string.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern t_list *envs;

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
	t_list		*tmp_envs;
	t_list		*curr;
	t_env	*env_var;

	tmp_envs = envs;
	while (tmp_envs)
	{
		env_var = (t_env *) tmp_envs->content;
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
		tmp_envs = tmp_envs->next;
	}
	if (*lst)
		ft_sort(*lst);
	return (1);
}

static int	ft_print_env(t_list *lst)
{
	int		n_print;
	int		i;
	int		j;

	n_print = 0;
	while (lst)
	{
		i = 0;
		while (((char *) lst->content)[i] != '=')
			i++;
		i++;
		write(1, "declare -x ", 11);
		write(1, lst->content, i);
		write(1, "\"", 1);
		j = i;
		while (((char *) lst->content)[j])
			j++;
		write(1, lst->content + i, j - i);
		write(1, "\"\n", 2);
		n_print++;
		lst = lst->next;
	}
	return (n_print);
}

int	ft_export(t_list *args)
{
	(void) args;
	int		size;
	int		n_print;
	char	c;
	t_list	*lst;

	lst = NULL;
	n_print = 0;
	c = 'A';
	size = ft_lstsize(envs);
	while (c <= 'z')
	{
		if (ft_curr_lst(c, &lst) == 0)
			return (0);
		if (lst)
		{
			n_print += ft_print_env(lst);
			ft_lstclear(&lst, NULL);
			if (n_print == size)
				break ;
		}
		c++;
	}
	return (1);
}
