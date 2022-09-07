/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 17:14:02 by lfrederi          #+#    #+#             */
/*   Updated: 2022/09/07 23:03:47 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "error.h"
#include "ft_string.h"
#include "expansion.h"

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

static int	heredoc(t_redir *redir)
{
	int		fd;
	t_list	*hdoc;

	unlink("/tmp/_heredoc-minishell");
	fd = open("/tmp/_heredoc-minishell", O_CREAT | O_RDWR, 0600);
	if (fd == -1)
		return (ft_perror(FAILED, "open"));
	hdoc = redir->heredoc;
	while (hdoc)
	{
		write(fd, (char *) hdoc->content, ft_strlen((char *) hdoc->content));
		write(fd, "\n", 1);
		hdoc = hdoc->next;
	}
	close(fd);
	fd = open("/tmp/_heredoc-minishell", O_RDONLY);
	if (fd == -1)
		return (ft_perror(FAILED, "open"));
	dup2(fd, 0);
	close(fd);
	return (SUCCESS);
}

static int	set_stdin(t_redir *redir, t_list *my_envp)
{
	int		fd;
	char	*file_exp;

	if (redir->code == INFILE)
	{
		file_exp = expand_trim(redir->file, my_envp);
		if (file_exp == NULL)
			return (puterror(FAILED, "expand in redirection failed\n"));
		if (file_exp[0] == '\0' || ft_strchr(file_exp, ' ') != 0)
			return (free(file_exp), puterror(FAILED, "ambiguous redirect\n"));
		free(redir->file);
		redir->file = file_exp;
		fd = open(redir->file, O_RDONLY);
		if (fd == -1)
			return (ft_perror(FAILED, "open"));
		dup2(fd, 0);
		close(fd);
		return (SUCCESS);
	}
	return (heredoc(redir));
}

static int	set_stdout(t_redir *redir, t_list *my_envp)
{
	int		fd;
	char	*file_exp;

	file_exp = expand_trim(redir->file, my_envp);
	if (file_exp == NULL)
		return (puterror(FAILED, "expand in redirection failed\n"));
	if (file_exp[0] == '\0' || ft_strchr(file_exp, ' ') != 0)
		return (free(file_exp), puterror(FAILED, "ambiguous redirect\n"));
	free(redir->file);
	redir->file = file_exp;
	if (redir->code == OUTFILE)
		fd = open(redir->file, O_CREAT | O_TRUNC | O_WRONLY, 0664);
	else
		fd = open(redir->file, O_CREAT | O_APPEND | O_WRONLY, 0664);
	if (fd == -1)
		return (ft_perror(FAILED, "open"));
	dup2(fd, 1);
	close(fd);
	return (SUCCESS);
}

int	redirection(t_command *cmd, t_list *my_envp)
{
	t_list	*node_redir;
	t_redir	*redir;

	node_redir = cmd->redir;
	while (node_redir)
	{
		redir = (t_redir *) node_redir->content;
		if (redir->code == INFILE || redir->code == HEREDOC)
		{
			if (set_stdin(redir, my_envp) == FAILED)
				return (FAILED);
		}
		else
		{
			if (set_stdout(redir, my_envp) == FAILED)
				return (FAILED);
		}
		node_redir = node_redir->next;
	}
	return (SUCCESS);
}
