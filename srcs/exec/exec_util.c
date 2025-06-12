/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brturcio <brturcio@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 21:25:01 by brturcio          #+#    #+#             */
/*   Updated: 2025/06/06 17:09:02 by brturcio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Forks and launches each command that requires a new process.
 *
 * For each command:
 * - If the command is not a builtin that runs without fork,
 *   it forks a new process.
 * - In the child, it installs execution signal handlers and
 *   runs the command.
 * - PIDs of children are stored for later `waitpid` calls.
 *
 * @param env The environment variables.
 * @param shell The shell state structure.
 * @return 1 on success, 0 on failure.
 */
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

/**
 * @brief Counts the number of commands in the command list.
 *
 * Useful to determine how many child processes will be created.
 *
 * @param cmds Pointer to the first command.
 * @return Number of commands.
 */

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
