/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 11:00:18 by lfrederi          #+#    #+#             */
/*   Updated: 2022/06/14 19:47:39 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include <stdlib.h>

void	ft_del_token(void *token)
{
	if (((t_token *) token)->word)
		free(((t_token *) token)->word);
	free(token);
}

void	ft_del_str(void	*content)
{
	free(content);
}

void	ft_del_output(t_output *output)
{
	if (output->filename)
		free(output->filename);
	output->filename = NULL;
	free(output);
}

void	ft_del_input(t_input *input)
{
	if (input->filename)
		free(input->filename);
	if (input->heredoc)
		ft_lstclear(&(input->heredoc), &ft_del_str);
	input->filename = NULL;
	input->heredoc = NULL;
	free(input);
}

void	ft_del_command(void	*command)
{
	t_command	*cmd;

	cmd = (t_command *) command;
	if (cmd->args)
		ft_lstclear(&cmd->args, &ft_del_str);
	if (cmd->output)
		ft_del_output(cmd->output);
	if (cmd->input)
		ft_del_input(cmd->input);
	cmd->args = NULL;
	cmd->output = NULL;
	cmd->input = NULL;
	free(command);
}

void	ft_del_env(void	*content)
{
	free(((t_env *) content)->var);
	free(content);
}
