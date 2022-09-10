/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_exe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 15:49:58 by lfrederi          #+#    #+#             */
/*   Updated: 2022/09/10 16:09:01 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "env.h"
#include "ft_string.h"
#include "ft_stdio.h"
#include "init.h"

#include <stdlib.h>
#include <unistd.h>

static void	cmd_not_found(char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
	set_status(127);
}

static int	add_path(char **path, t_list *cmd)
{
	int		i;
	char	*tmp;
	char	*path_exe;

	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		if (!tmp)
			return (cmd_not_found((char *) cmd->content), FAILED);
		path_exe = ft_strjoin(tmp, (char *) cmd->content);
		free(tmp);
		if (!path_exe)
			return (cmd_not_found((char *) cmd->content), FAILED);
		if (access(path_exe, F_OK) == 0)
		{
			free(cmd->content);
			cmd->content = path_exe;
			return (SUCCESS);
		}
		free(path_exe);
		i++;
	}
	return (cmd_not_found((char *) cmd->content), FAILED);
}

int	search_exe(t_list *cmd, t_list *my_envp)
{
	char	*path;
	char	**split;
	int		ret;

	if (ft_strcmp((char *) cmd->content, "") == 0)
		return (cmd_not_found((char *) cmd->content), FAILED);
	if (ft_strchr((char *) cmd->content, '/') == 0)
	{
		path = getenv_value(my_envp, "PATH");
		if (!path || path[0] == '\0')
			return (SUCCESS);
		split = ft_split(path, ':');
		if (split == NULL)
			return (cmd_not_found((char *) cmd->content), FAILED);
		ret = add_path(split, cmd);
		ft_clear_split(split);
		return (ret);
	}
	return (SUCCESS);
}
