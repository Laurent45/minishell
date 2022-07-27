/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */

/*                                                    +:+ +:+         +:+     */
/*   By: llepiney <llepiney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 21:21:07 by llepiney          #+#    #+#             */
/*   Updated: 2022/05/30 09:51:54 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "ft_stdio.h"
#include <unistd.h>
#include <stdio.h>

int	ft_env(t_list *args)
{
	(void) args;

	/*while (v_env)
	{
		ft_putstr_fd((char *) v_env->content, 1);
		write(1, "\n", 1);
		v_env = v_env->next;
	}
	while (v_shell)
	{
		ft_putstr_fd((char *) v_shell->content, 1);
		write(1, "\n", 1);
		v_shell = v_shell->next;
	}*/
	printf("ft_env\n");
	return (1);
}
