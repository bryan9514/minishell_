/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brturcio <brturcio@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 21:25:01 by brturcio          #+#    #+#             */
/*   Updated: 2025/06/29 13:44:23 by brturcio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_init_process(char **env, t_shell *shell, int i)
{
	t_cmd	*cmd;

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
			if (cmd->out != STDOUT_FILENO && cmd->out > 0)
				close(cmd->out);
			if (cmd->in != STDIN_FILENO && cmd->in > 0)
				close(cmd->in);
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
