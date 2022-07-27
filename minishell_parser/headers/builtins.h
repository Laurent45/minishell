/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrederi <lfrederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 17:14:49 by lfrederi          #+#    #+#             */
/*   Updated: 2022/07/17 12:59:54 by lfrederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "struct.h"

# define NB_BUILT	7

void	ft_init_built(t_built *builts);
t_built	*ft_isbuiltins(char *cmd, t_built *builts);
int	ft_exe_builtins(t_built *built, t_command *command);

int		ft_cd(t_list *args);
int		ft_echo(t_list *args);
int		ft_env(t_list *args);
int		ft_exit_built(t_list *args);
int		ft_export(t_list *args);
int		ft_pwd(t_list *args);
int		ft_unset(t_list *args);

#endif
