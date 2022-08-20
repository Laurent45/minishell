/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmdargs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 15:59:21 by lfrederi          #+#    #+#             */
/*   Updated: 2022/08/18 19:26:42 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "command.h"
#include "ft_string.h"

#include <stdlib.h>

int	ft_split_expand(char **split_expand, t_list **new_cmdargs)
{
	int		i;
	char	*dup;
	t_list	*node;

	i = 0;
	while (split_expand[i])
	{
		dup = ft_strdup(split_expand[i]);
		if (!dup)
			return (ft_clear_split(split_expand), 0);
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
}

int	ft_expand_cmdargs(t_list **cmd_args)
{
	t_list	*new_cmdargs;
	t_list	*tmp_cmdargs;
	char	*expand;
	char	**split;
	char	sep;

	new_cmdargs = NULL;
	tmp_cmdargs = *cmd_args;
	sep = ' ';
	while (tmp_cmdargs)
	{
		expand = ft_expand_trim((char *) tmp_cmdargs->content);
		if (expand == NULL)
			return (ft_lstclear(&new_cmdargs, &ft_del_str), 0);
		if (new_cmdargs)
			sep = '\0';
		split = ft_split(expand, sep);
		free(expand);
		if (split == NULL || ft_split_expand(split, &new_cmdargs) == 0)
			return (ft_lstclear(&new_cmdargs, &ft_del_str), 0);
		tmp_cmdargs = tmp_cmdargs->next;
	}
	ft_lstclear(cmd_args, &ft_del_str);
	*cmd_args = new_cmdargs;
	return (1);
}
