/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llepiney <llepiney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 14:33:30 by llepiney          #+#    #+#             */
/*   Updated: 2022/07/20 22:40:12 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

#include <stdlib.h>

int	ft_create_tokens(t_list **tokens, char *prompt, int i)
{
	int		state;
	char	*buff;
	int		tmp;

	state = 1;
	buff = NULL;
	while (*prompt)
	{
		while (*prompt && (*prompt == ' ' || *prompt == 9) && state == 1)
			prompt++;
		while (*prompt && *prompt != ' ' && *prompt != 9 && state == 1
			&& unquote_case(&prompt, tokens, &buff, &state)
			&& meta_alloc(is_it(*prompt), &state, &prompt, tokens))
			;
		while (prompt[i] && state == 2)
		{
			tmp = (quote_case(&prompt, tokens, &buff, &state));
			if (tmp == 0)
				break ;
			if (tmp == 2)
				return (free(buff), 0);
		}
	}
	return (free(buff), 1);
}
