/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rigel <rigel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 14:37:42 by rigel             #+#    #+#             */
/*   Updated: 2022/09/13 10:48:35 by rigel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "token.h"
#include "env.h"
#include "ft_string.h"
#include "ft_ctype.h"
#include "struct.h"

#include <stdlib.h>

static int	tmp_alloc(t_expansion *x, char **new, int i)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_substr(x->str, (unsigned int)(x->anch), (size_t)(i - x->anch));
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

static int	dollar_alloc(t_expansion *x, char **new, int *i, t_list *my_envp)
{
	char	*var;
	char	*tmp;
	char	*tmp2;

	x->anch = *i;
	while ((ft_isalnum(x->str[*i]) || x->str[*i] == '_' || x->str[*i] == '?') \
			&& x->str[*i] != '\0')
		*i = *i + 1;
	var = ft_substr(x->str, (unsigned int)(x->anch), (size_t)(*i - x->anch));
	var = trim_quote(var);
	if (!var)
		return (0);
	tmp = getenv_value(my_envp, var);
	dollar_alloc2(tmp, *new, &tmp2);
	if (ft_strcmp(var, "?") == 0)
		free(tmp);
	free(var);
	free(*new);
	if (tmp2 == NULL)
		return (0);
	*new = tmp2;
	x->anch = *i;
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

static int	dollar_case(t_expansion *x, char **new, int *i, t_list *my_envp)
{
	if (x->str[*i] == '$')
	{
		if (!tmp_alloc(x, new, *i))
			return (2);
		*i = *i + 1;
		if (ft_isdigit(x->str[*i]) || x->str[*i] == '\0')
			return (0);
		else if (!ft_is_alphanum(x->str[*i]) && x->str[*i] != '_'
			&& x->str[*i] != '\'' && x->str[*i] != '\"')
			return (0);
		if (!dollar_alloc(x, new, i, my_envp))
			return (2);
		return (0);
	}
	return (1);
}

char	*expand(t_list *my_envp, char *str, int isexpand, int i)
{
	t_expansion	x;
	char		*new;
	int			quote;

	new = malloc(sizeof(char));
	if (!new)
		return (NULL);
	new[0] = '\0';
	x.anch = 0;
	x.str = str;
	quote = 0;
	while (str[i])
	{
		if (!quote_expand(str, &i, isexpand, &quote))
			continue ;
		if (!(dollar_case(&x, &new, &i, my_envp)))
			continue ;
		else if (dollar_case(&x, &new, &i, my_envp) == 2)
			return (free(new), NULL);
		i++;
	}
	if (!tmp_alloc(&x, &new, i))
		return (free(new), NULL);
	return (new);
}
