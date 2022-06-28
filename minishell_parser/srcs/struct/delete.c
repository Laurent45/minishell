/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 11:00:18 by lfrederi          #+#    #+#             */
/*   Updated: 2022/06/26 17:33:23 by lfrederi         ###   ########.fr       */
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

/*void	ft_del_output(t_output *output)
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
}*/

void	ft_del_command(void	*command)
{
	// TODO: Delete clean redir
	t_command	*cmd;

	cmd = (t_command *) command;
	if (cmd->cmd)
		free(cmd->cmd);
	if (cmd->args)
		ft_lstclear(&cmd->args, &ft_del_str);
	if (cmd->env_var)
		ft_lstclear(&cmd->env_var, &ft_del_str);
	cmd->cmd = NULL;
	cmd->args = NULL;
	cmd->redir = NULL;
	cmd->env_var = NULL;
	free(command);
}

void	ft_del_env(void	*content)
{
	free(((t_env *) content)->var);
	free(content);
}
