/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 11:29:16 by lfrederi          #+#    #+#             */
/*   Updated: 2022/07/15 15:21:59 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# define S_QUOTE	1
# define D_QUOTE	2
# define DOLLAR		3
# define OTHER		4

extern t_list *envs;

int	ft_code_char(char c)
{
	if (c == '\'')
		return (S_QUOTE);
	if (c == '\"')
		return (D_QUOTE);
	if (c == '$')
		return (DOLLAR);
	return (OTHER);
}

char	*ft_join_char(char *tojoin, char *word, int start, int end)
{
	char	*substr;
	char	*join_result;

	substr = ft_substr(word, start, end);
	if (!substr)
		return (NULL);
	join_result = ft_strjoin(tojoin, substr);
	if (!join_result)
		return (NULL);
	free(tojoin);
	free(substr);
	return (join_result);
}

char	*ft_join_dollar(char *tojoin, char *word, int start)
{
	int i;

	i = start + 1;
	if (word[i] != '_' && ft_isalpha(word[i]))
	{
		if (ft_isdigit(word[i]))
			return (ft_strjoin(tojoin, ""));
		else
			return (ft_strjoin(tojoin, "$"));
	}
	i++;
	while (word[i])
	{
		i++;
	}
}

//TODO: Check leaks
char	*ft_expand(char *word)
{
	int		i;
	int		r;
	char	*substr = NULL;
	char	*result = NULL;
	char	*tmp = NULL;
	int		code;

	i = 0;
	r = 0;
	result = (char *) malloc(sizeof(char));
	if (result)
		return (NULL);
	result[0] = '\0';
	while (word[i])
	{
		code = ft_code_char(word[i]);
		if (code != OTHER)
		{
			if (r < i)
			{
				substr = ft_substr(word, r, i - r);
				if (substr == NULL)
					return (NULL);
				tmp = ft_strjoin(result, substr);
				free(result);
				free(substr);
				if (tmp == NULL)
					return (NULL);
				else
					result = tmp;
				r = i;
			}
			if (code == DOLLAR)
			{
				while (word[i] && word[i] != ' ')
					i++;
				if (ft_getenv(varname, &substr) == 0)
					return (NULL);
				tmp = ft_strjoin(result, substr);
				free(substr);
				free(result);
				if (tmp != NULL)
					return (NULL);
				else
					result = tmp;
			}
			if (code == D_QUOTE)
			{
			}
		}
		i++;
	}

}
