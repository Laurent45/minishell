/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 19:10:10 by lfrederi          #+#    #+#             */
/*   Updated: 2022/09/07 11:00:10 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include <stdlib.h>

void	del_env(void	*content)
{
	free(((t_env *) content)->var);
	free(content);
}

int	clear_env(t_list **env, int ret)
{
	ft_lstclear(env, &del_env);
	return (ret);
}
