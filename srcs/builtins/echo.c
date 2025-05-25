/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 13:40:32 by brturcio          #+#    #+#             */
/*   Updated: 2025/05/09 17:27:30 by yel-mens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_is_newline(char *str)
{
	int	i;

	if (str[0] != '-')
		return (1);
	i = 1;
	if (str[i] == '\0')
		return (1);
	while (str[i])
	{
		if (str[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

static int	ft_echo_printf(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	return (0);
}

int	ft_echo_builtins(t_cmd *cmd)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	if (!cmd || !cmd->args || !cmd->args[0])
		return (1);
	while (cmd->args[i] && !ft_is_newline(cmd->args[i]))
	{
		newline = 0;
		i++;
	}
	ft_echo_printf(cmd->args + i);
	if (newline)
		ft_putstr_fd("\n", 1);
	return (0);
}
