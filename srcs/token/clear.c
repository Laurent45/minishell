/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 23:16:52 by lfrederi          #+#    #+#             */
/*   Updated: 2022/07/20 23:18:04 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

int	ft_clear_tokens(t_list **tokens, int ret)
{
	ft_lstclear(tokens, &ft_del);
	return (ret);
}
