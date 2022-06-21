/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 10:37:30 by lfrederi          #+#    #+#             */
/*   Updated: 2022/06/14 16:45:44 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "command.h"
#include "ft_string.h"
#include "ft_stdio.h"
#include "token.h"
#include "error.h"

static int	ft_heredoc(t_command *command, char *str)
{
	char	*line;
	t_list	*node;

	write(1, "> ", 2);
	line = get_next_line(0);
	if (!line)
		return (ft_allocated_err(0, "get_next_line"));
	while (line)
	{
		if (ft_strncmp(line, str, ft_strlen(str)) == 0)
		{
			free(line);
			return (1);
		}
		if (ft_new_node(&node, line) == 0)
		{
			free(line);
			return (ft_allocated_err(0, "node in ft_heredoc"));
		}
		ft_lstadd_back(&(command->input->heredoc), node);
		write(1, "> ", 2);
		line = get_next_line(0);
	}
	return (1);
}

int	ft_input(t_command *command, int code, char *str)
{
	t_input		*in;

	if (command->input == NULL && ft_new_input(&command->input) == 0)
		return (0);
	in = command->input;
	if (in->filename)
	{
		free(in->filename);
		in->filename = NULL;
	}
	if (in->heredoc)
		ft_lstclear(&(command->input->heredoc), &ft_del_str);
	if (code == LESS)
	{
		in->keyboard = 0;
		in->filename = ft_strdup(str);
		if (!in->filename)
			return (ft_allocated_err(0, "ft_strdup in ft_input"));
	}
	else
	{
		in->keyboard = 1;
		return (ft_heredoc(command, str));
	}
	return (1);
}

int	ft_output(t_command *command, int code, char *str)
{
	t_output	*out;

	if (command->output == NULL && ft_new_output(&command->output) == 0)
		return (0);
	out = command->output;
	if (out->filename)
	{
		free(out->filename);
		out->filename = NULL;
	}
	out->filename = ft_strdup(str);
	if (!out->filename)
		return (ft_allocated_err(0, "ft_strdup in ft_output"));
	if (code == GREATGREAT)
		out->append = 1;
	else
		out->append = 0;
	return (1);
}
