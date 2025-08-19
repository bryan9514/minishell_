/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brturcio <brturcio@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:21:11 by brturcio          #+#    #+#             */
/*   Updated: 2025/07/01 11:04:49 by brturcio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_builtin(char *arg)
{
	if (!ft_strcmp(arg, "echo") || !ft_strcmp(arg, "cd")
		|| !ft_strcmp(arg, "pwd") || !ft_strcmp(arg, "export")
		|| !ft_strcmp(arg, "unset") || !ft_strcmp(arg, "env")
		|| !ft_strcmp(arg, "exit"))
		return (1);
	return (0);
}

int	ft_is_builtin_no_fork(char *arg)
{
	if (!ft_strcmp(arg, "cd") || !ft_strcmp(arg, "export")
		|| !ft_strcmp(arg, "unset") || !ft_strcmp(arg, "exit"))
		return (1);
	return (0);
}

int	ft_no_fork(t_cmd *cmd, t_shell *shell)
{
	if (!(!(shell->nb_cmds > 1) && cmd->args
			&& ft_is_builtin_no_fork(cmd->args[0])))
		return (0);
	ft_exec_builtins(cmd, shell);
	return (1);
}

void	ft_exec_builtins(t_cmd *cmd, t_shell *shell)
{
	if (!ft_strcmp(cmd->args[0], "echo"))
		shell->exit_status = ft_echo_builtins(cmd);
	else if (!ft_strcmp(cmd->args[0], "cd"))
		shell->exit_status = ft_cd_builtins(cmd, shell);
	else if (!ft_strcmp(cmd->args[0], "pwd"))
		shell->exit_status = ft_pwd_builtins(cmd);
	else if (!ft_strcmp(cmd->args[0], "env"))
		shell->exit_status = ft_env_builtins(cmd, shell->env);
	else if (!ft_strcmp(cmd->args[0], "export"))
		shell->exit_status = ft_export_builtins(shell);
	else if (!ft_strcmp(cmd->args[0], "unset"))
		shell->exit_status = ft_unset_builtins(shell);
	else if (!ft_strcmp(cmd->args[0], "exit"))
		ft_exit_builtins(cmd, shell);
}
