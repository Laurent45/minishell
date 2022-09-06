/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_exe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 15:49:58 by lfrederi          #+#    #+#             */
/*   Updated: 2022/08/30 09:37:18 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "env.h"
#include "ft_string.h"
#include "ft_stdio.h"

#include <stdlib.h>
#include <unistd.h>

static int	ft_cmd_not_found(int ret, char *cmd)
{
	if (ret == 127)
		ft_putstr_fd("command not found: ", 2);
	if (ret == 126)
		ft_putstr_fd("command not executable: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd("\n", 2);
	return (ret);
}

static int	ft_access(char *path_exe, t_list *cmd)
{
	if (access(path_exe, F_OK) == 0)
	{
		if (access(path_exe, X_OK) == 0)
		{
			free(cmd->content);
			cmd->content = path_exe;
			return (0);
		}
		free(path_exe);
		return (ft_cmd_not_found(126, (char *) cmd->content));
	}
	free(path_exe);
	return (1);
}

static int	ft_add_path(char **path, t_list *cmd)
{
	int		i;
	int		ret;
	char	*tmp;
	char	*path_exe;

	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		if (!tmp)
			return (ft_cmd_not_found(127, (char *) cmd->content));
		path_exe = ft_strjoin(tmp, (char *) cmd->content);
		free(tmp);
		if (!path_exe)
			return (ft_cmd_not_found(127, (char *) cmd->content));
		ret = ft_access(path_exe, cmd);
		if (ret != 1)
			return (ret);
		i++;
	}
	return (ft_cmd_not_found(127, (char *) cmd->content));
}

int	ft_search_exe(t_list *cmd)
{
	char	*path;
	char	**split;
	int		ret;

	if (cmd == NULL)
		return (0);
	if (ft_strchr((char *) cmd->content, '/') == 0)
	{
		path = ft_getenv_value("PATH");
		if (!path || path[0] == '\0')
			return (free(path), ft_cmd_not_found(127, (char *) cmd->content));
		split = ft_split(path, ':');
		free(path);
		if (split == NULL)
			return (ft_cmd_not_found(127, (char *) cmd->content));
		ret = ft_add_path(split, cmd);
		ft_clear_split(split);
		return (ret);
	}
	if (access((char *) cmd->content, F_OK) == 0 \
			&& access((char *) cmd->content, X_OK) != 0)
		return (ft_cmd_not_found(126, (char *) cmd->content));
	return (0);
}
