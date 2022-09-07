/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llepiney <llepiney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 21:01:11 by llepiney          #+#    #+#             */
/*   Updated: 2022/09/07 10:59:53 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "ft_lst.h"
#include "ft_mem.h"
#include "ft_string.h"

#include <stdio.h>
#include <stdlib.h>

int	tok_alloc_err(t_list **tokens)
{
	ft_lstclear(tokens, &del);
	printf("Token allocation error.\n");
	return (0);
}

int	tok_alloc(t_token **tok, char *str, int code)
{
	*tok = (t_token *) malloc(sizeof(t_token));
	if (!(*tok))
		return (0);
	quote_detect(str, &code);
	(*tok)->str = str;
	(*tok)->code = code;
	return (1);
}

int	buff_alloc(char **arg, char **buff, int *i)
{
	char	*str1;
	char	*str2;

	str1 = (char *) malloc(sizeof(char) * ((*i) + 2));
	if (!str1)
		return (0);
	ft_memcpy(str1, *arg, ((*i) + 1));
	str1[(*i) + 1] = '\0';
	if (*buff)
		str2 = ft_strjoin(*buff, str1);
	else
		str2 = ft_strdup(str1);
	free(*buff);
	free(str1);
	*buff = str2;
	*arg = *arg + ((*i) + 1);
	*i = -1;
	return (1);
}

int	lst_alloc(char **arg, char **buff, t_list **tokens)
{
	int		code;
	t_token	*tok;
	t_list	*lst1;

	*arg = *arg - 1;
	code = is_it((*arg)[0]);
	if (code == DOLLAR)
		code = WORD;
	if ((code == LESS && is_it((*arg)[1]) == LESS)
			|| (code == GREAT && is_it((*arg)[1]) == GREAT))
	{
		code += 2;
		*arg = *arg + 1;
	}
	*arg = *arg + 1;
	if (!(tok_alloc(&tok, *buff, code)))
		return (tok_alloc_err(tokens));
	lst1 = ft_lstnew(tok);
	if (!lst1)
		return (free(tok), tok_alloc_err(tokens));
	ft_lstadd_back(tokens, lst1);
	*buff = NULL;
	return (1);
}

int	meta_alloc(int code, int *state, char **arg, t_list **tokens)
{
	char	*buff;
	int		i;

	i = 0;
	buff = NULL;
	if (code == D_QUOTE || code == S_QUOTE)
	{
		*state = 2;
		return (0);
	}
	else if (code > 4)
	{
		if (!buff_alloc(arg, &buff, &i))
			return (0);
		if (!lst_alloc(arg, &buff, tokens))
			return (0);
	}
	return (1);
}
