/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 19:13:51 by lfrederi          #+#    #+#             */
/*   Updated: 2022/06/26 17:35:17 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print.h"
#include <stdio.h>

void	print_tokens(t_list *tokens)
{
	for (; tokens; tokens = tokens->next)
		printf("code = %d et word = %s\n", ((t_token *) tokens->content)->code, ((t_token *) tokens->content)->word);
}

void	print_strings(t_list *strings)
{
	if (!strings)
	{
		printf("NULL\n");
		return ;
	}
	for (; strings; strings = strings->next)
		printf("%s", (char *) strings->content);
}

void	print_args(t_list *strings)
{
	for (; strings; strings = strings->next)
		printf("%s ", (char *) strings->content);
	printf("\n");	
}

void	print_command(t_list *commands)
{
	for (; commands; commands = commands->next)
	{
		t_command *cmd = (t_command *) commands->content;

		printf("cmd --> %s\n", cmd->cmd);

		printf("env_var  --> ");
		print_args(cmd->env_var);

		printf("args  --> ");
		print_args(cmd->args);

		for (; cmd->redir; cmd->redir = cmd->redir->next)
		{
			t_redir *redir = (t_redir *) cmd->redir->content;
			if (redir->outfile)
				printf("outfile => %s\n", redir->outfile);
			if (redir->appendfile)
				printf("appendfile => %s\n", redir->appendfile);

			if (redir->infile)
				printf("infile => %s\n", redir->infile);

			if (redir->heredoc)
				printf("heredoc => %s\n", redir->heredoc);
		}

	}
}

void	print_env(t_list *env)
{
	while (env)
	{
		printf("%s\n", ((t_env *) env->content)->var);
		env = env->next;
	}
}


