/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stream.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 17:14:02 by lfrederi          #+#    #+#             */
/*   Updated: 2022/07/07 18:58:51 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "error.h"
#include "ft_string.h"
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>

int	ft_set_stdin(t_redir *redir)
{
	int		fd;
	t_list	*heredoc;

	if (redir->code == INFILE)
	{
		fd = open(redir->file, O_RDONLY);
		if (fd == -1)
			return (ft_perror(0, "open"));
		dup2(fd, 0);
		close(fd);
		return (1);
	}
	unlink("/tmp/_heredoc-minishell");
	fd = open("/tmp/_heredoc-minishell", O_CREAT | O_RDWR, 0600);
	if (fd == -1)
		return (ft_perror(0, "open"));
	heredoc = redir->heredoc;
	while (heredoc)
	{
		write(fd, (char *) heredoc->content, ft_strlen((char *) heredoc->content));
		heredoc = heredoc->next;
	}
	close(fd);
	fd = open("/tmp/_heredoc-minishell", O_RDONLY);
	dup2(fd, 0);
	close(fd);
	return (1);
}

int	ft_set_stdout(t_redir *redir)
{
	int	fd;

	if (redir->code == OUTFILE)
		fd = open(redir->file, O_CREAT | O_TRUNC | O_WRONLY, 0664);
	else
		fd = open(redir->file, O_CREAT | O_APPEND | O_WRONLY, 0664);
	if (fd == -1)
		return (ft_perror(0, "open"));
	dup2(fd, 1);
	close(fd);
	return (1);
}

int	ft_redirection(t_command *cmd)
{
	t_list	*node_redir;
	t_redir	*redir;

	node_redir = cmd->redir;
	while (node_redir)
	{
		redir = (t_redir *) node_redir->content;
		if (redir->code == INFILE || redir->code == HEREDOC)
		{
			if (ft_set_stdin(redir) == 0)
				return (0);
		}
		else
		{
			if (ft_set_stdout(redir) == 0)
				return (0);
		}
		node_redir = node_redir->next;
	}
	return (1);
}
