/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 16:28:31 by lfrederi          #+#    #+#             */
/*   Updated: 2022/07/12 16:43:36 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_is_builtin(t_command *command, t_builtins *array_builtins)
{
	int		i;
	t_list	*cmd_args;

	i = 0;
	cmd_args = command->cmd_args;
	while (array_builtins[i])
	{
		if (ft_strcmp(((char *) cmd_args->content), array_builts[i].str) == 0)
		{
		}
		i++;
	}

}

int	ft_simple_command(t_command *command, t_builtin *builtins)
{
	if (ft_is_builtin(command, builtins))
		return (1);
}
