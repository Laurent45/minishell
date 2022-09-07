/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 22:42:04 by lfrederi          #+#    #+#             */
/*   Updated: 2022/09/07 11:31:14 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

#include <stdlib.h>

int	ft_is_alphanum(char c)
{
	if (c >= 'a' && c <= 'z')
		return (1);
	if (c >= 'A' && c <= 'Z')
		return (1);
	if (c >= '0' && c <= '9')
		return (1);
	if (is_meta(c) == 0)
		return (1);
	return (0);
}

int	is_meta(char c)
{
	if (c == 34)
		return (D_QUOTE);
	if (c == 39)
		return (S_QUOTE);
	if (c == '<')
		return (LESS);
	if (c == '>')
		return (GREAT);
	if (c == '$')
		return (DOLLAR);
	if (c == '|')
		return (PIPE);
	return (0);
}

int	is_it(char c)
{
	if (ft_is_alphanum(c))
		return (ft_is_alphanum(c));
	if (is_meta(c))
		return (is_meta(c));
	return (0);
}

void	del(void *tok)
{
	free(((t_token *)tok)->str);
	free(tok);
}
