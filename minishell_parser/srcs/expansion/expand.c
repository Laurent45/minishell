/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rigel <rigel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 14:37:42 by rigel             #+#    #+#             */
/*   Updated: 2022/07/18 17:31:04 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "env.h"
#include "ft_string.h"
#include <stdlib.h>

extern t_list	*envs;
///////////////////////////////////////////////////////////////////////////////
int	is_alphanum(char c)
{
	if (c >= 'a' && c <= 'z')
		return (1);
	if (c >= 'A' && c <= 'Z')
		return (1);
	if (c >= '0' && c <= '9')
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
	if (is_alphanum(c))
		return (is_alphanum(c));
	if (is_meta(c))
		return (is_meta(c));
	return (0);
}
///////////////////////////////////////////////////////////////////////////////
int	is_num(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}


static int	tmp_alloc(char *str, char **new, int anch, int i)
{
	char	*tmp;
	char	*tmp2;

	if (str[i + 1] == '\0')
		tmp = ft_substr(str, (unsigned int)anch, (size_t)(i - anch + 1));
	else
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
	while ((is_alphanum(str[*i]) || str[*i] == '_') && str[*i] != '\0')
		*i = *i + 1;
	var = ft_substr(str, (unsigned int)(*anch), (size_t)(*i - *anch));
	if (!var)
		return (0);
	if (ft_get_envvar(var, &tmp) == 0)
	{
		free(var);
		return (0);
	}
	if (tmp == NULL)
		tmp2 = ft_strjoin(*new, "");
	else
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

static int	quote_case(char *str, int *i, int test)
{
	int	code;

	if (is_it(str[*i]) == S_QUOTE || (is_it(str[*i]) == D_QUOTE && test == 2))
	{
		code = is_it(str[*i]);
		*i = *i + 1;
		while (str[*i] && is_it(str[*i]) != code)
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
		if (is_num(str[*i]))
			return (0);
		else if (!is_alphanum(str[*i]) && str[*i] != '_')
			return (0);
		if (!dollar_alloc(str, new, anch, i))
			return (2);
		return (0);
	}
	return (1);
}

char	*mini_expand(char *str, int test, int i)
{
	int		anch;
	char	*new;

	new = malloc(sizeof(char));
	if (!new)
		return (NULL);
	new[0] = '\0';
	anch = 0;
	while (str[i])
	{
		if (str[i + 1] == '\0')
		{
			if (!tmp_alloc(str, &new, anch, i))
				return (free(new), NULL);
			return (new);
		}
		if (!quote_case(str, &i, test))
			continue ;
		if (!(dollar_case(str, &new, &i, &anch)))
			continue ;
		else if (dollar_case(str, &new, &i, &anch) == 2)
			return (free(new), NULL);
		i++;
	}
	return (new);
}

