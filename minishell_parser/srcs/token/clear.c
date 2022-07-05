/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 12:30:03 by lfrederi          #+#    #+#             */
/*   Updated: 2022/07/05 12:36:22 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include <stdlib.h>

void	ft_del_token(void *token)
{
	if (((t_token *) token)->word)
		free(((t_token *) token)->word);
	free(token);
}

int	ft_clear_tokens(t_list **tokens, int ret)
{
	ft_lstclear(tokens, &ft_del_token);
	return (ret);
}
