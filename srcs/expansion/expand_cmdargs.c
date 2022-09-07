/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmdargs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 15:59:21 by lfrederi          #+#    #+#             */
/*   Updated: 2022/09/07 23:13:56 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "command.h"
#include "ft_string.h"

#include <stdlib.h>

/*static int	split_expand(char *expand, t_list **new_cmdargs)
{
	int		i;
	char	*dup;
	t_list	*node;
	char	**split_expand;

	split_expand = ft_split(expand, ' ');
	if (!split_expand)
		return (0);
	i = 0;
	while (split_expand[i])
	{
		dup = ft_strdup(split_expand[i]);
		if (!dup)
			return (clear_split(split_expand), 0);
		node = ft_lstnew(dup);
		if (node == NULL)
		{
			free(dup);
			return (ft_clear_split(split_expand), 0);
		}
		ft_lstadd_back(new_cmdargs, node);
		i++;
	}
	return (ft_clear_split(split_expand), 1);
}*/

static int	add_expand(char *arg, t_list **new_cmdargs)
{
	t_list	*node;

	node = ft_lstnew(arg);
	if (node == NULL)
		return (FAILED);
	ft_lstadd_back(new_cmdargs, node);
	return (SUCCESS);
}

int	expand_cmdargs(t_list **cmd_args, t_list *my_envp)
{
	t_list	*new_cmdargs;
	t_list	*tmp_cmdargs;
	char	*ret_exp;

	new_cmdargs = NULL;
	tmp_cmdargs = *cmd_args;
	while (tmp_cmdargs)
	{
		ret_exp = expand_trim((char *) tmp_cmdargs->content, my_envp);
		if (ret_exp == NULL)
			return (ft_lstclear(&new_cmdargs, &del_str), FAILED);
		// TODO: split or not
		/*if (new_cmdargs == NULL)
		{
			if (split_expand(expand, &new_cmdargs) == 0)
				return (lstclear(&new_cmdargs, &del_str), 0);
			free(expand);
		}
		else*/
		if (add_expand(ret_exp, &new_cmdargs) == FAILED)
			return (free(ret_exp), ft_lstclear(&new_cmdargs, &del_str), FAILED);
		tmp_cmdargs = tmp_cmdargs->next;
	}
	ft_lstclear(cmd_args, &del_str);
	*cmd_args = new_cmdargs;
	return (SUCCESS);
}
