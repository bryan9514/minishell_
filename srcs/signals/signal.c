/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brturcio <brturcio@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 10:32:34 by brturcio          #+#    #+#             */
/*   Updated: 2025/06/01 19:22:43 by brturcio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_sigint_handler(int signal)
{
	(void)signal;
	if (g_signal == MAIN_SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (g_signal == HEREDOC_SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
	}
	else if (g_signal == EXEC_SIGINT)
		write(STDOUT_FILENO, "\n", 1);
}

void	ft_wait_and_set_exit_status(t_shell *shell)
{
	int	i;
	int	status;
	int	sig;

	i = 0;
	while (i < shell->nb_cmds)
	{
		if (shell->pids[i] > 0)
		{
			waitpid(shell->pids[i], &status, 0);
			if (WIFSIGNALED(status))
			{
				sig = WTERMSIG(status);
				shell->exit_status = 128 + sig;
				if (sig == SIGQUIT)
					ft_putendl_fd("Quit (core dumped)", STDOUT_FILENO);
				g_signal = EXEC_SIGINT;
			}
			else if (WIFEXITED(status))
				shell->exit_status = WEXITSTATUS(status);
		}
		i++;
	}
}

void	ft_update_exit_status_by_signal(t_shell *shell)
{
	if (g_signal == MAIN_SIGINT || g_signal == HEREDOC_SIGINT)
		shell->exit_status = 130;
	else if (g_signal == EXEC_SIGQUIT)
		shell->exit_status = 131;
	g_signal = NO_SIGNAL;
}
