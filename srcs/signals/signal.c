/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brturcio <brturcio@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 10:32:34 by brturcio          #+#    #+#             */
/*   Updated: 2025/06/13 08:48:30 by brturcio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_sigint_handler(int signal)
{
	(void)signal;
	g_signal = MAIN_SIGINT;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	ft_handler_heredoc(int signal)
{
	(void)signal;
	write(STDOUT_FILENO, "^C\n", 3);
	exit(EXIT_SIGINT);
}

void	ft_wait_status_child_continution(t_shell *shell, \
int status, int first_signal)
{
	int	sig;

	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		shell->exit_status = 128 + sig;
		if (sig == SIGQUIT && first_signal)
		{
			ft_putendl_fd("Quit", STDOUT_FILENO);
			first_signal = 0;
		}
		if (sig == SIGINT && first_signal)
		{
			write(STDOUT_FILENO, "\n", 1);
			first_signal = 0;
		}
	}
	else if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
}

void	ft_wait_status_child(t_shell *shell)
{
	int	i;
	int	status;
	int	first_signal;

	i = 0;
	first_signal = 1;
	ft_signals_ign();
	while (i < shell->nb_cmds)
	{
		if (shell->pids[i] > 0)
		{
			waitpid(shell->pids[i], &status, 0);
			ft_wait_status_child_continution(shell, status, first_signal);
		}
		i++;
	}
	ft_control_signals_main();
}

void	ft_update_exit_status_by_signal(t_shell *shell)
{
	if (g_signal == MAIN_SIGINT)
		shell->exit_status = 130;
	g_signal = NO_SIGNAL;
}
