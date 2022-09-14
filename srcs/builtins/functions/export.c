/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 09:25:57 by lfrederi          #+#    #+#             */
/*   Updated: 2022/09/13 12:24:04 by lfrederi         ###   ########.fr       */
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
		if ((env_var->varname)[0] == r && env_var->globale)
		{
			curr = ft_lstnew(env_var);
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
	t_env	*env_var;

	while (lst)
	{
		env_var = (t_env *) lst->content;
		if (env_var->value != NULL)
			printf("export %s=\"%s\"\n", env_var->varname, env_var->value);
		else
			printf("export %s\n", env_var->varname);
		lst = lst->next;
	}
}

static int	export_envvar(t_list **my_envp, t_list *args)
{
	char	*add_args;
	int		status;

	status = 0;
	while (args)
	{
		add_args = (char *) args->content;
		if (add_args[0] != '_' && ft_isalpha(add_args[0]) == 0)
			status = puterror(2, "export: not a valid identifier");
		else
			if (add_envvar(my_envp, add_args, 1) == FAILED)
				status = puterror(2, "export failed");
		args = args->next;
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
