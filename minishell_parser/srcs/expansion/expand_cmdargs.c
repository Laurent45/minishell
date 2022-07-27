/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmdargs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 15:59:21 by lfrederi          #+#    #+#             */
/*   Updated: 2022/07/19 11:11:08 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "ft_string.h"
#include <stdlib.h>

int	ft_expand_cmdargs(t_list **cmd_args)
{
	t_list	*new_cmdargs;
	t_list	*tmp_cmdargs;
	t_list	*node;
	char	*expand;
	char	*dup;
	char	**split;
	int		i;

	new_cmdargs = NULL;
	tmp_cmdargs = *cmd_args;
	while (tmp_cmdargs)
	{
		expand = mini_expand((char *) tmp_cmdargs->content, 1, 0);
		if (expand == NULL)
		{
			ft_lstclear(&new_cmdargs, &ft_del_str);
			return (0);
		}
		expand = trim_quote(expand);
		if (expand == NULL)
		{
			ft_lstclear(&new_cmdargs, &ft_del_str);
			return (0);
		}
		split = ft_split(expand, ' ');
		if (split == NULL)
		{
			free(expand);
			ft_lstclear(&new_cmdargs, &ft_del_str);
		}
		i = 0;
		while (split[i])
		{
			dup = ft_strdup(split[i]);
			if (!dup)
			{
				ft_clear_split(split);
				ft_lstclear(&new_cmdargs, &ft_del_str);
				return (0);
			}
			node = ft_lstnew(dup);
			if (node == NULL)
			{
				ft_clear_split(split);
				ft_lstclear(&new_cmdargs, &ft_del_str);
				return (0);
			}
			ft_lstadd_back(&new_cmdargs, node);
			i++;
		}
		tmp_cmdargs = tmp_cmdargs->next;
	}
	ft_lstclear(cmd_args, &ft_del_str);
	*cmd_args = new_cmdargs;
	return (1);
}
