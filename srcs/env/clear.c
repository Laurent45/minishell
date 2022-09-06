/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 19:10:10 by lfrederi          #+#    #+#             */
/*   Updated: 2022/07/22 16:03:12 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include <stdlib.h>

void	ft_del_env(void	*content)
{
	free(((t_env *) content)->var);
	free(content);
}

int	ft_clear_env(t_list **env, int ret)
{
	ft_lstclear(env, &ft_del_env);
	return (ret);
}
