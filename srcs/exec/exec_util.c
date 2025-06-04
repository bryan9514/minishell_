/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brturcio <brturcio@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 21:25:01 by brturcio          #+#    #+#             */
/*   Updated: 2025/05/31 21:03:32 by brturcio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_init_process(char **env, t_shell *shell)
{
	int		i;
	t_cmd	*cmd;

	i = 0;
	cmd = shell->cmds;
	while (cmd)
	{
		if (!ft_no_fork(cmd, shell))
		{
			shell->pids[i] = fork();
			if (shell->pids[i] < 0)
				return (1);
			if (!shell->pids[i])
			{
				ft_control_signals_child();
				ft_child_process(cmd, env, shell);
				exit(EXIT_FAILURE);
			}
			i++;
		}
		cmd = cmd->next;
	}
	return (1);
}

int	ft_count_cmds(t_cmd *cmds)
{
	int	count;

	count = 0;
	while (cmds)
	{
		count++;
		cmds = cmds->next;
	}
	return (count);
}
