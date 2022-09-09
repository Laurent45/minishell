/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 09:25:57 by lfrederi          #+#    #+#             */
/*   Updated: 2022/09/08 21:41:04 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "env.h"
#include "ft_string.h"
#include "ft_ctype.h"
#include "error.h"
#include "init.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void	sort(t_list *l)
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

static int	curr_lst(t_list *my_envp, char r, t_list **lst)
{
	t_list		*curr;
	t_env		*env_var;

	while (my_envp)
	{
		env_var = (t_env *) my_envp->content;
		if ((env_var->var)[0] == r && env_var->globale)
		{
			curr = ft_lstnew(env_var->var);
			if (!curr)
			{
				ft_lstclear(lst, NULL);
				return (FAILED);
			}
			ft_lstadd_back(lst, curr);
		}
		my_envp = my_envp->next;
	}
	if (*lst)
		sort(*lst);
	return (SUCCESS);
}

static void	print_env(t_list *lst)
{
	int		i;
	int		j;

	while (lst)
	{
		i = 0;
		while (((char *) lst->content)[i] != '=' && ((char *) lst->content)[i])
			i++;
		write(1, "export ", 7);
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

static int	export_envvar(t_list **my_envp, t_list *envvar)
{
	char	*curr_envvar;
	int		status;

	status = 0;
	while (envvar)
	{
		curr_envvar = (char *) envvar->content;
		if (curr_envvar[0] != '_' && ft_isalpha(curr_envvar[0]) == 0)
			 status = puterror(2, "export: not a valid identifier");
		else
			if (add_envvar(my_envp, curr_envvar, 1) == FAILED)
				status = puterror(2, "export failed");
		envvar = envvar->next;
	}
	return (set_status(status), SUCCESS);
}

int	built_export(t_list *args, t_list **my_envp)
{
	char	c;
	t_list	*lst;

	if (ft_lstsize(args) > 1)
		return (export_envvar(my_envp, args->next));
	lst = NULL;
	c = 'A';
	while (c <= 'z')
	{
		if (curr_lst(*my_envp, c, &lst) == FAILED)
			return (FAILED);
		if (lst)
		{
			print_env(lst);
			ft_lstclear(&lst, NULL);
		}
		c++;
	}
	return (SUCCESS);
}
