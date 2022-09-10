/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rigel <rigel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:45:42 by rigel             #+#    #+#             */
/*   Updated: 2022/09/10 11:04:31 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "token.h"

#include <stdlib.h>

static int	trim_count(char *str)
{
	int	i;
	int	code;
	int	count;

	i = 0;
	code = 0;
	count = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '\"')
			&& (code == 0 || code == is_it(str[i])))
		{
			if (code == 0)
				code = is_it(str[i]);
			else if (code == is_it(str[i]))
				code = 0;
			count--;
		}
		count++;
		i++;
	}
	return (count);
}

static int	trim_quote2(char *str, int *i, int *code)
{
	if ((str[*i] == '\'' || str[*i] == '\"')
		&& (*code == 0 || *code == is_it(str[*i])))
	{
		if (*code == 0)
			*code = is_it(str[*i]);
		else if (*code == is_it(str[*i]))
			*code = 0;
		*i = *i + 1;
		return (0);
	}
	return (1);
}

char	*trim_quote(char *str)
{
	int		i;
	int		j;
	int		code;
	char	*new;

	i = 0;
	j = 0;
	code = 0;
	new = malloc(sizeof(char) * (trim_count(str) + 1));
	if (!new)
	{
		free(str);
		str = NULL;
		return (NULL);
	}
	while (str[i])
	{
		if (!trim_quote2(str, &i, &code))
			continue ;
		new[j] = str[i];
		i++;
		j++;
	}
	new[j] = '\0';
	return (free(str), new);
}
