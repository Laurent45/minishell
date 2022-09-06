/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rigel <rigel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 14:37:42 by rigel             #+#    #+#             */
/*   Updated: 2022/08/30 14:57:47 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "token.h"
#include "env.h"
#include "ft_string.h"
#include "ft_ctype.h"

#include <stdlib.h>

static int	tmp_alloc(char *str, char **new, int anch, int i)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_substr(str, (unsigned int)anch, (size_t)(i - anch));
	if (!tmp)
		return (0);
	tmp2 = ft_strjoin(*new, tmp);
	free(tmp);
	free(*new);
	if (tmp2 == NULL)
		return (0);
	*new = tmp2;
	return (1);
}

static int	dollar_alloc(char *str, char **new, int *anch, int *i)
{
	char	*var;
	char	*tmp;
	char	*tmp2;

	*anch = *i;
	while ((ft_isalnum(str[*i]) || str[*i] == '_' || str[*i] == '?') \
			&& str[*i] != '\0')
		*i = *i + 1;
	var = ft_substr(str, (unsigned int)(*anch), (size_t)(*i - *anch));
	if (!var)
		return (0);
	tmp = ft_getenv_value(var);
	if (tmp == NULL)
		return (free(var), 0);
	tmp2 = ft_strjoin(*new, tmp);
	free(var);
	free(tmp);
	free(*new);
	if (tmp2 == NULL)
		return (0);
	*new = tmp2;
	*anch = *i;
	return (1);
}

static int	quote_expand(char *str, int *i, int isexpand, int *quote)
{
	int	code;

	if (is_it(str[*i]) == D_QUOTE)
	{
		if (*quote)
			*quote = 0;
		else
			*quote = 1;
	}
	if (is_it(str[*i]) == S_QUOTE && isexpand == 0 && *quote == 0)
	{
		code = is_it(str[*i]);
		*i = *i + 1;
		while (str[*i] && is_it(str[*i]) != code)
			*i = *i + 1;
		*i = *i + 1;
		return (0);
	}
	return (1);
}

static int	dollar_case(char *str, char **new, int *i, int *anch)
{
	if (str[*i] == '$')
	{
		if (!tmp_alloc(str, new, *anch, *i))
			return (2);
		*i = *i + 1;
		if (ft_isdigit(str[*i]) || str[*i] == '\0')
			return (0);
		else if (!is_alphanum(str[*i]) && str[*i] != '_')
			return (0);
		if (!dollar_alloc(str, new, anch, i))
			return (2);
		return (0);
	}
	return (1);
}

char	*ft_expand(char *str, int isexpand, int i)
{
	int		anch;
	char	*new;
	int		quote;

	new = malloc(sizeof(char));
	if (!new)
		return (NULL);
	new[0] = '\0';
	anch = 0;
	quote = 0;
	while (str[i])
	{
		if (!quote_expand(str, &i, isexpand, &quote))
			continue ;
		if (!(dollar_case(str, &new, &i, &anch)))
			continue ;
		else if (dollar_case(str, &new, &i, &anch) == 2)
			return (free(new), NULL);
		i++;
	}
	if (!tmp_alloc(str, &new, anch, i))
		return (free(new), NULL);
	return (new);
}
