/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llepiney <llepiney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 15:33:24 by llepiney          #+#    #+#             */
/*   Updated: 2022/07/21 12:26:15 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include <stdio.h>

int	quote_detect(char *str, int *code)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (is_it(str[i]) == S_QUOTE || is_it(str[i]) == D_QUOTE)
		{
			*code = WORD;
			return (1);
		}
		i++;
	}
	return (0);
}

static int	unquote_case2(char **arg, int *code, int *state, int i)
{
	if ((*arg)[i] == '\'' || (*arg)[i] == '\"')
	{
		*code = is_it((*arg)[i]);
		*state = 2;
		return (0);
	}
	return (1);
}

int	unquote_case(char **arg, t_list **tokens, char **buff, int *state)
{
	int		code;
	int		i;

	i = 0;
	code = is_it((*arg)[i]);
	if (code <= 2)
	{
		while ((*arg)[i] && is_it((*arg)[i]) <= 2
				&& (*arg)[i] != ' ' && (*arg)[i] != 9)
		{
			if (((*arg)[i + 1] == '\0' || (*arg)[i + 1] == ' '
					|| (*arg)[i + 1] == 9 || is_it((*arg)[i + 1]) > 2)
					&& !buff_alloc(arg, buff, &i))
				return (tok_alloc_err(tokens));
			i = i + 1;
			if (!(unquote_case2(arg, &code, state, i)))
				break ;
		}
		if (*state == 1 && !lst_alloc(arg, buff, tokens))
			return (2);
		return (0);
	}
	return (1);
}

int	quote_case2(char **arg, t_list **tokens, char **buff)
{
	int		code;
	int		i;

	i = 0;
	code = is_it(**arg);
	while ((*arg)[i] && ((is_it((*arg)[i]) != code && i != 0) || i == 0))
	{
		if ((*arg)[i + 1] == '\0')
		{
			printf("Open quotes.\n");
			return (tok_alloc_err(tokens));
		}
		else if (is_it((*arg)[i + 1]) == code)
		{
			i++;
			if (!buff_alloc(arg, buff, &i))
				return (tok_alloc_err(tokens));
			break ;
		}
		i++;
	}
	return (1);
}

int	quote_case(char **arg, t_list **tokens, char **buff, int *state)
{
	if (!quote_case2(arg, tokens, buff))
		return (2);
	if (is_it(**arg) <= 4 && **arg != 9 && **arg != ' ' && **arg != '\0')
		*state = 1;
	else
	{
		if (!lst_alloc(arg, buff, tokens))
			return (0);
		*state = 1;
	}
	if (*state == 1)
		return (0);
	return (1);
}
