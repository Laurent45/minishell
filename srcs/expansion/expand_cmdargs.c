/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmdargs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 15:59:21 by lfrederi          #+#    #+#             */
/*   Updated: 2022/09/10 11:20:38 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "command.h"
#include "ft_string.h"

#include <stdlib.h>

static int	split_expand(char *expand, t_list **new_cmdargs)
{
	int		i;
	t_list	*node;
	char	**split_expand;
	char	*trim;

	split_expand = ft_split(expand, ' ');
	free(expand);
	if (!split_expand)
		return (FAILED);
	if (split_expand[0] == NULL)
		return (free(split_expand), SUCCESS);
	i = 0;
	while (split_expand[i])
	{
		trim = trim_quote(split_expand[i]);
		if (!trim)
			return (ft_clear_split(split_expand), FAILED);
		node = ft_lstnew(trim);
		if (node == NULL)
			return (free(trim), ft_clear_split(split_expand), FAILED);
		ft_lstadd_back(new_cmdargs, node);
		i++;
	}
	return (free(split_expand), SUCCESS);
}

static int	add_expand(char *arg, t_list **new_cmdargs, int to_split)
{
	t_list	*node;
	char	*trim;

	if (to_split)
		return (split_expand(arg, new_cmdargs));
	trim = trim_quote(arg);
	if (!trim)
		return (FAILED);
	node = ft_lstnew(trim);
	if (node == NULL)
		return (FAILED);
	ft_lstadd_back(new_cmdargs, node);
	return (SUCCESS);
}

int	expand_cmdargs(t_list **cmd_args, t_list *my_envp)
{
	t_list	*new_cmdargs;
	t_list	*tmp_cmdargs;
	int		to_split;
	char	*ret_exp;

	new_cmdargs = NULL;
	tmp_cmdargs = *cmd_args;
	to_split = 0;
	while (tmp_cmdargs)
	{
		ret_exp = expand(my_envp, (char *) tmp_cmdargs->content, 0, 0);
		if (ret_exp == NULL)
			return (ft_lstclear(&new_cmdargs, &del_str), FAILED);
		if (ft_strcmp(ret_exp, (char *) tmp_cmdargs->content) != 0)
			to_split = 1;
		if (add_expand(ret_exp, &new_cmdargs, to_split) == FAILED)
			return (ft_lstclear(&new_cmdargs, &del_str), FAILED);
		tmp_cmdargs = tmp_cmdargs->next;
	}
	ft_lstclear(cmd_args, &del_str);
	*cmd_args = new_cmdargs;
	return (SUCCESS);
}
