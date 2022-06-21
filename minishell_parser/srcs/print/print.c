/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 19:13:51 by lfrederi          #+#    #+#             */
/*   Updated: 2022/06/19 19:24:41 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print.h"
#include <stdio.h>

void	print_tokens(t_list *tokens)
{
	for (; tokens; tokens = tokens->next)
		printf("code = %d et word = %s et quote = %d\n", ((t_token *) tokens->content)->code, ((t_token *) tokens->content)->word, ((t_token *) tokens->content)->quote);
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

		printf("args  --> ");
		print_args(cmd->args);

		if (cmd->output)
		{
			if (cmd->output->filename)
				printf("output (filename) ==> %s\n", cmd->output->filename);
			printf("output (append) ==> %d\n", cmd->output->append);
		}
		else
			printf("output == NULL\n");

		if (cmd->input)
		{
			printf("input (keyboard) ==> %d\n", cmd->input->keyboard);
			if (cmd->input->filename)
				printf("input (filename) ==> %s\n", cmd->input->filename);
			else
				printf("input (filename) ==> NULL\n");
			if (cmd->input->heredoc)
			{
				printf("input (heredoc) ==> ");
				print_strings(cmd->input->heredoc);
			}
			else
				printf("input (heredoc) ==> NULL\n");
		}
		else
			printf("input == NULL\n");
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


