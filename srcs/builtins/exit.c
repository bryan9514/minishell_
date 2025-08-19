/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brturcio <brturcio@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 17:38:56 by brturcio          #+#    #+#             */
/*   Updated: 2025/06/30 17:27:19 by brturcio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_exit_error_msj(int exit, char *arg, char *msj)
{
	(void)exit;
	if (isatty(STDIN_FILENO))
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
		exit (2);
	}
	if (cmd->args[1] && cmd->args[2])
	{
		if (!ft_is_number(cmd->args[1]))
		{
			ft_exit_error_msj(1, cmd->args[1], "numeric argument required\n");
			ft_free_shell(shell);
			exit (2);
		}
		else
		{
			ft_exit_error_msj(1, NULL, "too many arguments\n");
			shell->exit_status = 1;
			return (1);
		}
	}
	return (0);
}

static int	is_long_overflow(char *arg)
{
	int	size;

	size = ft_strlen(arg);
	if (arg[0] == '-')
	{
		if (size > 20 || (size == 20 && \
ft_strcmp(arg, "-9223372036854775808") > 0))
			return (1);
	}
	else
	{
		if (size > 19 || (size == 19 && \
ft_strcmp(arg, "9223372036854775807") > 0))
			return (1);
	}
	return (0);
}

void	ft_exit_builtins(t_cmd *cmd, t_shell *shell)
{
	int	status;

	status = shell->exit_status;
	if (isatty(STDIN_FILENO) && !cmd->next)
		ft_putstr_fd("exit\n", STDERR_FILENO);
	if (!cmd->args[1])
	{
		ft_free_shell(shell);
		exit(status);
	}
	if (ft_check_exit_path(cmd, shell))
		return ;
	if (is_long_overflow(cmd->args[1]))
	{
		ft_exit_error_msj(1, cmd->args[1], "numeric argument required\n");
		ft_free_shell(shell);
		exit(2);
	}
	status = ft_atol (cmd->args[1]);
	ft_free_shell(shell);
	exit((unsigned char)status);
}
