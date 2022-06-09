/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 15:14:12 by lfrederi          #+#    #+#             */
/*   Updated: 2022/06/09 11:22:34 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "command.h"
#include "struct.h"
#include "error.h"
#include <stddef.h>
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
		printf("%s ", (char *) strings->content);
	printf("\n");
}

void	print_command(t_list *commands)
{
	for (; commands; commands = commands->next)
	{
		printf("args  --> ");
		print_strings(((t_command *) commands->content)->args);
		printf("output  --> ");
		print_strings(((t_command *) commands->content)->output);
		printf("append = %d\n", ((t_command *) commands->content)->append);
	}
}

int	main(int argc, char *argv[])
{
	if (argc == 1)
		return (0);
	t_list *tokens = NULL; // Content is t_token
	t_list *commands = NULL;
	if (ft_create_tokens(&tokens, argv[1]) == 0)
		return (ft_allocated_err(-1, "malloc (tokens)"));
	//printf("%s\n", argv[1]);
	print_tokens(tokens);
	
	ft_create_command(&commands, tokens);

	print_command(commands);

	ft_clear_tokens(&tokens);
	return (0);
}

