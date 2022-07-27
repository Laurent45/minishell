/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 15:14:12 by lfrederi          #+#    #+#             */
/*   Updated: 2022/07/27 16:44:38 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "command.h"
#include "execution.h"
#include "builtins.h"
#include "struct.h"
#include "error.h"
#include "env.h"
#include "signal_handler.h"
#include "ft_string.h"

#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

t_list	*g_envs;

void	ft_add_existatus(int exitstatus)
{
	char	*itoa_exit;
	char	*envvar;

	itoa_exit = ft_itoa(exitstatus);
	if (!itoa_exit)
		ft_puterror(0, "failed while saving exit status");
	envvar = ft_strjoin("?=", itoa_exit);
	free(itoa_exit);
	if (!envvar)
		ft_puterror(0, "failed while saving exit status");
	if (ft_add_envvar(envvar, 0) == 0)
		ft_puterror(0, "failed while saving exit status");
	free(envvar);
}

int	ft_run_shell(char *prompt, t_built *builts)
{
	t_list	*tokens;		// Content is t_token
	t_list	*commands;	// Content is t_command
	int		exitstatus;

	tokens = NULL;
	commands = NULL;
	if (ft_create_tokens(&tokens, prompt, 0) == 0)
		return (free(prompt), 1);
	free(prompt);
	if (ft_check_tokens(&tokens) == 0)
		return (ft_clear_tokens(&tokens, 1));
	if (ft_parse_to_command(&commands, tokens, 0) == 0)
		return (ft_clear_tokens(&tokens, 1));
	ft_clear_tokens(&tokens, 0);
	exitstatus = ft_execute(&commands, builts);
	if (exitstatus == EXIT_BUILT && ft_lstsize(commands) == 1)
		return (ft_clear_commands(&commands, -1));
	return (ft_clear_commands(&commands, exitstatus));
}

int	main(int argc, char *argv[], char *envp[])
{
	(void) argv;
	(void) argc;
	t_built	builts[NB_BUILT + 1];
	char	*prompt;
	int		exitstatus;

	if (ft_clone_env(&g_envs, envp) == ENV_FAILED)
		return (-1);
	ft_init_built(builts);
	exitstatus = 0;
	while (1 && exitstatus != -1)
	{
		ft_add_existatus(exitstatus);
		signal(SIGINT, &handler_sigint);
		prompt = readline("  minishell $ ");
		signal(SIGINT, SIG_IGN);
		if (!prompt)
		{
			printf("exit\n");
			break;
		}
		if (!prompt[0])
		{
			free(prompt);
			continue ;
		}
		add_history(prompt);
		exitstatus = ft_run_shell(prompt, builts);
	}
	rl_clear_history();
	ft_clear_env(&g_envs, 0);
	return (0);
}
