/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brturcio <brturcio@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 17:38:56 by brturcio          #+#    #+#             */
/*   Updated: 2025/05/18 14:38:51 by brturcio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_exit_error_msj(int exit, char *arg, char *msj)
{
	if (exit)
		ft_putendl_fd("exit", STDERR_FILENO);
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	if (arg)
	{
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (msj)
		ft_putstr_fd(msj, STDERR_FILENO);
}

static int	ft_is_number(char *arg)
{
	int	i;
	int	num;

	i = 0;
	num = 0;
	if (arg[0] == '-' || arg[0] == '+')
		i++;
	while (ft_isdigit(arg[i]))
		i++;
	if (arg[i] == '\0')
		num = 1;
	return (num);
}

static int	ft_check_exit_path(t_cmd *cmd, t_shell *shell)
{
	if (!ft_is_number(cmd->args[1]) && !cmd->args[2])
	{
		ft_exit_error_msj(1, cmd->args[1], "numeric argument required\n");
		ft_free_shell(shell);
		exit (255);
	}
	if (cmd->args[1] && cmd->args[2])
	{
		if (!ft_is_number(cmd->args[1]))
		{
			ft_exit_error_msj(1, cmd->args[1], "numeric argument required\n");
			ft_free_shell(shell);
			exit (255);
		}
		else
		{
			ft_exit_error_msj(0, NULL, "too many arguments\n");
			return (1);
		}
	}
	return (0);
}

static void	ft_exit_valid_path(t_cmd *cmd, t_shell *shell)
{
	long	num;

	num = shell->exit_status;
	if (cmd->args[1])
		num = ft_atol (cmd->args[1]);
	if (num < 0 || num > 255)
		num %= 256;
	ft_putendl_fd("exit", STDOUT_FILENO);
	ft_free_shell(shell);
	exit((unsigned char)num);
}

void	ft_exit_builtins(t_cmd *cmd, t_shell *shell)
{
	int	size;
	int	status;

	status = shell->exit_status;
	if (!cmd->args[1])
	{
		ft_putendl_fd("exit", STDOUT_FILENO);
		ft_free_shell(shell);
		exit(status);
	}
	if (ft_check_exit_path(cmd, shell))
		return ;
	size = ft_strlen(cmd->args[1]);
	if ((cmd->args[1][0] == '-' && (size > 20 || \
	(size == 20 && ft_strcmp(cmd->args[1], "-9223372036854775808") > 0))) \
	|| (cmd->args[1][0] != '-' && (size > 19 || (size == 19 && \
ft_strcmp(cmd->args[1], "9223372036854775807") > 0))))
	{
		ft_exit_error_msj(1, cmd->args[1], "numeric argument required\n");
		ft_free_shell(shell);
		exit(255);
	}
	ft_exit_valid_path(cmd, shell);
}
