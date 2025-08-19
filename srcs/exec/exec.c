/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 11:21:39 by yel-mens          #+#    #+#             */
/*   Updated: 2025/06/29 11:32:02 by yel-mens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_dup_files(t_cmd *cmd)
{
	if (cmd->in < 0 || cmd->out < 0)
		return (0);
	if (cmd->in >= 0 && cmd->in != STDIN_FILENO)
	{
		if (dup2(cmd->in, STDIN_FILENO) < 0)
		{
			perror("dup2 to stdin");
			close(cmd->in);
			if (cmd->out >= 0 && cmd->out != STDOUT_FILENO)
				close(cmd->out);
			return (0);
		}
		close(cmd->in);
	}
	if (cmd->out >= 0 && cmd->out != STDOUT_FILENO)
	{
		if (dup2(cmd->out, STDOUT_FILENO) < 0)
		{
			perror("dup2 to stdout");
			close(cmd->out);
			return (0);
		}
		close(cmd->out);
	}
	return (1);
}

static int	ft_exec(t_cmd *cmd, char **env, t_shell *shell)
{
	if (!cmd->args && (cmd->in != STDIN_FILENO || cmd->out != STDOUT_FILENO))
		return (2);
	if (!cmd->args)
		return (0);
	if (ft_is_builtin(cmd->args[0]))
	{
		ft_exec_builtins(cmd, shell);
		ft_free_shell(shell);
		exit(EXIT_SUCCESS);
	}
	else if (execve(cmd->args[0], cmd->args, env) < 0)
		return (0);
	return (1);
}

static void	ft_close(t_cmd *all_cmd, t_cmd *cmd)
{
	while (all_cmd)
	{
		if (all_cmd != cmd)
		{
			if (all_cmd->in >= 0 && all_cmd->in != STDIN_FILENO)
				close(all_cmd->in);
			if (all_cmd->out >= 0 && all_cmd->out != STDOUT_FILENO)
				close(all_cmd->out);
		}
		all_cmd = all_cmd->next;
	}
}

void	ft_child_process(t_cmd *cmd, char **env, t_shell *shell)
{
	int	exit_status;
	int	exec;

	exit_status = shell->exit_status;
	ft_close(shell->cmds, cmd);
	if (!ft_dup_files(cmd))
	{
		if (cmd->in < 0)
		{
			ft_free_shell(shell);
			exit(exit_status);
		}
		ft_free_shell(shell);
		return ;
	}
	exec = ft_exec(cmd, env, shell);
	ft_free_shell(shell);
	if (!exec)
		exit(EXIT_CMD_NOT_FOUND);
	if (exec == 2)
		exit(EXIT_SUCCESS);
}

/**
 * @brief Handles the complete execution cycle of commands.
 *
 * This function initializes process handling by:
 * - Counting the number of commands in the list.
 * - Allocating memory for child PIDs.
 * - Forking and executing each command.
 * - Waiting for all children and updating the exit status.
 * - Freeing all commands after execution.
 *
 * @param env The environment variables.
 * @param shell The shell state structure.
 */
void	ft_process(char **env, t_shell *shell)
{
	shell->nb_cmds = ft_count_cmds(shell->cmds);
	shell->pids = ft_calloc(shell->nb_cmds, sizeof(pid_t));
	if (!shell->pids)
	{
		ft_free_cmds(shell->cmds);
		shell->cmds = NULL;
		perror("malloc pids error");
		return ;
	}
	if (!ft_init_process(env, shell, 0))
		return ;
	ft_wait_status_child(shell);
	free(shell->pids);
	shell->pids = NULL;
	ft_free_cmds(shell->cmds);
	shell->cmds = NULL;
}
