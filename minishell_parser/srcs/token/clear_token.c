/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 09:51:06 by lfrederi          #+#    #+#             */
/*   Updated: 2022/06/07 10:11:35 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "struct.h"
#include <stdlib.h>

void	ft_del_token(void *token)
{
	if (((t_token *) token)->word)
		free(((t_token *) token)->word);
	free(token);
}

int	ft_clear_tokens(t_list **tokens)
{
	ft_lstclear(tokens, &ft_del_token);
	return (0);
}
