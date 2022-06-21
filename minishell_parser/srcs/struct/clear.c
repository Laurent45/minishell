/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 19:10:10 by lfrederi          #+#    #+#             */
/*   Updated: 2022/06/14 19:48:39 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"

int	ft_clear_tokens(t_list **tokens, int ret)
{
	ft_lstclear(tokens, &ft_del_token);
	return (ret);
}

int	ft_clear_commands(t_list **commands, int ret)
{
	ft_lstclear(commands, &ft_del_command);
	return (ret);
}

int	ft_clear_env(t_list **env, int ret)
{
	ft_lstclear(env, &ft_del_env);
	return (ret);
}
